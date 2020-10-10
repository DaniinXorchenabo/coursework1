#pragma once
#include "point.h"


Point::Point(int x_start, int y_start){
    x = (float)x_start;
    y = (float)y_start;
}

void Point::muve_up(float x_start, float y_start){
    x += x_start;
    y += y_start;
}

void Point::muve_up(int x_serup, int y_serup){
    x += (float)x_serup;
    y += (float)y_serup;
}

int Point::get_x(){
    return (int)x;
}

int Point::get_y(){
    return (int)y;
}

void Point::set_x(int new_x){
    x = (float)new_x;
}

void Point::set_y(int new_y){
    y = (float)new_y;
}

void Point::set_point(int new_x, int new_y){
    x = (float)new_x;
    y = (float)new_y;
}

void Point::set_x(float new_x){
    x = new_x;
}

void Point::set_y(float new_y){
    y = new_y;
}

void Point::set_point(float new_x, float new_y){
        x = new_x;
        y = new_y;
}