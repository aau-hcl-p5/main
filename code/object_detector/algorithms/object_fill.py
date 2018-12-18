"""
This algorithm is a manually created one.
It will:
    1. Do a rough run over of the image to find the first occurrence of grouped red.
    2. Use a filling algorithm to "fill" the object.
    3. Use the average x and y coordinates of the outline to determine the center of the object
    4. Use the old center coordinates to search for the object in the next frame, and the goto 2.
"""
from collections import deque
from functools import reduce
from typing import Optional, Set, Deque, Union, Iterator, Tuple

import numpy as np

from .object_localizer import ObjectLocalizer
from .utilities import Vector

DEFAULT_FIND_STEP_SIZE = 4
DEFAULT_FILL_STEP_SIZE = 2
DEFAULT_REQUIRED_STEPS_FOR_FIND = 3
DEFAULT_RED_THRESHOLD = 4
DEFAULT_MIN_TOTAL_REDNESS = 3000  # value of my mouth


def _redness(x: Union[int, float], y: Union[int, float], frame: np.ndarray) -> int:
    return frame.item(int(y), int(x), 2) - \
           frame.item(int(y), int(x), 1) - \
           frame.item(int(y), int(x), 0)


class ObjectFillController(ObjectLocalizer):  # pylint: disable=too-few-public-methods
    """
This algorithm is a manually created one.
It will:
    1. Do a rough run over of the image to find the first occurrence of grouped red.
    2. Use a filling algorithm to "fill" the object.
    3. Use the average x and y coordinates of the outline to determine the center of the object
    4. Use the old center coordinates to search for the object in the next frame, and the goto 2.
    """

    def __init__(self,
                 find_step_size: int = DEFAULT_FIND_STEP_SIZE,
                 fill_step_size: int = DEFAULT_FILL_STEP_SIZE,
                 required_steps_for_find: int = DEFAULT_REQUIRED_STEPS_FOR_FIND,
                 red_threshold: int = DEFAULT_RED_THRESHOLD,
                 debug: bool = False,
                 dynamic_fill_size: bool = True
                 ) -> None:
        self.find_step_size = find_step_size
        self.fill_step_size = fill_step_size
        self.required_steps_for_find = required_steps_for_find
        self.red_threshold = red_threshold
        self.debug = debug
        self._last_center: Optional[Vector] = None
        self._dynamic_fill_size = dynamic_fill_size
        self._blacklisted_pixels: Set[Vector] = set()

    def locate_center(self, frame: np.ndarray) -> Optional[Tuple[Vector, bool]]:
        """
        :param frame: The image to search in
        :return: The center of the object (Can be null).
        """

        image_size = Vector(frame.shape[1], frame.shape[0])

        # """
        new_data = None
        for object_position in self._locate_object(frame, image_size):
            new_data = self._fill_get_center(object_position, frame, image_size)
            if new_data is not None:
                break
        if self.debug:
            for pixel in self._blacklisted_pixels:
                if pixel is not None:
                    frame[pixel.y, pixel.x] = [0, 0, 0]
        # get location from tuple

        self._last_center = new_data[0] if new_data else None
        self._blacklisted_pixels = set()
        if new_data is None:
            self.fill_step_size = DEFAULT_FILL_STEP_SIZE

        return new_data

    @property
    def _bound(self) -> int:
        return self.find_step_size * 2 + 1

    def _all_pixels_around_point_are_red(self, x: int, y:int, frame: np.ndarray) -> bool:
        return all(
            Vector(current_x, y) not in self._blacklisted_pixels and
            self._is_red(current_x, y, frame)
            for current_x in range(x, x + self._bound, self.find_step_size)
        )

    def _locate_object(self, frame: np.ndarray, image_size: Vector) -> Iterator[Vector]:
        step_size = self.find_step_size
        # set to center if not already set. We this is from where we need to search,
        # so if we have no where to search then just use the center
        if not self._last_center:
            self._last_center = Vector(image_size.x / 2, image_size.y / 2)

        for y in range(0, int(image_size.y), self.find_step_size):
            for x in range(0, int(image_size.x) - 3 * self.find_step_size, self._bound):
                if y + self._last_center.y < image_size.y:
                    current_y = int(self._last_center.y + y)
                    if self._all_pixels_around_point_are_red(x, current_y, frame):
                        yield Vector(x + step_size, current_y)
                if self._last_center.y - y > 0:
                    current_y = int(self._last_center.y - y)
                    if self._all_pixels_around_point_are_red(x, current_y, frame):
                        yield Vector(x + step_size, current_y)

    def _is_pixel_on_border(self, pixel: Vector, image_size: Vector) -> bool:
        return pixel.x - self.fill_step_size < 0 or \
               image_size.x - self.fill_step_size <= pixel.x + self.fill_step_size + 1 or \
               pixel.y - self.fill_step_size < 0 or \
               image_size.y - self.fill_step_size <= pixel.y + self.fill_step_size + 1

    def _get_neighbours(self, pixel: Vector, image_size: Vector) -> Set[Vector]:
        if self._is_pixel_on_border(pixel, image_size):
            return set()
        x_dir_offset = Vector(self.fill_step_size, 0)
        y_dir_offset = Vector(0, self.fill_step_size)
        return {
            pixel - x_dir_offset,
            pixel + x_dir_offset,
            pixel - y_dir_offset,
            pixel + y_dir_offset
        }

    def _fill_get_center(self, object_position: Vector, frame: np.ndarray, image_size: Vector) -> \
            Optional[Tuple[Vector,bool]]:
        queue: Deque = deque()
        queue.append(object_position)
        self._blacklisted_pixels.add(object_position)
        sum_redness = 0
        # used to calculate whether the bounding box covers the center
        outline = []

        while queue:
            element = queue.popleft()
            pixel_redness = _redness(element.x, element.y, frame)
            # is a bounding pixel
            if pixel_redness < self.red_threshold:
                outline.append(element)
                if self.debug:
                    frame[int(element.y), int(element.x)] = [0, 255, 0]
                continue

            for neighbour in self._get_neighbours(element, image_size) - self._blacklisted_pixels:
                sum_redness += pixel_redness
                self._blacklisted_pixels.add(neighbour)
                queue.append(neighbour)

        if self._dynamic_fill_size:
            self.fill_step_size = max(
                DEFAULT_FILL_STEP_SIZE,
                int(len(outline) * self.fill_step_size / 75)
            )
        sum_outline = Vector(0, 0)
        for e in outline:
            sum_outline += e

        if sum_redness > DEFAULT_MIN_TOTAL_REDNESS:
            on_target = (
                    min(*(e.x for e in outline)) < 0 < max(*(e.x for e in outline)) and
                    min(*(e.y for e in outline)) < 0 < max(*(e.y for e in outline))
            )
            return sum_outline / len(outline), on_target
        else:
            return None

    def _is_red(self, x: int, y: int, frame: np.ndarray) -> bool:

        return self.red_threshold < _redness(x, y, frame)
