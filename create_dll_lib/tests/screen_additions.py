from itertools import cycle
from time import sleep
import copy
import sys
from random import randint, random

from asciimatics.effects import Print
from asciimatics.renderers import DynamicRenderer
from asciimatics.scene import Scene
from asciimatics.screen import Screen
from asciimatics.exceptions import ResizeScreenError, StopApplication


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


setattr(Screen, "start_play", start_play)
setattr(Screen, "no_while_play", no_while_play)

all_lines = []  # (x0, y0, x1, y1)


class MyNiceLire(DynamicRenderer):
    """
    Renderer to create a fire effect based on a specified `emitter` that
    defines the heat source.

    The implementation here uses the same techniques described in
    http://freespace.virgin.net/hugo.elias/models/m_fire.htm, although a
    slightly different implementation.
    """

    _COLOURS_16 = [
        (Screen.COLOUR_RED, 0),
        (Screen.COLOUR_RED, 0),
        (Screen.COLOUR_RED, 0),
        (Screen.COLOUR_RED, 0),
        (Screen.COLOUR_RED, 0),
        (Screen.COLOUR_RED, 0),
        (Screen.COLOUR_RED, 0),
        (Screen.COLOUR_RED, Screen.A_BOLD),
        (Screen.COLOUR_RED, Screen.A_BOLD),
        (Screen.COLOUR_RED, Screen.A_BOLD),
        (Screen.COLOUR_RED, Screen.A_BOLD),
        (Screen.COLOUR_YELLOW, Screen.A_BOLD),
        (Screen.COLOUR_YELLOW, Screen.A_BOLD),
        (Screen.COLOUR_YELLOW, Screen.A_BOLD),
        (Screen.COLOUR_YELLOW, Screen.A_BOLD),
        (Screen.COLOUR_WHITE, Screen.A_BOLD),
    ]

    _COLOURS_256 = [
        (0, 0),
        (52, 0),
        (88, 0),
        (124, 0),
        (160, 0),
        (196, 0),
        (202, 0),
        (208, 0),
        (214, 0),
        (220, 0),
        (226, 0),
        (227, 0),
        (228, 0),
        (229, 0),
        (230, 0),
        (231, 0),
    ]

    _CHARS = " ...::$$$&&&@@"
    _line_chars = " ''^.|/7.\\|Ywbd#"
    _uni_line_chars = " ▘▝▀▖▌▞▛▗▚▐▜▄▙▟█"

    def __init__(self, height, width, colours,
                 bg=False, unicode_aware=False):
        """
        :param height: Height of the box to contain the flames.
        :param width: Width of the box to contain the flames.
        :param emitter: Heat source for the flames.  Any non-whitespace
            character is treated as part of the heat source.
        :param intensity: The strength of the flames.  The bigger the number,
            the hotter the fire.  0 <= intensity <= 1.0.
        :param spot: Heat of each spot source.  Must be an integer > 0.
        :param colours: Number of colours the screen supports.
        :param bg: (Optional) Whether to render background colours only.
        """
        super(MyNiceLire, self).__init__(height, width)
        self._unicode_aware = unicode_aware
        # self._emitter = emitter
        # self._intensity = intensity
        # self._spot_heat = spot
        # self._count = len([c for c in emitter if c not in " \n"])
        line = [0 for _ in range(self._width)]
        char_line = ["" for _ in range(self._width)]
        self._buffer = [copy.deepcopy(line) for _ in range(self._width * 2)]
        self._char_buffer = [copy.deepcopy(char_line) for _ in range(self._width * 2)]
        self._colours = self._COLOURS_256 if colours >= 256 else \
            self._COLOURS_16
        self._colors_console_count = colours
        self._bg_too = bg

        # Figure out offset of emitter to centre at the bottom of the buffer
        e_width = 0
        e_height = 0
        for line in self._emitter.split("\n"):
            e_width = max(e_width, len(line))
            e_height += 1
        self._x = (width - e_width) // 2
        self._y = height - e_height
        self.line_chars = (self._uni_line_chars if self._unicode_aware else self._line_chars)

    def get_from(self, x, y):
        """
        Get the character at the specified location.

        :param x: The column (x coord) of the character.
        :param y: The row (y coord) of the character.

        :return: A 4-tuple of (ascii code, foreground, attributes, background)
                 for the character at the location.
        """
        # Convert to buffer coordinates
        # y -= self._start_line
        if y < 0 or y > len(self._char_buffer) or x < 0 or x >= self._width:
            return None
        char = self._char_buffer[y][x]
        if bool(char):
            return ord(char)
        return None

    def _render_now(self, char=None, thin=False):

        color_iterator = cycle(range(16))
        char_line = ["" for _ in range(self._width)]
        self._char_buffer = [copy.deepcopy(char_line) for _ in range(self._width * 2)]

        for (x0, y0, x1, y1, *new_color_iter) in all_lines:
            x0, y0 = int(round(x0 * 2, 0)), int(round(y0 * 2, 0))
            x1, y1 = int(round(x1 * 2, 0)), int(round(y1 * 2, 0))
            if new_color_iter and bool(new_color_iter):
                color_iterator = new_color_iter[0]
                if len(new_color_iter) > 1:
                    self._colours = new_color_iter[1]

            # Don't bother drawing anything if we're guaranteed to be off-screen
            if ((x0 < 0 and x1 < 0) or (x0 >= self._width * 2 and x1 >= self._width * 2) or
                    (y0 < 0 and y1 < 0) or (y0 >= self._height * 2 and y1 >= self._height * 2)):
                continue

            dx = abs(x1 - x0)
            dy = abs(y1 - y0)

            sx = -1 if x0 > x1 else 1
            sy = -1 if y0 > y1 else 1

            def _get_start_char(cx, cy):
                needle = self.get_from(cx, cy)
                if needle is not None and bool(needle):
                    letter = needle
                    if chr(letter) in self.line_chars:
                        return self.line_chars.find(chr(letter))
                return 0

            def _fast_fill(start_x, end_x, iy):
                next_char = -1

                for ix in range(start_x, end_x):
                    if ix % 2 == 0 or next_char == -1:
                        next_char = _get_start_char(ix // 2, iy // 2)
                    next_char |= 2 ** abs(ix % 2) * 4 ** (iy % 2)
                    if ix % 2 == 1:
                        self._char_buffer[iy // 2][ix // 2] = self.line_chars[next_char]
                        self._buffer[iy // 2][ix // 2] = next(color_iterator)
                if end_x % 2 == 1:
                    self._char_buffer[iy // 2][end_x // 2] = self.line_chars[next_char]
                    self._buffer[iy // 2][end_x // 2] = next(color_iterator)

            def _draw_on_x(ix, iy):
                err = dx
                px = ix - 2
                py = iy - 2
                next_char = 0
                while ix != x1:
                    if ix < px or ix - px >= 2 or iy < py or iy - py >= 2:
                        px = ix & ~1
                        py = iy & ~1
                        next_char = _get_start_char(px // 2, py // 2)
                    next_char |= 2 ** abs(ix % 2) * 4 ** (iy % 2)
                    err -= 2 * dy
                    if err < 0:
                        iy += sy
                        err += 2 * dx
                    ix += sx

                    if char is None:
                        self._char_buffer[py // 2][px // 2] = self.line_chars[next_char]
                        self._buffer[py // 2][px // 2] = next(color_iterator)
                    else:
                        self._char_buffer[py // 2][px // 2] = char
                        self._buffer[py // 2][px // 2] = next(color_iterator)

            def _draw_on_y(ix, iy):
                err = dy
                px = ix - 2
                py = iy - 2
                next_char = 0
                while iy != y1:
                    if ix < px or ix - px >= 2 or iy < py or iy - py >= 2:
                        px = ix & ~1
                        py = iy & ~1
                        next_char = _get_start_char(px // 2, py // 2)
                    next_char |= 2 ** abs(ix % 2) * 4 ** (iy % 2)
                    err -= 2 * dx
                    if err < 0:
                        ix += sx
                        err += 2 * dy
                    iy += sy

                    if char is None:
                        self._buffer[py // 2][px // 2] = next(color_iterator)
                        self._char_buffer[py // 2][px // 2] = self.line_chars[next_char]
                    else:
                        self._char_buffer[py // 2][px // 2] = char
                        self._buffer[py // 2][px // 2] = next(color_iterator)

            if dy == 0 and thin and char is None:
                # Fast-path for polygon filling
                _fast_fill(min(x0, x1), max(x0, x1), y0)
            elif dx > dy:
                _draw_on_x(x0, y0)
                if not thin:
                    _draw_on_x(x0, y0 + 1)
            else:
                _draw_on_y(x0, y0)
                if not thin:
                    _draw_on_y(x0 + 1, y0)

        self._clear()
        for x in range(self._width):
            for y in range(len(self._buffer)):
                if self._buffer[y][x] > 0:
                    colour = self._colours[min(len(self._colours) - 1,
                                               self._buffer[y][x])]
                    if self._bg_too:
                        char = " "
                        bg = colour[0]
                    else:
                        char = self._char_buffer[y][x]
                        bg = 0
                    self._write(char, x, y, colour[0], colour[1], bg)
        return self._plain_image, self._colour_map

