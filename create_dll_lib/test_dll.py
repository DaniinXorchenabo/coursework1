# from ctypes import *
#
# lib = cdll.LoadLibrary(r"D:\programs\jobs\coursework1\app\tests\my_library.dll")
# lib.my_python_print()

#!/usr/bin/env python3

# from __future__ import division
from asciimatics.effects import Cycle, Stars
from asciimatics.renderers import FigletText
from asciimatics.scene import Scene
from asciimatics.screen import Screen
from asciimatics.renderers import *
import PIL
print(PIL.__file__)

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


# Screen.wrapper(demo)