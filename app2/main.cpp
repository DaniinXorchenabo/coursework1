#include <list>
#include <iterator>
#include <memory>
#include <iostream>
#include <windows.h>
#include <conio.h>
#include <chrono>
#include <cmath>
#include <random>

#include "utils.cpp"
#include "Point.cpp"
#include "BaseFigure.cpp"
#include "headers/import_python_func.h"
#include "console.cpp"

using namespace std;


int main(){

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



    while (true){
        if (this_console.renderer(canvas)) break;
    }

    return 0;
}

// g++ BaseFigure1_test.cpp -o main.exe -std=c++17
