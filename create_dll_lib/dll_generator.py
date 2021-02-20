# -*- coding: utf-8 -*-

import cffi, _cffi_backend


# from asciimatics.effects import Cycle, Stars
# from asciimatics.renderers import FigletText
# from asciimatics.scene import Scene
# from asciimatics.screen import Screen
import asciimatics
import sys
import os


PATH = os.getcwd()
# sys.path.append(asciimatics.__file__)
lib_path = asciimatics.__file__
print(*sys.path, os.path.split(asciimatics.__file__)[0] , sep='\n')
print(_cffi_backend)
print(sys.builtin_module_names)
ffi = cffi.FFI()

ffi.embedding_api(open("python_graphics.h").read())

ffi.embedding_init_code(str(open("dll_lib_code.py", 'r', encoding='utf-8').read()))

ffi.set_source("python_graphics", "")
ffi.compile(verbose=True)