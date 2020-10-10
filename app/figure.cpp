#pragma once
#include "figure.h"
#include "point.h"


Figure::Figure(const std::list<Point> &init_points){
    points = init_points;
    int count = 0;
    for (auto it = points.begin(); it != points.end(); ++it, ++count) {
        center[0] += it->get_x();
        center[1] += it->get_y();
    }
    if (count != 0) {
        center = std::vector<int>{center[0]/count, center[1]/count};
    }

}

void Figure::muve_up(int setup_x, int setup_y){
    for (auto it = points.begin(); it != points.end(); ++it) {
        it->muve_up(setup_x, setup_y);
    }
}
void Figure::set_x(int new_x){
    muve_up(new_x - center[0], 0);
    center[0] = new_x;
}
void Figure::set_y(int new_y){
    muve_up(0, new_y - center[1]);
    center[1] = new_y;
}
void Figure::set_posiition(int new_x, int new_y){
    muve_up(new_x - center[0], new_y - center[1]);
    center = std::vector<int>{new_x, new_y};
}
std::vector<int> Figure::get_center(){
    return center;
}

int Figure:: return_32(){
    return 32;
}