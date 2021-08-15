#include <list>
#include <iterator>
#include <memory>
#include <iostream>
#include "python_graphics.h"
//#include <windows.h>
//#include <conio.h>
#include <chrono>
#include <cmath>
#include <random>

#ifndef UTILS_H
#define UTILS_H

uint64_t current_timestamp();

std::pair<int, int> get_event(int canvas);

#endif