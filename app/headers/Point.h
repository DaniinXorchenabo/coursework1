#ifndef POINT_H
#define POINT_H

#include <list>
#include <iterator>
#include <memory>
#include <iostream>
//#include <windows.h>
//#include <conio.h>
#include <chrono>
#include <cmath>
#include <random>
#include "import_python_func.h"
#include "utils.h"

using namespace std;

class Point {

protected:
    float x, y, radius = -1;
    int canvas;

public:
    int get_x() const;

    int get_y() const;

    int get_canvas() const;

    float get_raw_x() const;

    float get_raw_y() const;

    bool border_control(int max_x, int max_y);

    pair<float, float> get_polar_coord(float c_x, float c_y);

    pair<float, float> get_change_polar_coord(float r, float angle, float c_x, float c_y);

    void reboot_radius();

    void set_coord(float new_x, float new_y);

    void set_polar_coord(float r, float angle, float c_x, float c_y);

    Point();

    Point(int my_canvas, int s_x, int s_y);

    Point(const Point &copy);

    tuple <shared_ptr<Point>, shared_ptr<Point>, shared_ptr<Point>, shared_ptr<Point>>
    get_extreme_points(tuple <shared_ptr<Point>, shared_ptr<Point>,
                       shared_ptr<Point>, shared_ptr<Point>> data);

    void draw();

    void draw_line(Point &point);

    void move_point(float add_x, float add_y);
};

#endif