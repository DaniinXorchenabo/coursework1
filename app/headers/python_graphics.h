

#ifndef PYTHON_GRAPHICS_H
#define PYTHON_GRAPHICS_H
//#pragma onse
extern "C" {


float compute(float first, float second);

int my_python_print();

int create_obj(int);

int print_class(int);

//void draw_point_python(int, float, float);
void draw_point_python(int, int, int);
void draw_line_python(int, float, float, float, float);
//void draw_line_python(int, int, int, int, int);

//int create_canvas();
int create_canvas(int, int);

void refresh_python(int);
void exit_console_python(int);
bool check_exit_button_python(int);
int get_event_type(int);
int get_event_code(int);
float get_mouse_x(int);
float get_mouse_y(int);

int get_console_x_size_python(int);
int get_console_y_size_python(int);

int new_start_python();
void new_renderer_python(int);
void new_draw_line_python(int, float, float, float, float);
}
#endif
