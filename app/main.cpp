#include <iostream>
// #pragma once
#include "point.h"
#include "figure.h"
#include <list>
#include <vector>
#include <iterator>


using namespace std;

int main()
{
    Point point1(1, 2);
    Figure test_figure(list<Point>{Point(1,2)});
    std::cout << "Hi!" << std::endl;
    std::cout << test_figure.return_32() << std::endl;
    std::cout << point1.get_x() << " " << point1.get_y()<< std::endl;
    return 0;
}