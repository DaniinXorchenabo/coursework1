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
#include "headers/console.h"

bool ConsoleRenderer::renderer(int canvas) {
    current_time = current_timestamp();
    if (update_time <= current_time) {

        difference_between_times = current_time - last_time_update;
        last_time_update = current_time;
        update_time = current_time + delay;
        mouse_pos_x = my_get_mouse_x(canvas);
        mouse_pos_y = my_get_mouse_y(canvas);

        rendering_figures = BaseFigure::sum_figures(rendering_figures);

        for (auto figure: rendering_figures) {
            figure->renderer(canvas, difference_between_times, weight, height,
                             mouse_pos_x, mouse_pos_y,
                             last_mouse_pos_x, last_mouse_pos_y);
        }

//        if (BaseFigure::left_button_pressed){
//            new_draw_line_python(canvas, my_get_mouse_x(canvas)-1, my_get_mouse_y(canvas)-1,
//                                 my_get_mouse_x(canvas)+1, my_get_mouse_y(canvas)+1);
//            cout<<my_get_mouse_x(canvas)<<" "<<my_get_mouse_y(canvas)<<"\n";
//
//        }

        last_mouse_pos_x = mouse_pos_x;
        last_mouse_pos_y = mouse_pos_y;
        new_renderer_python(canvas);

    }
    if (event_processing(canvas)) {
        return true;
    }
    return false;
}

ConsoleRenderer::ConsoleRenderer() {}

ConsoleRenderer::ConsoleRenderer(int canvas) {

    weight = get_console_x_size_python(canvas);
    height = get_console_y_size_python(canvas);

    current_time = current_timestamp();  // текущее время
    update_time = current_time + delay; // плановое время обновления
    last_time_update = current_time;  // прошлое время обновления

}

ConsoleRenderer::ConsoleRenderer(int canvas, int set_delay) {

    weight = get_console_x_size_python(canvas);
    height = get_console_y_size_python(canvas);
    delay = set_delay;

    current_time = current_timestamp();  // текущее время
    update_time = current_time + delay; // плановое время обновления
    last_time_update = current_time;  // прошлое время обновления


}

bool ConsoleRenderer::event_processing(int canvas) {
    static list<int> exit_list = {81, 113, -1};
    auto[ev_type, ev_code] = get_event(canvas);
    if (ev_type == 1) {
        // Событие клавиатуры
        bool exit = false;
        for (auto i: exit_list) exit |= i;
        if (exit) {
            exit_console_python(canvas);
            return true;
        }
    } else if (ev_type == 2) {
        // Событие мыши
        if (ev_code == 1) { // Нажате левая клавиша мыши
            BaseFigure::left_button_pressed = true;
        } else {
            BaseFigure::left_button_pressed = false;
        }
    }
    return false;
}

void ConsoleRenderer::add_figure(shared_ptr <BaseFigure> figure) {
    rendering_figures.push_back(figure);
}

void ConsoleRenderer::add_figure(BaseFigure &figure) {
    rendering_figures.push_back(make_shared<BaseFigure>(figure));
}