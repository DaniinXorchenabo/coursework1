

#include <list>
#include <iterator>
#include <memory>
#include <iostream>
#include <windows.h>
#include <conio.h>
#include <chrono>
#include <cmath>
#include <random>
#include "headers/import_python_func.h"
#include "headers/Point.h"

using namespace std;


        int Point::get_canvas() const {
            return canvas;
        }
        float Point::get_raw_x() const {
            return x;
        }

        float Point::get_raw_y() const {
            return y;
        }

        void Point::reboot_radius() {
            radius = -1;
        }

        int Point::get_x() const {
            return (int)x;
        }
        int Point::get_y() const {
            return (int)y;
        }

        bool Point::border_control(int max_x, int max_y){
            // Вернет true, если точка находится в пределах экрана
            return x >= 0 && y >= 0 && x <= max_x && y <= max_y;
        }

        pair<float, float> Point::get_polar_coord(float c_x, float c_y){
            float r_y = y - c_y;
            float r_x = x - c_x;
            if (radius == -1){
                radius = sqrt(r_x * r_x + r_y * r_y);
            }
            return {radius, atan2(r_y, r_x)};
        }

        pair<float, float> Point::get_change_polar_coord(float r, float angle, float c_x, float c_y){
            return {r * cos(angle) + c_x - x, r * sin(angle) + c_y - y};
        }

        void Point::set_polar_coord(float r, float angle, float c_x, float c_y){
            x = r * cos(angle) + c_x;
            y = r * sin(angle) + c_y;
        }

        void Point::move_point(float add_x, float add_y){
            x += add_x;
            y += add_y;
        }
        void Point::set_coord(float new_x, float new_y){
            x = new_x;
            y = new_y;
        }

        Point::Point(){
            x = 0;
            y = 0;
        }

        Point::Point(int my_canvas, int s_x, int s_y){
            canvas = my_canvas;
            x = s_x;
            y = s_y;
        }

        Point::Point (const Point& copy){
            canvas = copy.get_canvas();
            x = copy.get_raw_x();
            y = copy.get_raw_y();
        }

        tuple<shared_ptr<Point>, shared_ptr<Point>, shared_ptr<Point>, shared_ptr<Point>>
            Point::get_extreme_points(tuple<shared_ptr<Point>, shared_ptr<Point>, shared_ptr<Point>, shared_ptr<Point>> data){
            auto [max_x, max_y, min_x, min_y] = data;
            if (max_x->get_raw_x() <= x) max_x = make_shared<Point>(*this);
            if (max_y->get_raw_y() <= y) max_y = make_shared<Point>(*this);
            if (min_x->get_raw_x() >= x) min_x = make_shared<Point>(*this);
            if (min_y->get_raw_y() >= y) min_y = make_shared<Point>(*this);
            return {max_x, max_y, min_x, min_y};
        }

        void Point::draw(){
            cout<<"Draw point";
            cout<<get_x();
            cout<<", ";
            cout<<get_y()<<endl;
//            draw_point_python(canvas, x, y);
        }
        void Point::draw_line(Point& point){
            new_draw_line_python(canvas, x, y, point.get_raw_x(), point.get_raw_y());
//            draw_line_python(canvas, x, y, point.get_raw_x(), point.get_raw_y());
        }

