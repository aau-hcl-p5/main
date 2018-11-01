"""
This algorithm is a manually created one.
It will:
    1. Do a rough run over of the image to find the first occurrence of grouped red.
    2. Use a filling algorithm to "fill" the object.
    3. Use the average x and y coordinates of the outline to determine the center of the object
    4. Use the old center coordinates to search for the object in the next frame, and the goto 2.
"""
from collections import deque
from typing import Optional, Set, Deque

import numpy as np

from algorithms.utilities import Vector

DEFAULT_FIND_STEP_SIZE = 4
DEFAULT_FILL_STEP_SIZE = 2
DEFAULT_REQUIRED_STEPS_FOR_FIND = 3
DEFAULT_RED_THRESHOLD = 10
DEFAULT_MIN_AREA_SIZE = 50


def _redness(vector: Vector, frame: np.ndarray) -> int:
    x = int(vector.x)
    y = int(vector.y)
    return frame.item(y, x, 2) - frame.item(y, x, 1) - frame.item(y, x, 0)


class ObjectFillController:  # pylint: disable=too-few-public-methods
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
                 debug: bool = True,
                 dynamic_fill_size: bool = True
                 ) -> None:
        self.find_step_size = find_step_size
        self.fill_step_size = fill_step_size
        self.required_steps_for_find = required_steps_for_find
        self.red_threshold = red_threshold
        self.debug = debug
        self._last_center: Optional[Vector] = None
        self._dynamic_fill_size = dynamic_fill_size
        self._blacklisted_pixels = {None}

    def locate_center(self, frame: np.ndarray) -> Optional[Vector]:
        """
        :param frame: The image to search in
        :return: The center of the object (Can be null).
        """

        image_size = Vector(frame.shape[1], frame.shape[0])
        new_center = None

        # while new_center is None:
        # for i in range(1):
        object_position = self._locate_object(frame, image_size)
        if object_position:
            new_center = self._fill_get_center(object_position, frame, image_size)
            if new_center is not None:
                pass  # break
        else:
            pass  # break

        self._last_center = new_center
        self._blacklisted_pixels = {None}
        if new_center is None:
            self.fill_step_size = DEFAULT_FILL_STEP_SIZE

        return self._last_center

    def _locate_object(self, frame: np.ndarray, image_size: Vector) -> Optional[Vector]:
        step_size = self.find_step_size
        bound = step_size * 2 + 1
        # set to center if not already set. We this is from where we need to search,
        # so if we have no where to search then just use the center
        if not self._last_center:
            self._last_center = Vector(image_size.x / 2, image_size.y / 2)

        for y in range(0, int(image_size.y), step_size):
            for x in range(0, int(image_size.x) - 3 * step_size, bound):
                if Vector(x, y) in self._blacklisted_pixels:
                    continue
                if y + self._last_center.y < image_size.y:
                    current_y = int(y + self._last_center.y)
                    if all(self._is_red(Vector(z, current_y), frame) for z in range(x, x + bound, step_size)):
                        return Vector(x + step_size, current_y)
                if self._last_center.y - y > 0:
                    current_y = int(self._last_center.y - y)
                    if all(self._is_red(Vector(z, current_y), frame) for z in range(x, x + bound, step_size)):
                        return Vector(x + step_size, current_y)
        return None

    def _is_pixel_on_border(self, pixel: Vector, image_size: Vector) -> bool:
        #return pixel in self._blacklisted_pixels or \
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

    def _fill_get_center(self, object_position: Vector, frame: np.ndarray, image_size: Vector) -> Optional[Vector]:
        queue: Deque = deque()
        visited = {object_position}
        for neighbour in self._get_neighbours(object_position, image_size):
            queue.append(neighbour)
            visited.add(neighbour)
        sum_outline = object_position
        # sum_redness = _redness(object_position, frame)
        sum_elements_in_outline = 1
        while queue:
            element = queue.popleft()
            pixel_redness = _redness(Vector(element.x, element.y), frame)
            if pixel_redness > self.red_threshold:
                sum_outline += element
                sum_elements_in_outline += 1
                # sum_redness += pixel_redness

                if self.debug:
                    frame[int(element.y), int(element.x)] = [0, 255, 0]
                continue

            for neighbour in self._get_neighbours(element, image_size) - visited:
                visited.add(neighbour)
                queue.append(neighbour)

        if self._dynamic_fill_size:
            self.fill_step_size = max(DEFAULT_FILL_STEP_SIZE,
                                      int(sum_elements_in_outline * self.fill_step_size / 75))
        # if sum_redness > DEFAULT_MIN_AREA_SIZE:
        return sum_outline / sum_elements_in_outline
        # else:
        # self._blacklisted_pixels = self._blacklisted_pixels | visited
        #    return None

    def _is_red(self, vector: Vector, frame: np.ndarray) -> bool:

        return self.red_threshold < _redness(vector, frame)
