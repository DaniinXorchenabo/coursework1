#ifdef NEW__IMPORT_PYTHON_FUNC_H
#define NEW__IMPORT_PYTHON_FUNC_H

#include "headers/import_python_func.h"

#ifdef __linux__
#include <dlfcn.h>

void import_dll(){

    //    std::cout<<"try:\n";
//    std::cout<<new_start_python()<<"\n";
//    std::cout<<"try finished\n";

}

//    void* a = dlopen("/python_graphics.so", RTLD_NOW | RTLD_LOCAL); //
//    create_obj = (intReturnFunc1int) dlsym(a, "create_obj");
//    print_class = (intReturnFunc1int) dlsym(a, "print_class");
//    get_event_type = (intReturnFunc1int) dlsym(a, "get_event_type");
//    get_event_code = (intReturnFunc1int) dlsym(a, "get_event_code");
//    get_console_x_size_python = (intReturnFunc1int) dlsym(a, "get_console_x_size_python");
//    get_console_y_size_python = (intReturnFunc1int) dlsym(a, "get_console_y_size_python");
//    get_mouse_x = (FloatReturnFunc1int) dlsym(a, "get_mouse_x");
//    get_mouse_y = (FloatReturnFunc1int) dlsym(a, "get_mouse_y");
//    create_canvas = (intReturnFunc2int) dlsym(a, "create_canvas");
//    draw_point_python = (VoidReturnFunc3int) dlsym(a, "draw_point_python");
//    draw_line_python = (VoidReturnFunc1int4float) dlsym(a, "draw_line_python");
//    refresh_python = (VoidReturnFunc1int) dlsym(a, "refresh_python");
//    exit_console_python = (VoidReturnFunc1int) dlsym(a, "exit_console_python");
//    check_exit_button_python = (BoolReturnFunc1int) dlsym(a, "check_exit_button_python");
//    new_start_python = (intReturnFunc) dlsym(a, "new_start_python");
//    new_renderer_python = (VoidReturnFunc1int) dlsym(a, "new_renderer_python");
//    new_draw_line_python = (VoidReturnFunc1int4float) dlsym(a, "new_draw_line_python");


//    void* a = dlopen("/python_graphics.so", RTLD_NOW | RTLD_LOCAL); //
//    intReturnFunc1int create_obj = (intReturnFunc1int) dlsym(a, "create_obj");
//    intReturnFunc1int print_class = (intReturnFunc1int) dlsym(a, "print_class");
//    intReturnFunc1int get_event_type = (intReturnFunc1int) dlsym(a, "get_event_type");
//    intReturnFunc1int get_event_code = (intReturnFunc1int) dlsym(a, "get_event_code");
//    intReturnFunc1int get_console_x_size_python = (intReturnFunc1int) dlsym(a, "get_console_x_size_python");
//    intReturnFunc1int get_console_y_size_python = (intReturnFunc1int) dlsym(a, "get_console_y_size_python");
//    FloatReturnFunc1int get_mouse_x = (FloatReturnFunc1int) dlsym(a, "get_mouse_x");
//    FloatReturnFunc1int get_mouse_y = (FloatReturnFunc1int) dlsym(a, "get_mouse_y");
//    intReturnFunc2int create_canvas = (intReturnFunc2int) dlsym(a, "create_canvas");
//    VoidReturnFunc3int draw_point_python = (VoidReturnFunc3int) dlsym(a, "draw_point_python");
//    VoidReturnFunc1int4float draw_line_python = (VoidReturnFunc1int4float) dlsym(a, "draw_line_python");
//    VoidReturnFunc1int refresh_python = (VoidReturnFunc1int) dlsym(a, "refresh_python");
//    VoidReturnFunc1int exit_console_python = (VoidReturnFunc1int) dlsym(a, "exit_console_python");
//    BoolReturnFunc1int check_exit_button_python = (BoolReturnFunc1int) dlsym(a, "check_exit_button_python");
//    intReturnFunc new_start_python = (intReturnFunc) dlsym(a, "new_start_python");
//    VoidReturnFunc1int new_renderer_python = (VoidReturnFunc1int) dlsym(a, "new_renderer_python");
//    VoidReturnFunc1int4float new_draw_line_python = (VoidReturnFunc1int4float) dlsym(a, "new_draw_line_python");

#else

#include <windows.h>
void import_dll() {

//    HINSTANCE a = LoadLibrary("python_graphics.dll");
//
//    create_obj = (intReturnFunc1int) GetProcAddress(a, "create_obj");
//    print_class = (intReturnFunc1int) GetProcAddress(a, "print_class");
//
//    get_event_type = (intReturnFunc1int) GetProcAddress(a, "get_event_type");
//    get_event_code = (intReturnFunc1int) GetProcAddress(a, "get_event_code");
//
//    get_console_x_size_python = (intReturnFunc1int) GetProcAddress(a, "get_console_x_size_python");
//    get_console_y_size_python = (intReturnFunc1int) GetProcAddress(a, "get_console_y_size_python");
//
//    get_mouse_x = (FloatReturnFunc1int) GetProcAddress(a, "get_mouse_x");
//    get_mouse_y = (FloatReturnFunc1int) GetProcAddress(a, "get_mouse_y");
//
//    create_canvas = (intReturnFunc2int) GetProcAddress(a, "create_canvas");
//    draw_point_python = (VoidReturnFunc3int) GetProcAddress(a, "draw_point_python");
//    draw_line_python = (VoidReturnFunc1int4float) GetProcAddress(a, "draw_line_python");
//    refresh_python = (VoidReturnFunc1int) GetProcAddress(a, "refresh_python");
//    exit_console_python = (VoidReturnFunc1int) GetProcAddress(a, "exit_console_python");
//    check_exit_button_python = (BoolReturnFunc1int) GetProcAddress(a, "check_exit_button_python");
//
//    new_start_python = (intReturnFunc) GetProcAddress(a, "new_start_python");
//    new_renderer_python = (VoidReturnFunc1int) GetProcAddress(a, "new_renderer_python");
//    new_draw_line_python = (VoidReturnFunc1int4float) GetProcAddress(a,
                                                                                              "new_draw_line_python");
}

#endif

#endif