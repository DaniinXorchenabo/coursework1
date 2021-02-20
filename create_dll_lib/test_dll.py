from ctypes import *

lib = cdll.LoadLibrary(r"D:\programs\jobs\coursework1\create_dll_lib\python_graphics.dll")
lib.my_python_print()