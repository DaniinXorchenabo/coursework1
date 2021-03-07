from asciimatics.screen import Screen
from time import sleep
from asciimatics import event


def demo(screen):
    screen.print_at('Hello world!', 0, 0)

    # screen.clear_buffer()
    screen.move(0, 0)

    screen.draw(50, 30, thin=True)
    screen.fill_polygon([[(60, 0), (70, 0), (70, 10), (60, 10)],
                         [(63, 2), (67, 2), (67, 8), (63, 8)]])
    screen.refresh()
    screen.clear_buffer(Screen.COLOUR_WHITE, 0, Screen.COLOUR_BLACK)
    screen.print_at('Hello world!', 20, 20)
    sleep(5)
    screen.refresh()
    sleep(5)
    a = screen.get_event()
    # print([type(a), dir(a), a, type(a) == event.KeyboardEvent and a.key_code])

Screen.wrapper(demo)

print('----------')
