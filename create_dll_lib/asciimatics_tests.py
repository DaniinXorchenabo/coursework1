from asciimatics.screen import Screen
from time import sleep
from asciimatics import event
from asciimatics.event import KeyboardEvent, MouseEvent

import win32con
import win32console
import win32event
import win32file
import pywintypes

from itertools import cycle
from time import sleep
import copy
import sys
from random import randint, random
from typing import Tuple

from asciimatics.effects import Print
from asciimatics.renderers import DynamicRenderer
from asciimatics.scene import Scene
from asciimatics.screen import Screen
from asciimatics.exceptions import ResizeScreenError, StopApplication


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
    while True:
        ev = screen.get_event()
        if type(ev) == event.KeyboardEvent and ev.key_code in [81, 113, -1]:
            break
        if type(ev) == event.MouseEvent:
            print(ev.buttons, ev.x, ev.y)
    screen.refresh()
    a = screen.get_event()
    # print([type(a), dir(a), a, type(a) == event.KeyboardEvent and a.key_code])


# Screen.wrapper(demo)


def start_play(self, scenes, stop_on_resize=False, unhandled_input=None,
               start_scene=None, repeat=True, allow_int=False):
    # Initialise the Screen for animation.
    self.set_scenes(
        scenes, unhandled_input=unhandled_input, start_scene=start_scene)


def no_while_play(self, stop_on_resize=False, unhandled_input=None,
                  start_scene=None, repeat=True, allow_int=False):
    try:
        self.draw_next_frame(repeat=repeat)
        if self.has_resized():
            if stop_on_resize:
                self._scenes[self._scene_index].exit()
                raise ResizeScreenError("Screen resized",
                                        self._scenes[self._scene_index])
    except StopApplication:
        # Time to stop  - just exit the function.
        return


def my_get_event(self):
    """
    Check for any event without waiting.
    """
    # Look for a new event and consume it if there is one.
    while len(self._stdin.PeekConsoleInput(1)) > 0:
        event = self._stdin.ReadConsoleInput(1)[0]
        if event.EventType == win32console.KEY_EVENT:
            # Pasting unicode text appears to just generate key-up
            # events (as if you had pressed the Alt keys plus the
            # keypad code for the character), but the rest of the
            # console input simply doesn't
            # work with key up events - e.g. misses keyboard repeats.
            #
            # We therefore allow any key press (i.e. KeyDown) event and
            # _any_ event that appears to have popped up from nowhere
            # as long as the Alt key is present.
            key_code = ord(event.Char)
            if (event.KeyDown or
                    (key_code > 0 and key_code not in self._keys and
                     event.VirtualKeyCode == win32con.VK_MENU)):
                # Record any keys that were pressed.
                if event.KeyDown:
                    self._keys.add(key_code)

                # Translate keys into a KeyboardEvent object.
                if event.VirtualKeyCode in self._KEY_MAP:
                    key_code = self._KEY_MAP[event.VirtualKeyCode]

                # Sadly, we are limited to Linux terminal input and so
                # can't return modifier states in a cross-platform way.
                # If the user decided not to be cross-platform, so be
                # it, otherwise map some standard bindings for extended
                # keys.
                if (self._map_all and
                        event.VirtualKeyCode in self._EXTRA_KEY_MAP):
                    key_code = self._EXTRA_KEY_MAP[event.VirtualKeyCode]
                else:
                    if (event.VirtualKeyCode == win32con.VK_TAB and
                            event.ControlKeyState &
                            win32con.SHIFT_PRESSED):
                        key_code = Screen.KEY_BACK_TAB

                # Don't return anything if we didn't have a valid
                # mapping.
                if key_code:
                    return KeyboardEvent(key_code)
            else:
                # Tidy up any key that was previously pressed.  At
                # start-up, we may be mid-key, so can't assume this must
                # always match up.
                if key_code in self._keys:
                    self._keys.remove(key_code)

        elif event.EventType == win32console.MOUSE_EVENT:
            # Translate into a MouseEvent object.
            button = 0
            print(event.ButtonState, end="  ")
            if event.EventFlags == 0:
                # Button pressed - translate it.
                if (event.ButtonState & win32con.FROM_LEFT_1ST_BUTTON_PRESSED != 0):
                    button |= MouseEvent.LEFT_CLICK
                if (event.ButtonState & win32con.RIGHTMOST_BUTTON_PRESSED != 0):
                    button |= MouseEvent.RIGHT_CLICK
            elif event.EventFlags & win32con.DOUBLE_CLICK != 0:
                button |= MouseEvent.DOUBLE_CLICK
            button = (event.ButtonState if type(event.ButtonState) == int and button == 0 else button)
            return MouseEvent(event.MousePosition.X,
                              event.MousePosition.Y,
                              button)

    # If we get here, we've fully processed the event queue and found
    # nothing interesting.
    return None


setattr(Screen, "start_play", start_play)
setattr(Screen, "no_while_play", no_while_play)
setattr(Screen, "my_get_event", my_get_event)

try:
    screen = Screen.open(None,
                         catch_interrupt=False,
                         unicode_aware=None)

    scenes = []

    effects = [
        # Print(screen,
        #       MyNiceLire(screen.height, screen.width, "*" * 70, 0.8, 60, screen.colours, bg=screen.colours >= 256),
        #       0,
        #       speed=1,
        #       transparent=False),
    ]
    scenes.append(Scene(effects, -1))
    screen.start_play(scenes, stop_on_resize=True)
    # screen.no_while_play(stop_on_resize=True)
    while True:
        # screen.no_while_play(stop_on_resize=True)
        ev = screen.my_get_event()
        if type(ev) == event.KeyboardEvent and ev.key_code in [81, 113, -1]:
            break
        if type(ev) == event.MouseEvent:
            print(ev.buttons, ev.x, ev.y)

except StopApplication:
    pass
