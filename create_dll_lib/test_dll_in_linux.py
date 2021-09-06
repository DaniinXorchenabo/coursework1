import os
from time import sleep
from ctypes import  cdll
path_to_lib = "".join([(os.getcwd()), ("/python_graphics.so")])
lib = cdll.LoadLibrary(path_to_lib)
canvas = 0
height = -2
weight = -3
ev = -34
ev1=-309093
e = "not error"
ex="not error 2"
try:
    print(lib)
    # print(lib.my_python_print())
    print(path_to_lib)
    ((canvas:=lib.new_start_python()))
    ((weight:=lib.get_console_x_size_python(canvas)))
    ((height:=lib.get_console_y_size_python(canvas)))
    ((lib.new_renderer_python(canvas)))
    ((lib.new_draw_line_python(canvas, 10,10, 20,20)))
    ((lib.new_draw_line_python(canvas, 30,30, 10,40)))
    ((ev:=lib.get_event_type(canvas)))
    ((ev1:=lib.get_event_code(canvas)))
    ((lib.new_renderer_python(canvas)))
    sleep(1)
    # print((ev:=lib.get_event_type(canvas)))
    # print((ev1:=lib.get_event_code(canvas)))

    ((exit:=lib.exit_console_python(canvas)))
except Exception as e:
    try:
        ((exit:=lib.exit_console_python(canvas)))
        print(e)
    except Exception as ex:
        print("""krbtr""", ex)

print(canvas,weight,height, ev, ev1, [e], [ex])