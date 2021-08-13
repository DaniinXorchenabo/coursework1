#include <list>
#include <iterator>
#include <memory>
#include <iostream>
//#include <windows.h>
//#include <conio.h>
#include <chrono>
#include <cmath>
#include <random>
#include "utils.h"
//#include "import_python_func.h"
#include "Point.h"
#include "BaseFigure.h"

#ifndef CONSOLE_H
#define CONSOLE_H

using namespace std;

class ConsoleRenderer {
private:
    float mouse_pos_x = -1, mouse_pos_y = -1;
    float last_mouse_pos_x = -1, last_mouse_pos_y = -1;
    int delay = 50;  // плановый интервал между обновлениями
    float weight, height;

    uint64_t current_time;  // текущее время
    uint64_t update_time; // плановое время обновления
    uint64_t last_time_update;  // прошлое время обновления
    // действительная разница между временем обноаления и текущем временем
    int difference_between_times;

public:
    list <shared_ptr<BaseFigure>> rendering_figures = {};

    ConsoleRenderer();

    ConsoleRenderer(int canvas);

    ConsoleRenderer(int canvas, int set_delay);

    bool renderer(int canvas);

    void add_figure(shared_ptr <BaseFigure> figure);

    void add_figure(BaseFigure &figure);

    bool event_processing(int canvas);

    ConsoleRenderer &operator+=(const BaseFigure &figure) {
        rendering_figures.push_back(make_shared<BaseFigure>(figure));
        return *this;

    }

    ConsoleRenderer &operator+=(const shared_ptr <BaseFigure> figure) {
        rendering_figures.push_back(figure);
        return *this;

    }

};


#endif