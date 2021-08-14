#ifndef NEW_IMPORT_PYTHON_FUNC_H
#define NEW_IMPORT_PYTHON_FUNC_H
#include <list>
#include <iterator>
#include <memory>
#include <iostream>
//#include <conio.h>
#include <chrono>
#include <cmath>
#include <random>

typedef void (*VoidReturnFunc)();

typedef void (*VoidReturnFunc1int)(int);

typedef int (*intReturnFunc)();

typedef int (*intReturnFunc1int)(int);

typedef int (*intReturnFunc2int)(int, int);

typedef void (*VoidReturnFunc3int)(int, int, int);

typedef void (*VoidReturnFunc5int)(int, int, int, int, int);

typedef void (*VoidReturnFunc1int4float)(int, float, float, float, float);

typedef bool (*BoolReturnFunc1int)(int);

typedef float (*FloatReturnFunc1int)(int);

#ifdef __linux__

#include <dlfcn.h>


#else

#include <windows.h>


#endif

intReturnFunc1int init_console;
intReturnFunc1int print_class;

intReturnFunc1int get_event_type;
intReturnFunc1int get_event_code;

intReturnFunc1int get_console_x_size_python;
intReturnFunc1int get_console_y_size_python;

FloatReturnFunc1int my_get_mouse_x;
FloatReturnFunc1int my_get_mouse_y;

intReturnFunc2int create_canvas;
VoidReturnFunc3int draw_point_python;
VoidReturnFunc1int4float draw_line_python;
VoidReturnFunc1int refresh_python;
VoidReturnFunc1int exit_console_python;
BoolReturnFunc1int check_exit_button_python;
intReturnFunc new_start_python;
VoidReturnFunc1int new_renderer_python;
VoidReturnFunc1int4float new_draw_line_python;

#endif