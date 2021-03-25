# from ctypes import *
# 
# lib = cdll.LoadLibrary(r"D:\programs\jobs\coursework1\create_dll_lib\python_graphics.dll")
# lib.my_python_print()



def new_start_python(canvas_id: int = None):
    global obj_dict, counter

    try:
        screen = Screen.open(None,
                             catch_interrupt=False,
                             unicode_aware=None)
        counter += 1
        obj_dict[canvas_id or counter] = screen

        scenes = []

        effects = [
            Print(screen,
                  MyNiceLire(screen.height, screen.width, screen.colours, bg=screen.colours >= 256),
                  0,
                  speed=1,
                  transparent=False),
        ]
        scenes.append(Scene(effects, 100))
        screen.start_play(scenes, stop_on_resize=True)
        screen.no_while_play(stop_on_resize=True)

    except StopApplication:
        return canvas_id or counter
    return canvas_id or counter


def new_renderer(canvas_id: int):
    try:
        obj_dict[canvas_id].no_while_play(stop_on_resize=True)
    except ResizeScreenError:
        new_start_python(canvas_id)


# def demo(screen):
#     scenes = []
#
#     effects = [
#         Print(screen,
#               MyNiceLire(screen.height, screen.width, screen.colours, bg=screen.colours >= 256),
#               0,
#               speed=1,
#               transparent=False),
#     ]
#     scenes.append(Scene(effects, 100))
#     screen.play(scenes, stop_on_resize=True)
#
#
# if __name__ == "__main__":
#
#     while True:
#         try:
#             Screen.wrapper(demo)
#             sys.exit(0)
#         except ResizeScreenError:
#             pass
