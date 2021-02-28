#include <list>
#include "python_graphics.h"
using std::list;

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
            draw_point(canvas, x, y);
        }
        void draw_line(Point& point){
            draw_line(canvas, x, y, point->get_x(), point->get_y());
        }

};

//class BaseFigure{
//
//    private:
//        int canvas;
//
//    public:
//        list<BaseFigure&> complex_figure = list<BaseFigure*>();
//        list<Point> points_with_line = list<Point>(); // точки, соеденнные линией
//        list<Point> points_no_line = list<Point>();  // точки, не соеденённые линией
//
//        bool is_complex_figure(){
//            return complex_figure != NULL;
//        }
//        int get_canvas(){
//            return canvas;
//        }
//
//        BaseFigure(){}
//
//
//        BaseFigure(const initializer_list<Point> &points)
//        {
//            points_with_line(points){};
//        }
//
//        BaseFigure(int my_canvas, const initializer_list<Point> &points){
//            /* Вызов BaseFigure(my_canvas, { p1, p2, p3 }) */
//
//            canvas = my_canvas;
//            points_with_line(points){};
////            for (auto p = &points; *p; p++){ points_with_line.add(*p); }
//        }
//
//        BaseFigure(int my_canvas, int coordinates, ...){
//            canvas = my_canvas;
//            for (auto coordinate = &coordinates; *coordinate; coordinate++){
//                points_with_line.add(canvas, Point(coordinate, ++coordinate));
//            }
//        }
//
//        BaseFigure(BaseFigure figure_material){
//            canvas = figure_material.get_canvas();
//            points_no_line = figure_material.points_no_line;
//            points_with_line = figure_material.points_with_line;
//            complex_figure = figure_material.complex_figure;
//        }
//
//        void draw(){
//            if (len(complex_figure) > 1){
//                for (auto figure: complex_figure){
//                    figure.draw()
//                }
//            }
//            else {
//                Point start_point = NULL;
//                for (auto point: points_with_line){
//                    if (start_point != NULL){
//                        point.draw_line(start_point);
//                    }
//                    start_point = Point
//                }
//                for (auto point: points_no_line){
//                    point.draw();
//                }
//            }
//        }
//
//        const BaseFigure operator+=(const BaseFigure& other_figure) const {
//            if ((len(complex_figure) == 0) && (len(other_figure.complex_figure) == 0)){
//                complex_figure.add(BaseFigure(this));
//                complex_figure.add(other_figure);
//                points_with_line = list<Point>();
//                points_no_line = list<Point>();
//
//            }
//            else if ((len(complex_figure) != 0) && (len(other_figure.complex_figure) == 0)){
//                complex_figure.add(BaseFigure(other_figure));
//                other_figure.points_with_line = list<Point>();
//                other_figure.points_no_line = list<Point>();
//            }
//            else if ((len(complex_figure) == 0) && (len(other_figure.complex_figure) != 0)){
//                complex_figure = other_figure.complex_figure;
//                complex_figure.insert(0, BaseFigure(this));
//                points_with_line = list<Point>();
//                points_no_line = list<Point>();
//
//            }
//            else if ((len(complex_figure) != 0) && (len(other_figure.complex_figure) != 0)){
//                complex_figure.exists(other_figure.complex_figure);
//            }
//            return this
//        }
//
//};


int main(){
//    BF({Point(1,2), Point(1,2), Point(1,2), Point(1,2)})
    return 0;
}
