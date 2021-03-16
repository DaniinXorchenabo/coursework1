""""Этот """


from python_graphics import ffi, lib

import sys
import os


sys.path.insert(0, r"C:\Users\Acer\AppData\Local\Programs\Python\python38_cv2\Python38\lib\site-packages")
# sys.path = [i for i in sys.path if 'anaconda' not in i]

os.environ['PYTHONHOME'] = r'C:\Users\Acer\AppData\Local\Programs\Python\python38_cv2\Python38'
os.environ['PYTHONPATH'] = r'C:\Users\Acer\AppData\Local\Programs\Python\python38_cv2\Python38'

# sys.path.append(r"C:\Users\Acer\AppData\Local\Programs\Python\python38_cv2\Python38\lib\site-packages\PIL")
from asciimatics.effects import Cycle, Stars
from asciimatics.renderers import FigletText
from asciimatics.scene import Scene
from asciimatics.screen import Screen
from asciimatics import event


obj_dict = {}
counter = 0


class ConsoleClass:

    def __init__(self, int_from_c):
        self.int_from_c = int_from_c

    def print_cl(self):
        print('__88**77', self.int_from_c)


@ffi.def_extern()
def compute(first: float, second: float) -> float:
    return abs(first - second)


# class TestClass:
#     def __init__(self):
#         pass
#
#     def print(self):
#         print('&&666---------------111111')


@ffi.def_extern()
def create_obj(data: int) -> int:
    global counter, obj_dict
    counter += 1
    obj_dict[counter] = ConsoleClass(data)
    return counter


@ffi.def_extern()
def print_class(number: int) -> int:
    global obj_dict
    obj_dict[number].print_cl()
    return 0


@ffi.def_extern()
def my_python_print() -> int:
    # from __future__ import division
    from asciimatics.effects import Cycle, Stars
    from asciimatics.renderers import FigletText
    from asciimatics.scene import Scene
    from asciimatics.screen import Screen

    def demo(screen):
        effects = [
            Cycle(
                screen,
                FigletText("ASCIIMATICS", font='big'),
                screen.height // 2 - 8),
            Cycle(
                screen,
                FigletText("ROCKS!", font='big'),
                screen.height // 2 + 3),
            Stars(screen, (screen.width + screen.height) // 2)
        ]
        screen.play([Scene(effects, 500)])

    Screen.wrapper(demo)
    # import math
    # print(math.sin(5))
    # import sys
    #
    # print(sys.executable)
    return 7


@ffi.def_extern()
def draw_point_python(canvas: int, x: float, y: float):
    print(f'рисую на канвасе {canvas} точку (x = {int(x)}, y = {int(y)})')




@ffi.def_extern()
def draw_line_python(canvas: int, x1: float, y1: float, x2: float, y2: float):
    y2 = y2 * 0.5723297
    y1 = y1 * 0.5723297
    obj_dict[canvas].move(x1, y1)
    obj_dict[canvas].draw(x2, y2)
    # print(round(x1), round(y1), round(x2), round(y2))


@ffi.def_extern()
def create_canvas(h=None, weight=None) -> int:
    screen = Screen.open(None,
                         catch_interrupt=False,
                         unicode_aware=None)

    print(screen.height, screen.width)
    from time import sleep

    sleep(10)
    # restore = True
    # try:
    #     try:
    #         return func(screen)
    #     except ResizeScreenError:
    #         restore = False
    #         raise
    # finally:
    #     screen.close(restore)

    global obj_dict, counter
    if h and weight:
        print(f'создаю канвас размерами высота = {h}, ширина = {weight}')
    else:
        print('оспользую открытую консоль')
    counter += 1
    obj_dict[counter] = screen

    return counter


@ffi.def_extern()
def refresh_python(canvas: int):
    obj_dict[canvas].refresh()
    obj_dict[canvas].clear_buffer(Screen.COLOUR_WHITE, 0, Screen.COLOUR_BLACK)


@ffi.def_extern()
def exit_console_python(canvas: int):
    obj_dict[canvas].close()


@ffi.def_extern()
def check_exit_button_python(canvas: int) -> bool:
    ev = obj_dict[canvas].get_event()
    return type(ev) == event.KeyboardEvent and ev.key_code in [81, 113, -1]


@ffi.def_extern()
def get_console_x_size_python(canvas: int):
    return obj_dict[canvas].width


@ffi.def_extern()
def get_console_y_size_python(canvas: int):
    return int(obj_dict[canvas].height / 0.5723297)


