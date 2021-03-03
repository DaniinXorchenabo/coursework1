#include <list>
#include <iterator>
#include <memory>
#include <iostream>
#include <windows.h>
#include <conio.h>
//#include "python_graphics.h"

typedef void (*VoidReturnFunc)();
typedef int (*intReturnFunc)();
typedef int (*intReturnFunc1int)(int);
typedef int (*intReturnFunc2int)(int, int);
typedef void (*VoidReturnFunc3int)(int, int, int);
typedef void (*VoidReturnFunc5int)(int, int, int, int, int);

   HINSTANCE a = LoadLibrary("python_graphics.dll");
   VoidReturnFunc myFunc;
//   intReturnFunc1int init_console, print_class;
//   VoidReturnFunc3int draw_point_python;
//   VoidReturnFunc5int draw_line_python;

   intReturnFunc1int init_console = (intReturnFunc1int) GetProcAddress(a, "create_obj");
   intReturnFunc1int print_class = (intReturnFunc1int) GetProcAddress(a, "print_class");
   VoidReturnFunc3int draw_point_python = (VoidReturnFunc3int) GetProcAddress(a, "draw_point_python");
   VoidReturnFunc5int draw_line_python =  (VoidReturnFunc5int) GetProcAddress(a, "draw_line_python");

using namespace std;



class Point{

    private:
        float x, y;
        int canvas;

    public:

        int get_canvas() const {
            return canvas;
        }
        float get_raw_x() const {
            return x;
        }

        float get_raw_y() const {
            return y;
        }

        int get_x() const {
            return (int)x;
        }
        int get_y() const {
            return (int)y;
        }

        Point(){
            x = 0;
            y = 0;
        }

        Point(int my_canvas, int s_x, int s_y){
            canvas = my_canvas;
            x = s_x;
            y = s_y;
        }

        Point (const Point& copy){
            canvas = copy.get_canvas();
            x = copy.get_raw_x();
            y = copy.get_raw_y();
        }
        void draw(){
            cout<<"Draw point";
            cout<<get_x();
            cout<<", ";
            cout<<get_y()<<endl;
//            draw_point_python(canvas, x, y);
        }
        void draw_line(Point& point){
//            cout<<"Draw line from (";
//            cout<<get_x();
//            cout<<", ";
//            cout<<get_y();
//            cout<<") to (";
//            cout<<point.get_x();
//            cout<<", ";
//            cout<<point.get_y();
//            cout<<")\n";
            draw_line_python(canvas, get_x(), get_y(), point.get_x(), point.get_y());
        }

};

class BaseFigure{

    private:
        int canvas;

    public:
        list<shared_ptr<BaseFigure>> complex_figure = {};
        list<shared_ptr<Point>> points_with_line = {}; // точки, соеденнные линией
        list<shared_ptr<Point>> points_no_line = {};  // точки, не соеденённые линией

        bool is_complex_figure(){
            return complex_figure.empty() ;
        }

        int get_canvas() const {
            return canvas;
        }

        BaseFigure(){}

        BaseFigure(int my_canvas){ canvas = my_canvas; }

        BaseFigure(int my_canvas, initializer_list<Point> points){
            /* Вызов BaseFigure(my_canvas, p1, p2, p3}) */
            canvas = my_canvas;
            for (auto iter : points){
                points_with_line.push_back(make_shared<Point>(iter));
            }
        }

       /* BaseFigure(int my_canvas, Point points, ...){
            // Вызов BaseFigure(my_canvas, p1, p2, p3})
               cout<<"**********----"<<endl;

            canvas = my_canvas;
            cout<<"**********----"<<endl;
            for (Point* p = &points; points>0; points--){
                cout<<"**********----1"<<endl;
                points_with_line.push_back(make_shared<Point>(*(++p)));
                cout<<"**********----2"<<endl;
            }
            cout<<"**********----"<<endl;
        }*/
//        g++ BaseFigure1_test.cpp -o main.exe
//

        BaseFigure(int my_canvas, int coordinates, ...){
            canvas = my_canvas;
            for (auto coordinate = &coordinates; *coordinate; coordinate++){
                points_with_line.push_back(make_shared<Point>(canvas, *coordinate, *(++coordinate)));
            }
        }

        BaseFigure (const BaseFigure& figure_material){
            canvas = figure_material.get_canvas();
            points_no_line = figure_material.points_no_line;
            points_with_line = figure_material.points_with_line;
            complex_figure = figure_material.complex_figure;
        }

        void draw(){
            if (complex_figure.size() > 1){
                for (auto figure: complex_figure){
                    figure->draw();
                }
            }
            else {
                auto first_point = points_with_line.back();
                for (auto second_point: points_with_line){
                    first_point->draw_line(*second_point);
                    first_point = second_point;
                }
                for (auto point: points_no_line){
                    point->draw();
                }
            }
        }

        BaseFigure& operator+=(const BaseFigure& other_figure) {
            if (complex_figure.empty() && other_figure.complex_figure.empty()){
                complex_figure.push_back(make_shared<BaseFigure>(*this));
                complex_figure.push_back(make_shared<BaseFigure>(other_figure));
                points_with_line = {};
                points_no_line = {};

            }
            else if (!complex_figure.empty() && other_figure.complex_figure.empty()){
                complex_figure.push_back(make_shared<BaseFigure>(other_figure));
            }
            else if (complex_figure.empty() && !other_figure.complex_figure.empty()){
                complex_figure = other_figure.complex_figure;
                complex_figure.push_front(make_shared<BaseFigure>(*this));
                points_with_line = {};
                points_no_line = {};

            }
            else if (!complex_figure.empty() && !other_figure.complex_figure.empty()){
//                complex_figure += other_figure.complex_figure;
//                complex_figure.merge(other_figure.complex_figure);
                auto a = other_figure.complex_figure;
                complex_figure.merge(a);
            }

            return *this;
        }

        BaseFigure operator+(const BaseFigure& right) {

            BaseFigure new_figure(get_canvas());

            if (complex_figure.empty() && right.complex_figure.empty()){
                new_figure.complex_figure.push_back(make_shared<BaseFigure>(*this));
                new_figure.complex_figure.push_back(make_shared<BaseFigure>(right));
            }
            else if (!complex_figure.empty() && right.complex_figure.empty()){
                new_figure.complex_figure = complex_figure;
                new_figure.complex_figure.push_back(make_shared<BaseFigure>(right));
            }
            else if (complex_figure.empty() && !right.complex_figure.empty()){
                new_figure.complex_figure = right.complex_figure;
                new_figure.complex_figure.push_front(make_shared<BaseFigure>(*this));
            }
            else if (!complex_figure.empty() && !right.complex_figure.empty()){
                new_figure.complex_figure = complex_figure;
                auto a = right.complex_figure;
                complex_figure.merge(a);
//                new_figure.complex_figure.merge(right.complex_figure);
//                complex_figure += right.complex_figure;
//                complex_figure.merge(right.complex_figure);
            }

            return new_figure;
        }

};


int main(){


   int my_obj = init_console(5694);
   print_class(my_obj);
    BaseFigure one(1, { Point(1,1,1), Point(1,1,2),Point(1,1,3),Point(1,1,4),Point(1,1,5) });
    BaseFigure one_1(1, { Point(1,2,1), Point(1,2,2),Point(1,2,3),Point(1,2,4),Point(1,2,5) });
    BaseFigure one_3(1, { Point(1,3,1), Point(1,3,2),Point(1,3,3),Point(1,3,4),Point(1,3,5) });

    BaseFigure one_4 = one + one_1 + one_3;
    one_4.draw();
    cout<<"0**********----!!"<<endl;
    one.draw();
    cout<<"1**********----!!"<<endl;
    one_1.draw();
    cout<<"2**********----!!"<<endl;
    one_3.draw();
    getch();
    return 0;
}
