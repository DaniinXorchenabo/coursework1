//#ifndef NEW_IMPORT_PYTHON_FUNC_H
//#define NEW_IMPORT_PYTHON_FUNC_H
//extern "C" {
////#include <list>
////
////
////#include <iterator>
////#include <memory>
////#include <iostream>
//////#include <conio.h>
////#include <chrono>
////#include <cmath>
////#include <random>
//
//typedef void (*VoidReturnFunc)();
//
//typedef void (*VoidReturnFunc1int)(int);
//
//typedef int (*intReturnFunc)();
//
//typedef int (*intReturnFunc1int)(int);
//
//typedef int (*intReturnFunc2int)(int, int);
//
//typedef void (*VoidReturnFunc3int)(int, int, int);
//
//typedef void (*VoidReturnFunc5int)(int, int, int, int, int);
//
//typedef void (*VoidReturnFunc1int4float)(int, float, float, float, float);
//
//typedef bool (*BoolReturnFunc1int)(int);
//
//typedef float (*FloatReturnFunc1int)(int);
//
//#ifdef __linux__
//
//#include <dlfcn.h>
//
//void* a = dlopen("/python_graphics.so", RTLD_NOW | RTLD_LOCAL); //
//intReturnFunc1int create_obj = (intReturnFunc1int) dlsym(a, "create_obj");
//intReturnFunc1int print_class = (intReturnFunc1int) dlsym(a, "print_class");
//intReturnFunc1int get_event_type = (intReturnFunc1int) dlsym(a, "get_event_type");
//intReturnFunc1int get_event_code = (intReturnFunc1int) dlsym(a, "get_event_code");
//intReturnFunc1int get_console_x_size_python = (intReturnFunc1int) dlsym(a, "get_console_x_size_python");
//intReturnFunc1int get_console_y_size_python = (intReturnFunc1int) dlsym(a, "get_console_y_size_python");
//FloatReturnFunc1int get_mouse_x = (FloatReturnFunc1int) dlsym(a, "get_mouse_x");
//FloatReturnFunc1int get_mouse_y = (FloatReturnFunc1int) dlsym(a, "get_mouse_y");
//intReturnFunc2int create_canvas = (intReturnFunc2int) dlsym(a, "create_canvas");
//VoidReturnFunc3int draw_point_python = (VoidReturnFunc3int) dlsym(a, "draw_point_python");
//VoidReturnFunc1int4float draw_line_python = (VoidReturnFunc1int4float) dlsym(a, "draw_line_python");
//VoidReturnFunc1int refresh_python = (VoidReturnFunc1int) dlsym(a, "refresh_python");
//VoidReturnFunc1int exit_console_python = (VoidReturnFunc1int) dlsym(a, "exit_console_python");
//BoolReturnFunc1int check_exit_button_python = (BoolReturnFunc1int) dlsym(a, "check_exit_button_python");
//intReturnFunc new_start_python = (intReturnFunc) dlsym(a, "new_start_python");
//VoidReturnFunc1int new_renderer_python = (VoidReturnFunc1int) dlsym(a, "new_renderer_python");
//VoidReturnFunc1int4float new_draw_line_python = (VoidReturnFunc1int4float) dlsym(a, "new_draw_line_python");
//VoidReturnFunc my_python_print = (VoidReturnFunc) dlsym(a, "my_python_print");
//
//#else
//
//#include <windows.h>
//
//HINSTANCE a = LoadLibrary("python_graphics.dll");
//
//intReturnFunc1int create_obj = (intReturnFunc1int) GetProcAddress(a, "create_obj");
//intReturnFunc1int print_class = (intReturnFunc1int) GetProcAddress(a, "print_class");
//
//intReturnFunc1int get_event_type = (intReturnFunc1int) GetProcAddress(a, "get_event_type");
//intReturnFunc1int get_event_code = (intReturnFunc1int) GetProcAddress(a, "get_event_code");
//
//intReturnFunc1int get_console_x_size_python = (intReturnFunc1int) GetProcAddress(a, "get_console_x_size_python");
//intReturnFunc1int get_console_y_size_python = (intReturnFunc1int) GetProcAddress(a, "get_console_y_size_python");
//
//FloatReturnFunc1int get_mouse_x = (FloatReturnFunc1int) GetProcAddress(a, "get_mouse_x");
//FloatReturnFunc1int get_mouse_y = (FloatReturnFunc1int) GetProcAddress(a, "get_mouse_y");
//
//intReturnFunc2int create_canvas = (intReturnFunc2int) GetProcAddress(a, "create_canvas");
//VoidReturnFunc3int draw_point_python = (VoidReturnFunc3int) GetProcAddress(a, "draw_point_python");
//VoidReturnFunc1int4float draw_line_python = (VoidReturnFunc1int4float) GetProcAddress(a, "draw_line_python");
//VoidReturnFunc1int refresh_python = (VoidReturnFunc1int) GetProcAddress(a, "refresh_python");
//VoidReturnFunc1int exit_console_python = (VoidReturnFunc1int) GetProcAddress(a, "exit_console_python");
//BoolReturnFunc1int check_exit_button_python = (BoolReturnFunc1int) GetProcAddress(a, "check_exit_button_python");
//
//intReturnFunc new_start_python = (intReturnFunc) GetProcAddress(a, "new_start_python");
//VoidReturnFunc1int new_renderer_python = (VoidReturnFunc1int) GetProcAddress(a, "new_renderer_python");
//VoidReturnFunc1int4float new_draw_line_python = (VoidReturnFunc1int4float) GetProcAddress(a, "new_draw_line_python");
//VoidReturnFunc my_python_print = (VoidReturnFunc) GetProcAddress(a, "my_python_print");
//
//
//#endif
//}
////intReturnFunc1int create_obj;
////intReturnFunc1int print_class;
////
////intReturnFunc1int get_event_type;
////intReturnFunc1int get_event_code;
////
////intReturnFunc1int get_console_x_size_python;
////intReturnFunc1int get_console_y_size_python;
////
////FloatReturnFunc1int get_mouse_x;
////FloatReturnFunc1int get_mouse_y;
////
////intReturnFunc2int create_canvas;
////VoidReturnFunc3int draw_point_python;
////VoidReturnFunc1int4float draw_line_python;
////VoidReturnFunc1int refresh_python;
////VoidReturnFunc1int exit_console_python;
////BoolReturnFunc1int check_exit_button_python;
////intReturnFunc new_start_python;
////VoidReturnFunc1int new_renderer_python;
////VoidReturnFunc1int4float new_draw_line_python;
//
//#endif