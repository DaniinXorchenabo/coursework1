""""Этот """


from my_library import ffi, lib

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