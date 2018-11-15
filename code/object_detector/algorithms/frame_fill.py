from collections import deque
from typing import Optional, Set, Deque, Union, Iterator

import numpy as np

from algorithms.utilities import Vector

DEFAULT_STEP_SIZE = 4
DEFAULT_RED_THRESHOLD = 4
DEFAULT_OBJECT_MIN = 10
DEFAULT_OBJECT_ACCEPT = 150


def _redness(x: Union[int, float], y: Union[int, float], frame: np.ndarray) -> int:
    return frame.item(int(y), int(x), 2) - frame.item(int(y), int(x), 1) - frame.item(int(y), int(x), 0)


class RedObject:
    def __init__(self, x: int, y: int, size: int):
        self.x = x
        self.y = y
        self.size = size


class FrameFillController:  # pylint: disable=too-few-public-methods
    def __init__(self,
                 step_size: int = DEFAULT_STEP_SIZE,
                 red_threshold: int = DEFAULT_RED_THRESHOLD,
                 debug: bool = False,
                 ) -> None:
        self._step_size = step_size
        self.red_threshold = red_threshold
        self.debug = debug
        self._last_center: Optional[Vector] = None
        self._visited: Set[Vector] = set()

    def locate_center(self, frame: np.ndarray) -> Optional[Vector]:
        """
        :param frame: The image to search in
        :return: The center of the object (Can be null).
        """

        image_size = Vector(frame.shape[1], frame.shape[0])
        if not self._last_center:
            self._last_center = image_size / 2

        self._fill_get_biggest_object(self._last_center)

        return self._last_center

    def _is_pixel_on_border(self, pixel: Vector, image_size: Vector) -> bool:
        return pixel.x - self._step_size < 0 or \
               image_size.x - self._step_size <= pixel.x + self._step_size + 1 or \
               pixel.y - self._step_size < 0 or \
               image_size.y - self._step_size <= pixel.y + self._step_size + 1

    def _get_neighbours(self, pixel: Vector, image_size: Vector) -> Set[Vector]:
        if self._is_pixel_on_border(pixel, image_size):
            return set()
        x_dir_offset = Vector(self._step_size, 0)
        y_dir_offset = Vector(0, self._step_size)
        return {
            pixel - x_dir_offset,
            pixel + x_dir_offset,
            pixel - y_dir_offset,
            pixel + y_dir_offset
        } - self._visited

    def _fill_get_biggest_object(self,
                                 start_position: Vector,
                                 frame: np.ndarray,
                                 filling_object = False):
        queue: Deque = deque()
        queue.append(start_position)
        red_objects = []
        while queue:
            element = queue.popleft()
            if self._is_red(element.x, element.y, frame):
                if not filling_object:
                    red_objects.append(self._fill_get_biggest_object())
                    




    def _is_red(self, x: int, y: int, frame: np.ndarray) -> bool:
        return self.red_threshold < _redness(x, y, frame)
