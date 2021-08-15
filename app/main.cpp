#include <list>
#include <iterator>
#include <memory>
#include <iostream>
//#include <windows.h>
//#include <conio.h>
#include <chrono>
#include <cmath>
#include <random>

#include "headers/python_graphics.h"
#include "utils.cpp"
#include "Point.cpp"
#include "BaseFigure.cpp"
#include "headers/import_python_func.h"
#include "import_python_func.cpp"
#include "console.cpp"

using namespace std;

int main() {
//    cout<<"some string--\n";
//    import_dll();
//    cout<<"some string\n";
//    my_python_print();

    int canvas = new_start_python();
//    cout<<"some string\n";
    ConsoleRenderer this_console(canvas);
//    cout<<"some string\n";
    this_console += BaseFigure(canvas, {
        Point(canvas,5,5),
        Point(canvas,5,30),
        Point(canvas, 30,30),
        Point(canvas,30,5)
    });
//    cout<<"some string\n";
//    this_console += BaseFigure(canvas, {
//        Point(canvas,65,10),
//        Point(canvas,50,10)
//    });
//    cout<<"some string\n";
    this_console += BaseFigure(canvas, {
        Point(canvas,50,40),
        Point(canvas,70,50),
        Point(canvas,90,10)
    });
//    cout<<"some string\n";
//    this_console += BaseFigure(canvas, {
//            Point(canvas, 10, 10),
//            Point(canvas, 30, 10),
//            Point(canvas, 30, 30)
//    });
//    cout<<"some string\n";
    this_console += BaseFigure(canvas, {
            Point(canvas, 50, 50),
            Point(canvas, 80, 50),
            Point(canvas, 80, 80)
    });
//    cout<<"some string\n";
    while (true) {
//        cout<<"some pre-while\n";
        if (this_console.renderer(canvas)) {
//            cout<<"exiting from while\n";
            break;
        }
//        cout<<"some post-while\n";
    }
//    cout<<"end while\n";

//    #ifdef __linux__
//    dlclose(a);
//    #endif

    return 0;
}

// g++ BaseFigure1_test.cpp -o main.exe -std=c++17



//#include <iostream>
//#include "headers/python_graphics.h"
//using namespace std;
//int main()
//{
//    cout<<"start\n";
//    my_python_print();
//    cout<<"end\n";
//}