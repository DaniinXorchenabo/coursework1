#include <list>
#include <iterator>
#include <memory>
#include <iostream>
//#include <windows.h>
//#include <conio.h>
#include <chrono>
#include <cmath>
#include <random>
#include "headers/utils.h"
#include "headers/import_python_func.h"


uint64_t current_timestamp() {
    // copy paste with https://habr.com/ru/post/537682/
    return std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::steady_clock::now().time_since_epoch()
    ).count();
}

std::pair<int, int> get_event(int canvas) {
    int ev = get_event_type(canvas);
    if (ev != 0) {
        return {ev, get_event_code(canvas)};
    }
    return {0, 0};
}