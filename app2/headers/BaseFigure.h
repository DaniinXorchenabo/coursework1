#include <list>
#include <iterator>
#include <memory>
#include <iostream>
#include <windows.h>
#include <conio.h>
#include <chrono>
#include <cmath>
#include <random>
#include "utils.h"
#include "import_python_func.h"
#include "Point.h"

#ifndef BASE_FIGURE_H
#define BASE_FIGURE_H


const float MAX_SPEED = 4;
const float MAX_ROTATION_SPEED = 0.3;

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
        int user_move_me_status = 0;    // 0 - клавиша не нажата, (или нажата, но проверка еще не проводилась)
                                        // 1 - клавиша нажата, проверка проведена, перемещают не меня
                                        // 2 - клавиша нажата, перемещают меня


        bool is_complex_figure();

        int get_canvas() const ;

        tuple<float, float, int> get_raw_center_point();

        pair<float, float> get_center_point();

        BaseFigure();

        BaseFigure(int my_canvas);

        BaseFigure(int my_canvas, initializer_list<Point> points);

        BaseFigure(int my_canvas, int coordinates, ...);

        BaseFigure (const BaseFigure& figure_material);

        void draw();

        void move_figure();
        void move_figure(float add_x, float add_y);

        pair<float, float> rotation_figure();

        pair<float, float> rotation_figure(float center_x, float center_y);
        pair<float, float> rotation_figure(float center_x, float center_y,
                                           float rotation_point_x, float rotation_point_y);


        tuple<shared_ptr<Point>, shared_ptr<Point>, shared_ptr<Point>, shared_ptr<Point>>
            get_extreme_points();

        tuple<shared_ptr<Point>, shared_ptr<Point>, shared_ptr<Point>, shared_ptr<Point>>
            get_extreme_points(tuple<shared_ptr<Point>, shared_ptr<Point>, shared_ptr<Point>, shared_ptr<Point>> data);



        tuple<float, float, float, float> border_regulate(int x_size, int y_size, float center_x, float center_y);
        tuple<float, float, float, float> border_regulate(int x_size, int y_size);

        bool is_2_lines(float x_1, float y_1, float x_2, float y_2, float x1, float y1, float x2, float y2);

        bool is_point_into_figure(Point point);
        bool is_point_into_figure(shared_ptr<Point> point);
        bool is_point_into_figure(float x, float y);

        void renderer(int canvas, int difference_between_times, int x_size, int y_size, float last_position_x, float last_position_y);

        void reboot_radius();

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

#endif