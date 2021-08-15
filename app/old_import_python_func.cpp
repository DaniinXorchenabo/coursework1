#ifndef IMPORT_PYTHON_FUNC_H
#define IMPORT_PYTHON_FUNC_H
#include <list>
#include <iterator>
#include <memory>
#include <iostream>
//#include <conio.h>
#include <chrono>
#include <cmath>
#include <random>
#include "import_python_func.h"



#ifdef __linux__

#include <dlfcn.h>


void* a = dlopen("python_graphics.so", RTLD_NOW); //  | RTLD_LOCAL

intReturnFunc1int create_obj = (intReturnFunc1int) dlsym(a, "create_obj");
intReturnFunc1int print_class = (intReturnFunc1int) dlsym(a, "print_class");


intReturnFunc1int get_event_type = (intReturnFunc1int) dlsym(a, "get_event_type");

intReturnFunc1int get_event_code = (intReturnFunc1int) dlsym(a, "get_event_code");


intReturnFunc1int get_console_x_size_python = (intReturnFunc1int) dlsym(a, "get_console_x_size_python");

intReturnFunc1int get_console_y_size_python = (intReturnFunc1int) dlsym(a, "get_console_y_size_python");


FloatReturnFunc1int get_mouse_x = (FloatReturnFunc1int) dlsym(a, "get_mouse_x");

FloatReturnFunc1int get_mouse_y = (FloatReturnFunc1int) dlsym(a, "get_mouse_y");


intReturnFunc2int create_canvas = (intReturnFunc2int) dlsym(a, "create_canvas");

VoidReturnFunc3int draw_point_python = (VoidReturnFunc3int) dlsym(a, "draw_point_python");

VoidReturnFunc1int4float draw_line_python = (VoidReturnFunc1int4float) dlsym(a, "draw_line_python");

VoidReturnFunc1int refresh_python = (VoidReturnFunc1int) dlsym(a, "refresh_python");

VoidReturnFunc1int exit_console_python = (VoidReturnFunc1int) dlsym(a, "exit_console_python");

BoolReturnFunc1int check_exit_button_python = (BoolReturnFunc1int) dlsym(a, "check_exit_button_python");

intReturnFunc new_start_python = (intReturnFunc) dlsym(a, "new_start_python");

VoidReturnFunc1int new_renderer_python = (VoidReturnFunc1int) dlsym(a, "new_renderer_python");


VoidReturnFunc1int4float new_draw_line_python = (VoidReturnFunc1int4float) dlsym(a, "new_draw_line_python");

//dlclose(a);
void check_imports(){
//    std::cout<<"Фунеция проверки импортов";
//    std::cout<<"Фунеция проверки импортов";
//    if (!a){
//    std::cout<<"Динамическая либа не обнаружена -.-";
//    dlclose(a);
//    }
//    if (!create_obj) {
//    std::cout<<"Функция create_obj не найдена";
//    dlclose(a);
//}
//    if (!print_class) {
//    std::cout<<"Функция print_class не найдена";
//    dlclose(a);
//}
//    if (!get_event_type) {
//    std::cout<<"Функция get_event_type не найдена";
//    dlclose(a);
//}
//    if (!get_event_code) {
//    std::cout<<"Функция get_event_code не найдена";
//    dlclose(a);
//}
//    if (!get_console_x_size_python) {
//    std::cout<<"Функция get_event_get_console_x_size_pythoncode не найдена";
//    dlclose(a);
//}
//    if (!get_console_y_size_python) {
//    std::cout<<"Функция get_console_y_size_python не найдена";
//    dlclose(a);
//}
//    if (!get_mouse_x) {
//    std::cout<<"Функция get_mouse_x не найдена";
//    dlclose(a);
//}
//    if (!get_mouse_y) {
//    std::cout<<"Функция get_mouse_y не найдена";
//    dlclose(a);
//}
//    if (!create_canvas) {
//    std::cout<<"Функция create_canvas не найдена";
//    dlclose(a);
//}
//    if (!draw_point_python) {
//    std::cout<<"Функция draw_point_python не найдена";
//    dlclose(a);
//}
//    if (!draw_line_python) {
//    std::cout<<"Функция draw_line_python не найдена";
//    dlclose(a);
//}
//    if (!refresh_python) {
//    std::cout<<"Функция refresh_python не найдена";
//    dlclose(a);
//}
//    if (!exit_console_python) {
//    std::cout<<"Функция exit_console_python не найдена";
//    dlclose(a);
//}
//    if (!check_exit_button_python) {
//    std::cout<<"Функция check_exit_button_python не найдена";
//    dlclose(a);
//}
//    if (!new_start_python) {
//    std::cout<<"Функция new_start_python не найдена";
//    dlclose(a);
//}
//    if (!new_renderer_python) {
//    std::cout<<"Функция new_renderer_python не найдена";
//    dlclose(a);
//}
//
//if (!new_draw_line_python) {
//    std::cout<<"Функция new_draw_line_python не найдена";
//    dlclose(a);
//}
}
#else

#include <windows.h>

//HINSTANCE a;
//   VoidReturnFunc myFunc;
//
//   intReturnFunc1int create_obj;
//   intReturnFunc1int print_class;
//
//   intReturnFunc1int get_event_type;
//   intReturnFunc1int get_event_code;
//   intReturnFunc1int get_console_x_size_python;
//   intReturnFunc1int get_console_y_size_python;
//
//   FloatReturnFunc1int get_mouse_x;
//   FloatReturnFunc1int get_mouse_y;
//
//   intReturnFunc2int create_canvas;
//   VoidReturnFunc3int draw_point_python;
//   VoidReturnFunc1int4float draw_line_python;
//   VoidReturnFunc1int refresh_python;
//   VoidReturnFunc1int exit_console_python;
//   BoolReturnFunc1int check_exit_button_python;
//
//   intReturnFunc new_start_python;
//   VoidReturnFunc1int new_renderer_python;
//   VoidReturnFunc1int4float new_draw_line_python;

HINSTANCE a = LoadLibrary("python_graphics.dll");

//   intReturnFunc1int create_obj, print_class;
//   VoidReturnFunc3int draw_point_python;
//   VoidReturnFunc5int draw_line_python;

intReturnFunc1int create_obj = (intReturnFunc1int) GetProcAddress(a, "create_obj");
intReturnFunc1int print_class = (intReturnFunc1int) GetProcAddress(a, "print_class");

intReturnFunc1int get_event_type = (intReturnFunc1int) GetProcAddress(a, "get_event_type");
intReturnFunc1int get_event_code = (intReturnFunc1int) GetProcAddress(a, "get_event_code");

intReturnFunc1int get_console_x_size_python = (intReturnFunc1int) GetProcAddress(a, "get_console_x_size_python");
intReturnFunc1int get_console_y_size_python = (intReturnFunc1int) GetProcAddress(a, "get_console_y_size_python");

FloatReturnFunc1int get_mouse_x = (FloatReturnFunc1int) GetProcAddress(a, "get_mouse_x");
FloatReturnFunc1int get_mouse_y = (FloatReturnFunc1int) GetProcAddress(a, "get_mouse_y");

intReturnFunc2int create_canvas = (intReturnFunc2int) GetProcAddress(a, "create_canvas");
VoidReturnFunc3int draw_point_python = (VoidReturnFunc3int) GetProcAddress(a, "draw_point_python");
VoidReturnFunc1int4float draw_line_python = (VoidReturnFunc1int4float) GetProcAddress(a, "draw_line_python");
VoidReturnFunc1int refresh_python = (VoidReturnFunc1int) GetProcAddress(a, "refresh_python");
VoidReturnFunc1int exit_console_python = (VoidReturnFunc1int) GetProcAddress(a, "exit_console_python");
BoolReturnFunc1int check_exit_button_python = (BoolReturnFunc1int) GetProcAddress(a, "check_exit_button_python");

intReturnFunc new_start_python = (intReturnFunc) GetProcAddress(a, "new_start_python");
VoidReturnFunc1int new_renderer_python = (VoidReturnFunc1int) GetProcAddress(a, "new_renderer_python");
VoidReturnFunc1int4float new_draw_line_python = (VoidReturnFunc1int4float) GetProcAddress(a, "new_draw_line_python");

void check_imports(){
//    std::cout<<"check imports func";
}

#endif


#endif