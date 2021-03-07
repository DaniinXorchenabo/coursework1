#pragma once

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