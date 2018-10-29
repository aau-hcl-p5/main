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
                 dynamic_fill_size: bool =True
                 ) -> None:
        self.find_step_size = find_step_size
        self.fill_step_size = fill_step_size
        self.required_steps_for_find = required_steps_for_find
        self.red_threshold = red_threshold
        self.debug = debug
        self._last_center: Optional[Vector] = None
        self._dynamic_fill_size = dynamic_fill_size

    def locate_center(self, frame: np.ndarray) -> Optional[Vector]:
        """
        :param frame: The image to search in
        :return: The center of the object (Can be null).
        """
        image_size = Vector(int(frame.shape[1]), frame.shape[0])

        object_position = self._locate_object(frame, image_size)
        if object_position:
            self._last_center = self._fill_get_center(object_position, frame, image_size)
        else:
            #if self.debug:
                #print("No red object found!")
            self._last_center = None
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
                if y + self._last_center.y < image_size.y:
                    current_y = int(y + self._last_center.y)
                    if all(self._is_red(z, current_y, frame) for z in range(x, x + bound, step_size)):
                        return Vector(x + step_size, current_y)
                if self._last_center.y - y > 0:
                    current_y = int(self._last_center.y - y)
                    if all(self._is_red(z, current_y, frame) for z in range(x, x + bound, step_size)):
                        return Vector(x + step_size, current_y)
        return None

    def _is_pixel_on_border(self, pixel: Vector, image_size: Vector):
        return pixel.x - self.fill_step_size < 0 or \
               image_size.x - self.fill_step_size <= pixel.x + self.fill_step_size + 1 or \
               pixel.y - self.fill_step_size < 0 or \
               image_size.y - self.fill_step_size <= pixel.y + self.fill_step_size + 1

    def _get_neighbours(self, pixel: Vector, image_size: Vector) -> Set[Vector]:
        if self._is_pixel_on_border(pixel, image_size):
            return set()
        x_dir_offset = Vector(self.fill_step_size, 0)
        y_dir_offset = Vector(0, self.fill_step_size)
        return {pixel - x_dir_offset, pixel + x_dir_offset, pixel - y_dir_offset, pixel + y_dir_offset}

    def _fill_get_center(self, object_position: Vector, frame: np.ndarray, image_size: Vector) -> Vector:
        queue: Deque = deque()
        visited = {object_position}
        for neighbour in self._get_neighbours(object_position, image_size):
            queue.append(neighbour)
            visited.add(neighbour)
        sum_outline = object_position
        sum_elements_in_outline = 1
        while queue:
            element = queue.popleft()
            if not self._is_red(element.x, element.y, frame):
                sum_outline += element
                sum_elements_in_outline += 1
                if self.debug:
                    frame[int(element.y), int(element.x)] = [0, 255, 0]
                continue

            for neighbour in self._get_neighbours(element, image_size) - visited:
                visited.add(neighbour)
                queue.append(neighbour)

        if self._dynamic_fill_size:
            self.fill_step_size = max(DEFAULT_FILL_STEP_SIZE,
                                      int(sum_elements_in_outline * self.fill_step_size / 75))
            
        return sum_outline / sum_elements_in_outline

    def _is_red(self, x: int, y: int, frame: np.ndarray) -> bool:
        x = int(x)
        y = int(y)
        return self.red_threshold < frame.item(y, x, 2) - frame.item(y, x, 1) - frame.item(y, x, 0)
