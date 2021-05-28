#include <list>
#include <iterator>
#include <memory>
#include <iostream>
#include <windows.h>
#include <conio.h>
#include <chrono>
#include <cmath>
#include <random>
#include "headers/utils.h"
#include "headers/import_python_func.h"
#include "headers/Point.h"
#include "headers/BaseFigure.h"

// =======! Конструкторы !=======
BaseFigure::BaseFigure() {}

BaseFigure::BaseFigure(int my_canvas) { canvas = my_canvas; }

BaseFigure::BaseFigure(int my_canvas, initializer_list <Point> points) {
    /* Вызов BaseFigure(my_canvas, p1, p2, p3}) */
    canvas = my_canvas;
    for (auto iter : points) {
        points_with_line.push_back(make_shared<Point>(iter));
    }
    norm_speed_x = BaseFigure::get_random_speed();
    norm_speed_y = BaseFigure::get_random_speed();
    norm_speed_rotation = BaseFigure::get_random_rotation_speed();
}

BaseFigure::BaseFigure(int my_canvas, int coordinates, ...) {
    canvas = my_canvas;
    for (auto coordinate = &coordinates; *coordinate; coordinate++) {
        points_with_line.push_back(make_shared<Point>(canvas, *coordinate, *(++coordinate)));
    }
    norm_speed_x = BaseFigure::get_random_speed();
    norm_speed_y = BaseFigure::get_random_speed();
    norm_speed_rotation = BaseFigure::get_random_rotation_speed();
}

BaseFigure::BaseFigure(const BaseFigure &figure_material) {
    canvas = figure_material.get_canvas();
    points_no_line = figure_material.points_no_line;
    points_with_line = figure_material.points_with_line;
    complex_figure = figure_material.complex_figure;
    norm_speed_x = figure_material.norm_speed_x;
    norm_speed_y = figure_material.norm_speed_y;
    norm_speed_rotation = figure_material.norm_speed_rotation;
}

// =======! Геттеры !=======
int BaseFigure::get_canvas() const { return canvas; }

tuple<float, float, int> BaseFigure::get_raw_center_point() {
    float x = 0, y = 0;
    int counter = 0;
    if (complex_figure.size() > 1) {
        for (auto figure: complex_figure) {
            auto[new_x, new_y, new_counter] = figure->get_raw_center_point();
            x += new_x;
            y += new_y;
            counter += new_counter;
        }
    } else {
        for (auto point: points_with_line) {
            x += point->get_raw_x();
            y += point->get_raw_y();
            ++counter;
        }
        if (counter == 0) {
            for (auto point: points_no_line) {
                x += point->get_raw_x();
                y += point->get_raw_y();
                ++counter;
            }
        }
    }
    return {x, y, counter};
}

pair<float, float> BaseFigure::get_center_point() {
    float x = 0, y = 0;
    int counter = 0;
    if (complex_figure.size() > 1) {
        for (auto figure: complex_figure) {
            auto[new_x, new_y, new_counter] = figure->get_raw_center_point();
            x += new_x;
            y += new_y;
            counter += new_counter;
        }
    } else {
        for (auto point: points_with_line) {
            x += point->get_raw_x();
            y += point->get_raw_y();
            counter++;
        }
        if (counter == 0) {
            for (auto point: points_no_line) {
                x += point->get_raw_x();
                y += point->get_raw_y();
                counter++;
            }
        }
    }
    return {x / counter, y / counter};
}

tuple <shared_ptr<Point>, shared_ptr<Point>,
shared_ptr<Point>, shared_ptr<Point>>
BaseFigure::get_extreme_points() {
    auto max_x = make_shared<Point>(0, -1000, 0);
    auto max_y = make_shared<Point>(0, 0, -1000);
    auto min_x = make_shared<Point>(0, 10000, 0);
    auto min_y = make_shared<Point>(0, 0, 10000);
//            return {max_x, max_y, min_x, min_y};
    return get_extreme_points({max_x, max_y, min_x, min_y});
}

tuple <shared_ptr<Point>, shared_ptr<Point>,
shared_ptr<Point>, shared_ptr<Point>>
BaseFigure::get_extreme_points(tuple
                               <shared_ptr<Point>,
                               shared_ptr<Point>,
                               shared_ptr<Point>,
                               shared_ptr<Point>> data) {
    if (complex_figure.size() > 1) {
        for (auto figure: complex_figure) {
            data = figure->get_extreme_points(data);
        }
    } else {
        for (auto point: points_no_line) {
            data = point->get_extreme_points(data);

        }
        for (auto point: points_with_line) {
            data = point->get_extreme_points(data);

        }
    }
    return data;
}

list <shared_ptr<Point>> BaseFigure::get_all_points_with_line() {
    list <shared_ptr<Point>> all_points = {};
    if (complex_figure.size() > 1) {
        for (auto figure: complex_figure) {
            all_points.merge(figure->get_all_points_with_line());
        }
    } else {
        if (points_with_line.size() > 0) {
            for (auto point: points_with_line) {
                all_points.push_back(point);
            }
        } else {
            for (auto point: points_no_line) {
                all_points.push_back(point);
            }
        }
    }
    return all_points;
}

list <shared_ptr<Point>> BaseFigure::get_all_points() {
    list <shared_ptr<Point>> all_points = {};
    if (complex_figure.size() > 1) {
        for (auto figure: complex_figure) {
            all_points.merge(figure->get_all_points());
        }
    } else {
        for (auto point: points_with_line) {
            all_points.push_back(point);
        }

        for (auto point: points_no_line) {
            all_points.push_back(point);
        }

    }
    return all_points;
}


// =======! Сеттеры !=======
void BaseFigure::set_speed(float new_x, float new_y, float new_rotation) {
    norm_speed_x = new_x;
    norm_speed_y = new_y;
    norm_speed_rotation = new_rotation;
    speed_x = 0;
    speed_y = 0;
    speed_rotation = 0;
}

bool BaseFigure::is_complex_figure() { return complex_figure.empty(); }


// =======! Перемещение фигуры !=======
void BaseFigure::move_figure() { move_figure(speed_x, speed_y); }

void BaseFigure::move_figure(float add_x, float add_y) {
    if (complex_figure.size() > 1) {
        for (auto figure: complex_figure) {
            figure->move_figure(add_x, add_y);
        }
    } else {
        for (auto point: points_no_line) {
            point->move_point(add_x, add_y);

        }
        for (auto point: points_with_line) {
            point->move_point(add_x, add_y);

        }
    }
}


// =======! Поворот фигуры !=======
pair<float, float> BaseFigure::rotation_figure() {
    auto[center_x, center_y] = get_center_point();
    rotation_figure(center_x, center_y, center_x, center_y);
    return {center_x, center_y};
}

pair<float, float> BaseFigure::rotation_figure(float center_x, float center_y) {
    rotation_figure(center_x, center_y, center_x, center_y);
    return {center_x, center_y};
}

pair<float, float> BaseFigure::rotation_figure(float center_x, float center_y,
                                               float rotation_point_x, float rotation_point_y) {

    auto all_points = get_all_points();
    for (auto point: all_points) {
        if (rotation_point_x != center_x || rotation_point_y != center_y) point->reboot_radius();
        auto[r, angle] = point->get_polar_coord(rotation_point_x, rotation_point_y);
        angle += speed_rotation;
        point->set_polar_coord(r, angle, rotation_point_x, rotation_point_y);
        if (rotation_point_x != center_x || rotation_point_y != center_y) point->reboot_radius();
    }


    return {center_x, center_y};
}

void BaseFigure::reboot_radius() {
    if (complex_figure.size() > 1) {
        for (auto figure: complex_figure) {
            figure->reboot_radius();
        }
    } else {
        for (auto point: points_with_line) {
            point->reboot_radius();
        }
        for (auto point: points_no_line) {
            point->reboot_radius();
        }
    }
}


// =======! Проверка выхода за границы консоли !=======
tuple<float, float, float, float>
BaseFigure::border_regulate(int x_size, int y_size,
                            float center_x, float center_y) {
    auto[max_x, max_y, min_x, min_y] = get_extreme_points();
    if (x_size <= max_x->get_raw_x() && norm_speed_x > 0) norm_speed_x *= -1;
    if (y_size <= max_y->get_raw_y() && norm_speed_y > 0) norm_speed_y *= -1;
    if (0 >= min_x->get_raw_x() && norm_speed_x < 0) norm_speed_x *= -1;
    if (0 >= min_y->get_raw_y() && norm_speed_y < 0) norm_speed_y *= -1;

    auto[max_x_r, max_x_angle] = max_x->get_polar_coord(center_x, center_y);
    auto[dx, useless_dy] = max_x->get_change_polar_coord(max_x_r, max_x_angle + speed_rotation, center_x, center_y);
    auto[max_y_r, max_y_angle] = max_y->get_polar_coord(center_x, center_y);
    auto[useless_dx, dy] = max_y->get_change_polar_coord(max_y_r, max_y_angle + speed_rotation, center_x, center_y);

    auto[mim_x_r, min_x_angle] = min_x->get_polar_coord(center_x, center_y);
    auto[min_dx, useless_dy1] = min_x->get_change_polar_coord(mim_x_r, min_x_angle + speed_rotation, center_x,
                                                              center_y);
    auto[min_y_r, min_y_angle] = min_y->get_polar_coord(center_x, center_y);
    auto[useless_dx1, min_dy] = min_y->get_change_polar_coord(min_y_r, min_y_angle + speed_rotation, center_x,
                                                              center_y);

    auto rotation_point_x = center_x;
    auto rotation_point_y = center_y;
    if (x_size <= max_x->get_raw_x() && dx > 0) {
//                speed_rotation *= -1;
        rotation_point_x = max_x->get_raw_x();
        rotation_point_y = max_x->get_raw_y();
    } else if (y_size <= max_y->get_raw_y() && dy > 0) {
//                speed_rotation *= -1;
        rotation_point_x = max_y->get_raw_x();
        rotation_point_y = max_y->get_raw_y();
    } else if (0 >= min_x->get_raw_x() && min_dx < 0) {
//                speed_rotation *= -1;
        rotation_point_x = min_x->get_raw_x();
        rotation_point_y = min_x->get_raw_y();
    } else if (0 >= min_y->get_raw_y() && min_dy < 0) {
//                speed_rotation *= -1;
        rotation_point_x = min_y->get_raw_x();
        rotation_point_y = min_y->get_raw_y();
    }
    return {center_x, center_y, rotation_point_x, rotation_point_y};

}

tuple<float, float, float, float>
BaseFigure::border_regulate(int x_size, int y_size) {
    auto[center_x, center_y] = get_center_point();
    return border_regulate(x_size, y_size, center_x, center_y);
}


// =======! Пересечение фигур и точек !=======
bool BaseFigure::is_2_lines(float x_1, float y_1, float x_2, float y_2,
                            float x1, float y1, float x2, float y2) {
    // Вернёт true если 2 отрезка пересекаются
    float pr1 = (x1 - x_1) * (y_2 - y_1) - (y1 - y_1) * (x_2 - x_1);
    float pr2 = (x2 - x_1) * (y_2 - y_1) - (y2 - y_1) * (x_2 - x_1);
    float pr3 = (x_1 - x1) * (y2 - y1) - (y_1 - y1) * (x2 - x1);
    float pr4 = (x_2 - x1) * (y2 - y1) - (y_2 - y1) * (x2 - x1);
    return pr1 * pr2 <= 0 && pr3 * pr4 <= 0;
}

bool BaseFigure::is_point_into_figure(Point point) {
    return is_point_into_figure(point.get_raw_x(), point.get_raw_y());
}

bool BaseFigure::is_point_into_figure(shared_ptr <Point> point) {
    return is_point_into_figure(point->get_raw_x(), point->get_raw_y());
}

bool BaseFigure::is_point_into_figure(float x, float y) {

    if (complex_figure.size() > 1) {
        bool result = false;
        for (auto figure: complex_figure) {
            result = result || figure->is_point_into_figure(x, y);
            if (result) return result;
        }
        return result;
    } else {
        int local_counter = 0;
        if (points_with_line.size() > 1) {
            auto first_point = points_with_line.back();
            for (auto second_point: points_with_line) {
                if (is_2_lines(x, y, -10, y, first_point->get_raw_x(), first_point->get_raw_y(),
                               second_point->get_raw_x(), second_point->get_raw_y())) {
                    local_counter++;
                }
                first_point = second_point;
            }
        }

        for (auto point: points_no_line) {
            if (point->get_x() == (int) x && point->get_y() == (int) y) return true;
        }
        return local_counter % 2 != 0;
    }

}


bool BaseFigure::intersection_of_figures(shared_ptr <BaseFigure> figure) {
    bool result = false;
    for (auto point: figure->get_all_points_with_line()) {
        result = result || is_point_into_figure(point);
        if (result) { return result; }
    }
    return result;
}


// =======! Отрисовка фигур !=======
void BaseFigure::renderer(int canvas, int difference_between_times,
                          int x_size, int y_size,
                          float mouse_pos_x, float mouse_pos_y,
                          float last_position_x, float last_position_y) {
    if (is_active) {
        if (BaseFigure::left_button_pressed && (user_move_me_status == 0 || user_move_me_status == 2)) {
            if (user_move_me_status == 0) {
                if (is_point_into_figure(mouse_pos_x, mouse_pos_y)) user_move_me_status = 2;
                else user_move_me_status = 1;
            }
            if (user_move_me_status == 2) {
                float new_position_x = mouse_pos_x;
                float new_position_y = mouse_pos_y;
                move_figure(new_position_x - last_position_x, new_position_y - last_position_y);
            }
        } else {
            if (user_move_me_status != 0 && !BaseFigure::left_button_pressed) {
                user_move_me_status = 0;
            }

            speed_x = norm_speed_x * difference_between_times * 0.001;
            speed_y = norm_speed_y * difference_between_times * 0.001;
            speed_rotation = norm_speed_rotation * difference_between_times * 0.001;
            move_figure(speed_x, speed_y);
            auto[center_x, center_y, rotation_point_x, rotation_point_y] = border_regulate(x_size, y_size);
            rotation_figure(center_x, center_y, rotation_point_x, rotation_point_y);
        }
        draw();
    }
}

void BaseFigure::draw() {
    if (complex_figure.size() > 1) {
        for (auto figure: complex_figure) {
            figure->draw();
        }
    } else {
        if (points_with_line.size() > 1) {
            auto first_point = points_with_line.back();
            for (auto second_point: points_with_line) {
                first_point->draw_line(*second_point);
                first_point = second_point;
            }
        }
        for (auto point: points_no_line) {
            point->draw();
        }
    }
}


// =======! Добавление одной фигуры в другую !=======
void BaseFigure::add_figure(shared_ptr <BaseFigure> other_figure) {
    if (complex_figure.empty() && other_figure->complex_figure.empty()) {
        complex_figure.push_back(make_shared<BaseFigure>(*this));
        complex_figure.back()->set_speed(0, 0, 0);
        complex_figure.back()->is_active = false;
        complex_figure.push_back(other_figure);
        complex_figure.back()->set_speed(0, 0, 0);
        complex_figure.back()->is_active = false;
        points_with_line = {};
        points_no_line = {};

    } else if (!complex_figure.empty() && other_figure->complex_figure.empty()) {
        complex_figure.push_back(other_figure);
        complex_figure.back()->set_speed(0, 0, 0);
        complex_figure.back()->is_active = false;
    } else if (complex_figure.empty() && !other_figure->complex_figure.empty()) {
        complex_figure = other_figure->complex_figure;
        complex_figure.push_front(make_shared<BaseFigure>(*this));
        complex_figure.front()->set_speed(0, 0, 0);
        complex_figure.front()->is_active = false;
        points_with_line = {};
        points_no_line = {};

    } else if (!complex_figure.empty() && !other_figure->complex_figure.empty()) {
//                complex_figure += other_figure.complex_figure;
//                complex_figure.merge(other_figure.complex_figure);
        auto a = other_figure->complex_figure;
        complex_figure.merge(a);
    }
//    norm_speed_rotation = 0;
//    other_figure->set_speed(0, 0, 0);
    other_figure->is_active = false;
//    set_speed(0, 0, 0);
    reboot_radius();
    //    this->reboot_radius();
}

bool BaseFigure::left_button_pressed = false;