#pragma once
#include "point.h"
#include <list>
#include <vector>
#include <iterator>

class Figure{
    public:
        std::list<Point> points;
        std::vector<int> center { 0, 0 };

        Figure();
        Figure(const std::list<Point> &);

        void muve_up(int, int);
        void set_x(int);
        void set_y(int);
        void set_posiition(int, int);
        std::vector<int> get_center();
        int return_32();

};

