#include <list>
#include <iterator>
#include <memory>
#include <iostream>
//#include <windows.h>
//#include <conio.h>
#include <chrono>
#include <cmath>
#include <random>

#include "utils.cpp"
#include "Point.cpp"
#include "BaseFigure.cpp"
#include "headers/import_python_func.h"
#include "console.cpp"

using namespace std;

int main() {
    cout<<"some string\n";
    int canvas = new_start_python();
    ConsoleRenderer this_console(canvas);
    this_console += BaseFigure(canvas, {
        Point(canvas,5,5),
        Point(canvas,5,30),
        Point(canvas, 30,30),
        Point(canvas,30,5)
    });
    this_console += BaseFigure(canvas, {
        Point(canvas,65,10),
        Point(canvas,50,10)
    });
    this_console += BaseFigure(canvas, {
        Point(canvas,50,40),
        Point(canvas,70,50),
        Point(canvas,90,10)
    });
    this_console += BaseFigure(canvas, {
            Point(canvas, 10, 10),
            Point(canvas, 30, 10),
            Point(canvas, 30, 30)
    });
    this_console += BaseFigure(canvas, {
            Point(canvas, 50, 50),
            Point(canvas, 80, 50),
            Point(canvas, 80, 80)
    });

    while (true) { if (this_console.renderer(canvas)) break; }

//    #ifdef __linux__
//    dlclose(a);
//    #endif

    return 0;
}

// g++ BaseFigure1_test.cpp -o main.exe -std=c++17
