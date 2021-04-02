#include <list>
#include <iterator>
#include <memory>
#include <iostream>
#include <windows.h>
#include <conio.h>
#include <chrono>
#include <cmath>
#include <random>
//#include "python_graphics.h"

typedef void (*VoidReturnFunc)();
typedef void (*VoidReturnFunc1int)(int);
typedef int (*intReturnFunc)();
typedef int (*intReturnFunc1int)(int);
typedef int (*intReturnFunc2int)(int, int);
typedef void (*VoidReturnFunc3int)(int, int, int);
typedef void (*VoidReturnFunc5int)(int, int, int, int, int);
typedef void (*VoidReturnFunc1int4float)(int, float, float, float, float);
typedef bool (*BoolReturnFunc1int)(int);
typedef float (*FloatReturnFunc1int)(int);

   HINSTANCE a = LoadLibrary("python_graphics.dll");
   VoidReturnFunc myFunc;
//   intReturnFunc1int init_console, print_class;
//   VoidReturnFunc3int draw_point_python;
//   VoidReturnFunc5int draw_line_python;

   intReturnFunc1int init_console = (intReturnFunc1int) GetProcAddress(a, "create_obj");
   intReturnFunc1int print_class = (intReturnFunc1int) GetProcAddress(a, "print_class");

   intReturnFunc1int get_event_type = (intReturnFunc1int) GetProcAddress(a, "get_event_type");
   intReturnFunc1int get_event_code = (intReturnFunc1int) GetProcAddress(a, "get_event_code");

   intReturnFunc1int get_console_x_size_python = (intReturnFunc1int) GetProcAddress(a, "get_console_x_size_python");
   intReturnFunc1int get_console_y_size_python = (intReturnFunc1int) GetProcAddress(a, "get_console_y_size_python");

   FloatReturnFunc1int my_get_mouse_x = (FloatReturnFunc1int) GetProcAddress(a, "get_mouse_x");
   FloatReturnFunc1int my_get_mouse_y = (FloatReturnFunc1int) GetProcAddress(a, "get_mouse_y");

   intReturnFunc2int create_canvas = (intReturnFunc2int) GetProcAddress(a, "create_canvas");
   VoidReturnFunc3int draw_point_python = (VoidReturnFunc3int) GetProcAddress(a, "draw_point_python");
   VoidReturnFunc1int4float draw_line_python =  (VoidReturnFunc1int4float) GetProcAddress(a, "draw_line_python");
   VoidReturnFunc1int refresh_python =  (VoidReturnFunc1int)  GetProcAddress(a, "refresh_python");
   VoidReturnFunc1int exit_console_python = (VoidReturnFunc1int) GetProcAddress(a, "exit_console_python");
   BoolReturnFunc1int check_exit_button_python = (BoolReturnFunc1int)  GetProcAddress(a, "check_exit_button_python");

   intReturnFunc new_start_python =  (intReturnFunc)  GetProcAddress(a, "new_start_python");
   VoidReturnFunc1int new_renderer_python =  (VoidReturnFunc1int)  GetProcAddress(a, "new_renderer_python");
   VoidReturnFunc1int4float new_draw_line_python =  (VoidReturnFunc1int4float)  GetProcAddress(a, "new_draw_line_python");


//   int new_start_python();
//void new_renderer_python(int);
//void new_draw_line_python(int, float, float, float, float);

using namespace std;

const float MAX_SPEED = 4;
const float MAX_ROTATION_SPEED = 0.3;



uint64_t current_timestamp(){
    // copy paste with https://habr.com/ru/post/537682/
    return chrono::duration_cast<chrono::milliseconds>(
        chrono::steady_clock::now().time_since_epoch()
    ).count();
}

pair<int, int> get_event(int canvas){
    int ev = get_event_type(canvas);
    if (ev != 0){
        return {ev, get_event_code(canvas)};
    }
    return {0, 0};
}


class Point{

    private:
        float x, y, radius = -1;
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

        void reboot_radius() {
            radius = -1;
        }

        int get_x() const {
            return (int)x;
        }
        int get_y() const {
            return (int)y;
        }

        bool border_control(int max_x, int max_y){
            // Вернет true, если точка находится в пределах экрана
            return x >= 0 && y >= 0 && x <= max_x && y <= max_y;
        }

        pair<float, float> get_polar_coord(float c_x, float c_y){
            float r_y = y - c_y;
            float r_x = x - c_x;
            if (radius == -1){
                radius = sqrt(r_x * r_x + r_y * r_y);
            }
            return {radius, atan2(r_y, r_x)};
        }

        pair<float, float> get_change_polar_coord(float r, float angle, float c_x, float c_y){
            return {r * cos(angle) + c_x - x, r * sin(angle) + c_y - y};
        }

        void set_polar_coord(float r, float angle, float c_x, float c_y){
            x = r * cos(angle) + c_x;
            y = r * sin(angle) + c_y;
        }

        void move_point(float add_x, float add_y){
            x += add_x;
            y += add_y;
        }
        void set_coord(float new_x, float new_y){
            x = new_x;
            y = new_y;
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

        tuple<shared_ptr<Point>, shared_ptr<Point>, shared_ptr<Point>, shared_ptr<Point>>
         get_extreme_points(tuple<shared_ptr<Point>, shared_ptr<Point>, shared_ptr<Point>, shared_ptr<Point>> data){
            auto [max_x, max_y, min_x, min_y] = data;
            if (max_x->get_raw_x() <= x) max_x = make_shared<Point>(*this);
            if (max_y->get_raw_y() <= y) max_y = make_shared<Point>(*this);
            if (min_x->get_raw_x() >= x) min_x = make_shared<Point>(*this);
            if (min_y->get_raw_y() >= y) min_y = make_shared<Point>(*this);
            return {max_x, max_y, min_x, min_y};
        }

//        tuple<Point, Point, Point, Point> get_extreme_points(tuple<Point, Point, Point, Point> data){
//            auto [max_x, max_y, min_x, min_y] = data;
//            if (max_x.get_raw_x() <= x) max_x = Point(*this);
//            if (max_y.get_raw_y() <= y) max_y = Point(*this);
//            if (min_x.get_raw_x() >= x) min_x = Point(*this);
//            if (min_y.get_raw_y() >= y) min_y = Point(*this);
//            return {max_x, max_y, min_x, min_y};
//        }

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
//            cout<<x;
//            cout<<", ";
//            cout<<y;
//            cout<<"\n";
            new_draw_line_python(canvas, x, y, point.get_raw_x(), point.get_raw_y());
//            draw_line_python(canvas, x, y, point.get_raw_x(), point.get_raw_y());
        }

};

class BaseFigure{

    private:
        int canvas;
        float norm_speed_x = 2; // скорость передвижения в секунду
        float norm_speed_y = 0.5;
        float norm_speed_rotation = 0.1; // скорость поворота в секунду

        float speed_x;
        float speed_y;
        float speed_rotation;

        static float get_random_speed(){
            static random_device rd;  // Источник зерна для рандома
            static mt19937 gen(rd());  // Вихрь Мерсенна (Mersenne Twister)
            static uniform_int_distribution<> get_speed(-MAX_SPEED * 100, MAX_SPEED * 100);
            return (float)get_speed(gen) / 100;
        }

        static float get_random_rotation_speed(){
            static random_device rd;  // Источник зерна для рандома
            static mt19937 gen(rd());  // Вихрь Мерсенна (Mersenne Twister)
            static uniform_int_distribution<> get_rotation_speed(-MAX_ROTATION_SPEED * 100, MAX_ROTATION_SPEED * 100);
            return (float)get_rotation_speed(gen) / 100;
        }

    public:
        list<shared_ptr<BaseFigure>> complex_figure = {};
        list<shared_ptr<Point>> points_with_line = {}; // точки, соеденнные линией
        list<shared_ptr<Point>> points_no_line = {};  // точки, не соеденённые линией
        static bool left_button_pressed; // Нажата левая клавиша мыши
        bool user_move_not_me =  false;
        bool user_move_me = false;

        bool is_complex_figure(){
            return complex_figure.empty() ;
        }

        int get_canvas() const {
            return canvas;
        }

        tuple<float, float, int> get_raw_center_point(){
            float x = 0, y = 0;
            int counter = 0;
            if (complex_figure.size() > 1){
                for (auto figure: complex_figure){
                    auto [new_x, new_y, new_counter] = figure->get_raw_center_point();
                    x += new_x;
                    y += new_y;
                    counter += new_counter;
                }
            } else {
                for (auto point: points_with_line){
                    x += point->get_raw_x();
                    y += point->get_raw_y();
                    ++counter;
                }
                if (counter == 0){
                    for (auto point: points_no_line){
                        x += point->get_raw_x();
                        y += point->get_raw_y();
                        ++counter;
                    }
                }
            }
            return {x, y ,counter};
        }

        pair<float, float> get_center_point(){
            float x = 0, y = 0;
            int counter = 0;
            if (complex_figure.size() > 1){
                for (auto figure: complex_figure){
                    auto [new_x, new_y, new_counter] = figure->get_raw_center_point();
                    x += new_x;
                    y += new_y;
                    counter += new_counter;
                }
            } else {
                for (auto point: points_with_line){
                    x += point->get_raw_x();
                    y += point->get_raw_y();
                    ++counter;
                }
                if (counter == 0){
                    for (auto point: points_no_line){
                        x += point->get_raw_x();
                        y += point->get_raw_y();
                        ++counter;
                    }
                }
            }
            return {x / counter, y / counter};
        }

        BaseFigure(){}

        BaseFigure(int my_canvas){ canvas = my_canvas; }

        BaseFigure(int my_canvas, initializer_list<Point> points){
            /* Вызов BaseFigure(my_canvas, p1, p2, p3}) */
            canvas = my_canvas;
            for (auto iter : points){
                points_with_line.push_back(make_shared<Point>(iter));
            }
            norm_speed_x = BaseFigure::get_random_speed();
            norm_speed_y = BaseFigure::get_random_speed();
            norm_speed_rotation = BaseFigure::get_random_rotation_speed();
        }

        BaseFigure(int my_canvas, int coordinates, ...){
            canvas = my_canvas;
            for (auto coordinate = &coordinates; *coordinate; coordinate++){
                points_with_line.push_back(make_shared<Point>(canvas, *coordinate, *(++coordinate)));
            }
            norm_speed_x = BaseFigure::get_random_speed();
            norm_speed_y = BaseFigure::get_random_speed();
            norm_speed_rotation = BaseFigure::get_random_rotation_speed();
        }

        BaseFigure (const BaseFigure& figure_material){
            canvas = figure_material.get_canvas();
            points_no_line = figure_material.points_no_line;
            points_with_line = figure_material.points_with_line;
            complex_figure = figure_material.complex_figure;
            norm_speed_x = figure_material.norm_speed_x;
            norm_speed_y = figure_material.norm_speed_y;
            norm_speed_rotation = figure_material.norm_speed_rotation;
        }

        void draw(){
            if (complex_figure.size() > 1){
                for (auto figure: complex_figure){
                    figure->draw();
                }
            } else {
                // TODO: сделать условие, что длинна должна быть больше 2-х
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

        void move_figure(){ move_figure(speed_x, speed_y); }
        void move_figure(float add_x, float add_y){
            if (complex_figure.size() > 1){
                for (auto figure: complex_figure){
                    figure->move_figure(add_x, add_y);
                }
            } else {
                for (auto point: points_no_line){
                    point->move_point(add_x, add_y);

                }
                for (auto point: points_with_line){
                    point->move_point(add_x, add_y);

                }
            }
        }

        pair<float, float> rotation_figure(){
            auto [center_x, center_y] = get_center_point();
            rotation_figure(center_x, center_y, center_x, center_y);
            return {center_x, center_y};
        }

        pair<float, float> rotation_figure(float center_x, float center_y){
            rotation_figure(center_x, center_y, center_x, center_y);
            return {center_x, center_y};
        }
        pair<float, float> rotation_figure(float center_x, float center_y,
                                           float rotation_point_x, float rotation_point_y){
            if (complex_figure.size() > 1){
                for (auto figure: complex_figure){
                    figure->rotation_figure(center_x, center_y, rotation_point_x, rotation_point_y);
                }
            } else {
                for (auto point: points_with_line){
                    if (rotation_point_x != center_x || rotation_point_y != center_y) point->reboot_radius();
                    auto [r, angle] = point->get_polar_coord(rotation_point_x, rotation_point_y);
                    angle += speed_rotation;
                    point->set_polar_coord(r, angle, rotation_point_x, rotation_point_y);
                    if (rotation_point_x != center_x || rotation_point_y != center_y) point->reboot_radius();
                }
                for (auto point: points_no_line){
                    if (rotation_point_x != center_x || rotation_point_y != center_y) point->reboot_radius();
                    auto [r, angle] = point->get_polar_coord(rotation_point_x, rotation_point_y);
                    angle += speed_rotation;
                    point->set_polar_coord(r, angle, center_x, center_y);
                    if (rotation_point_x != center_x || rotation_point_y != center_y) point->reboot_radius();
                }
            }
            return {center_x, center_y};
        }


        tuple<shared_ptr<Point>, shared_ptr<Point>, shared_ptr<Point>, shared_ptr<Point>>
            get_extreme_points(){
            auto max_x = make_shared<Point>(0, -1000, 0);
            auto max_y = make_shared<Point>(0, 0, -1000);
            auto min_x =  make_shared<Point>(0, 10000, 0);
            auto min_y = make_shared<Point>(0, 0, 10000);
//            return {max_x, max_y, min_x, min_y};
            return get_extreme_points({max_x, max_y, min_x, min_y});
        }

        tuple<shared_ptr<Point>, shared_ptr<Point>, shared_ptr<Point>, shared_ptr<Point>>
            get_extreme_points(tuple<shared_ptr<Point>, shared_ptr<Point>, shared_ptr<Point>, shared_ptr<Point>> data){
            if (complex_figure.size() > 1){
                for (auto figure: complex_figure){
                    data = figure->get_extreme_points(data);
                }
            } else {
                for (auto point: points_no_line){
                    data = point->get_extreme_points(data);

                }
                for (auto point: points_with_line){
                    data = point->get_extreme_points(data);

                }
            }
            return data;
        }



        tuple<float, float, float, float> border_regulate(int x_size, int y_size, float center_x, float center_y){
            auto [max_x, max_y, min_x, min_y] = get_extreme_points();
            if (x_size <= max_x->get_raw_x() && norm_speed_x > 0) norm_speed_x *= -1;
            if (y_size <= max_y->get_raw_y() && norm_speed_y > 0) norm_speed_y *= -1;
            if (0 >= min_x->get_raw_x() && norm_speed_x < 0) norm_speed_x *= -1;
            if (0 >= min_y->get_raw_y() && norm_speed_y < 0) norm_speed_y *= -1;

            auto [max_x_r, max_x_angle] = max_x->get_polar_coord(center_x, center_y);
            auto [dx, useless_dy] = max_x->get_change_polar_coord(max_x_r, max_x_angle + speed_rotation, center_x, center_y);
            auto [max_y_r, max_y_angle] = max_y->get_polar_coord(center_x, center_y);
            auto [useless_dx, dy] = max_y->get_change_polar_coord(max_y_r, max_y_angle + speed_rotation, center_x, center_y);

            auto [mim_x_r, min_x_angle] = min_x->get_polar_coord(center_x, center_y);
            auto [min_dx, useless_dy1] = min_x->get_change_polar_coord(mim_x_r, min_x_angle + speed_rotation, center_x, center_y);
            auto [min_y_r, min_y_angle] = min_y->get_polar_coord(center_x, center_y);
            auto [useless_dx1, min_dy] = min_y->get_change_polar_coord(min_y_r, min_y_angle + speed_rotation, center_x, center_y);

            auto rotation_point_x = center_x;
            auto rotation_point_y = center_y;
            if (x_size <= max_x->get_raw_x() && dx > 0){
//                speed_rotation *= -1;
                rotation_point_x = max_x->get_raw_x();
                rotation_point_y = max_x->get_raw_y();
            }
            else if (y_size <= max_y->get_raw_y() && dy > 0){
//                speed_rotation *= -1;
                rotation_point_x = max_y->get_raw_x();
                rotation_point_y = max_y->get_raw_y();
            }
            else if (0 >= min_x->get_raw_x() && min_dx < 0){
//                speed_rotation *= -1;
                rotation_point_x = min_x->get_raw_x();
                rotation_point_y = min_x->get_raw_y();
            }
            else if (0 >= min_y->get_raw_y() && min_dy < 0){
//                speed_rotation *= -1;
                rotation_point_x = min_y->get_raw_x();
                rotation_point_y = min_y->get_raw_y();
            }
            return {center_x, center_y, rotation_point_x, rotation_point_y};

        }
        tuple<float, float, float, float> border_regulate(int x_size, int y_size){
            auto [center_x, center_y] = get_center_point();
            return border_regulate(x_size, y_size, center_x, center_y);
        }

//        bool is_2_lines(float x_1, float y_1, float x_2, float y_2, float x1, float y1, float x2, float y2){
//            // Вернёт true если 2 отрезка пересекаются
//            float pr1 = (x1 - x_1)*(y_2 - y_1) - (y1 - y_1)*(x_2 - x_1);
//            float pr2 = (x2 - x_1)*(y_2 - y_1) - (y2 - y_1)*(x_2 - x_1);
//            float pr3 = (x_1 - x1)*(y2 - y1) - (y_1 - y1)*(x2 - x1);
//            float pr4 = (x_2 - x1)*(y2 - y1) - (y_2 - y1)*(x2 - x1);
//            return pr1 * pr2 <= 0 && pr3 * pr4 <= 0;
//        }
//
//        bool is_point_into_figure(Point point) {
//            return is_point_into_figure(point.get_raw_x(), point.get_raw_y());
//        }
//        bool is_point_into_figure(shared_ptr<Point> point) {
//            return is_point_into_figure(point->get_raw_x(), point->get_raw_y());
//        }
//        bool is_point_into_figure(float x, float y){
//
//            if (complex_figure.size() > 1){
//                bool result = false;
//                for (auto figure: complex_figure){
//                    result = result || figure->is_point_into_figure(x, y);
//                    if (result) return result;
//                }
//                return result;
//            } else {
//                int local_counter = 0;
//                // TODO: сделать условие, что длинна должна быть больше 2-х
//                auto first_point = points_with_line.back();
//                for (auto second_point: points_with_line){
//                     if (is_2_lines(x, y, -10, y, first_point->get_raw_x(), first_point->get_raw_y(),
//                                                  second_point->get_raw_x(), second_point->get_raw_y())){
//                        local_counter++;
//                    }
//                    first_point->draw_line(*second_point);
//                    first_point = second_point;
//                }
//
//                for (auto point: points_no_line){
//                    if (point->get_x() == (int)x && point->get_y() == (int)y) return true;
//                }
//                return local_counter % 2 != 0;
//            }
//
//        }





        void renderer(int canvas, int difference_between_times, int x_size, int y_size){
            if (BaseFigure::left_button_pressed && (!user_move_not_me || user_move_me)){
//                if (!is_point_into_figure(my_get_mouse_x(canvas), my_get_mouse_y(canvas))) user_move_not_me = true;
//                else user_move_me = true;
//                static float last_position_x = my_get_mouse_x(canvas);
//                static float last_position_y = my_get_mouse_y(canvas);
//                static float new_position_x;
//                static float new_position_y;
//                new_position_x = my_get_mouse_x(canvas);
//                new_position_y = my_get_mouse_y(canvas);
//                move_figure(new_position_x - last_position_x, new_position_y - last_position_y);
//                last_position_x = new_position_x;
//                last_position_y = new_position_y;

            } else {
                if (user_move_not_me && !BaseFigure::left_button_pressed) {
                    user_move_not_me = false;
                    user_move_me = false;
                }

                speed_x = norm_speed_x * difference_between_times * 0.001;
                speed_y = norm_speed_y * difference_between_times * 0.001;
                speed_rotation = norm_speed_rotation * difference_between_times * 0.001;
                move_figure(speed_x, speed_y);
                auto [center_x, center_y, rotation_point_x, rotation_point_y] = border_regulate(x_size, y_size);
                rotation_figure(center_x, center_y, rotation_point_x, rotation_point_y);
            }
            draw();
        }

        void reboot_radius(){
            if (complex_figure.size() > 1){
                for (auto figure: complex_figure){
                    figure->reboot_radius();
                }
            } else {
                for (auto point: points_with_line){
                    point->reboot_radius();
                }
                for (auto point: points_no_line){
                    point->reboot_radius();
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
            this->reboot_radius();
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
            new_figure.reboot_radius();
            return new_figure;
        }

};
bool BaseFigure::left_button_pressed = false;


bool event_processing(int canvas){
    static list<int> exit_list = {81, 113, -1};
    auto [ev_type, ev_code] = get_event(canvas);
    if (ev_type == 1){
        // Событие клавиатуры
        bool exit = false;
        for (auto i: exit_list) exit |= i;
        if (exit) {
            exit_console_python(canvas);
            return true;
        }
    } else if (ev_type == 2) {
        // Событие мыши
        if (ev_code == 1) { // Нажате левая клавиша мыши
            BaseFigure::left_button_pressed = true;
        } else {
            BaseFigure::left_button_pressed = false;
        }
    }
    return false;
}


int main(){

   const int delay = 50;  // плановый интервал между обновлениями
   int canvas = new_start_python();  // create_canvas(0, 0);
   int x = get_console_x_size_python(canvas);
   int y = get_console_y_size_python(canvas);
   uint64_t current_time = current_timestamp();  // текущее время
   uint64_t update_time = current_time + delay; // плановое время обновления
   uint64_t last_time_update = current_time;  // прошлое время обновления
   int difference_between_times; // действительная разница между временем обноаления и текущем временем

//   print_class(my_obj);
    BaseFigure one(canvas, { Point(canvas,5,5), Point(canvas,5,40),Point(canvas, 40,40),Point(canvas,40,5) });
    BaseFigure line(canvas, { Point(canvas,10,20), Point(canvas,50,10) });

//    BaseFigure line(canvas, { Point(canvas,x - 1,0), Point(canvas,x - 1,y - 1)});
//    BaseFigure line2(canvas, { Point(canvas,0,y - 1), Point(canvas,x - 1,y - 1)});
//    BaseFigure line2(canvas, { Point(canvas,10,10), Point(canvas,10,50)});
//    BaseFigure one_1(canvas, { Point(canvas,50,20), Point(canvas,50,50),Point(canvas,75,70),Point(canvas,100,50),Point(canvas,100,20) });
    BaseFigure one_3(canvas, { Point(canvas,50,10), Point(canvas,70,30),Point(canvas,90,10)});

//    BaseFigure one_4 = one + one_1 + one_3;
//    one_4.draw();

//    one.draw();
//
//    one_1.draw();
//
//    one_3.draw();
    int counter = 0, render_counter = 0;
    while (true){
        current_time = current_timestamp();
        if (update_time <= current_time){
//            cout<<update_time - last_time_update<<" "<<difference_between_times<<"\n";
            difference_between_times = current_time - last_time_update;
            last_time_update = current_time; // update_time;
            update_time = current_time + delay;

            one.renderer(canvas, difference_between_times, x, y);
            line.renderer(canvas, difference_between_times, x, y);
            one_3.renderer(canvas, difference_between_times, x, y);

            if (BaseFigure::left_button_pressed){
                new_draw_line_python(canvas, my_get_mouse_x(canvas)-1, my_get_mouse_y(canvas)-1,
                                             my_get_mouse_x(canvas)+1, my_get_mouse_y(canvas)+1);
                cout<<my_get_mouse_x(canvas)<<" "<<my_get_mouse_y(canvas)<<"\n";

            }
            new_renderer_python(canvas);  // refresh_python(canvas);

            render_counter++;
        }
        if (event_processing(canvas)){
            break;
        }
        counter++;
    }
    cout<<x<<" "<<y<<"\n";
    cout<<counter<<" "<<render_counter<<"\n";




//    getch();
    return 0;
}

// g++ BaseFigure1_test.cpp -o main.exe -std=c++17
