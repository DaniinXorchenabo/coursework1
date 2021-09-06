# -*- coding: utf-8 -*-

import cffi, _cffi_backend


# from asciimatics.effects import Cycle, Stars
# from asciimatics.renderers import FigletText
# from asciimatics.scene import Scene
# from asciimatics.screen import Screen
import asciimatics
import os


PATH = os.getcwd()
lib_path = asciimatics.__file__
ffi = cffi.FFI()

ffi.embedding_api(open("python_graphics.h").read())

ffi.embedding_init_code(str(open("graphic_lib.py", 'r', encoding='utf-8').read()))

ffi.set_source("python_graphics", "")


dll_libs = ['python_graphics.dll', "python_graphics.so"]
for lib in dll_libs:
    ffi.compile(verbose=True, target=lib)
ffi.compile(verbose=True)


from os.path import join, split, isfile
from shutil import copyfile, move


# lib_remove_path = join(split(split(__file__)[0])[0], 'done')
# remove_files = dll_libs  # 'python_graphics.h',
# new_path_files = [join(lib_remove_path, i) for i in remove_files]
# remove_files = [join(split(__file__)[0], i) for i in remove_files]
# # try:
# #     [move(old, new) for old, new in zip(remove_files, new_path_files) if isfile(old)]
# # except Exception:
# #     pass
# lib_remove_path = join(split(__file__)[0], 'Release')
# remove_files = ['python_graphics.c']  # 'python_graphics.h',
# new_path_files = [join(lib_remove_path, i) for i in remove_files]
# remove_files = [join(split(__file__)[0], i) for i in remove_files]
# [move(old, new) for old, new in zip(remove_files, new_path_files)]

