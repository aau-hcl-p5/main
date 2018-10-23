"""
This algorithm is a manually created one.
It will:
    1. Do a rough run over of the image to find the first occurrence of grouped red.
    2. Use a filling algorithm to "fill" the object.
    3. Use the average x and y coordinates of the outline to determine the center of the object
    4. Use the old center coordinates to search for the object in the next frame, and the goto 2.
"""
import numpy as np
from typing import Optional
from collections import deque
from algorithms.utilities import Vector

DEFAULT_FIND_STEP_SIZE = 4
DEFAULT_FILL_STEP_SIZE = 2
DEFAULT_REQUIRED_STEPS_FOR_FIND = 3
DEFAULT_RED_THRESHOLD = 10


class ObjectFillController:  # pylint: disable=too-few-public-methods

    def __init__(self,
                 find_step_size=DEFAULT_FIND_STEP_SIZE,
                 fill_step_size=DEFAULT_FILL_STEP_SIZE,
                 required_steps_for_find=DEFAULT_REQUIRED_STEPS_FOR_FIND,
                 red_threshold=DEFAULT_RED_THRESHOLD,
                 debug=True
                 ) -> None:
        self.find_step_size = find_step_size
        self.fill_step_size = fill_step_size
        self.required_steps_for_find = required_steps_for_find
        self.red_threshold = red_threshold
        self.debug = debug
        self._last_center = None

    def locate_center(self, frame: np.ndarray) -> Optional[Vector]:
        """
        :param frame: The image to search in
        :return: The center of the object (Can be null).
        """
        image_size = (frame.shape[1], frame.shape[0])
        if not self._last_center:
            self._last_center = Vector(image_size[0] / 2, image_size[1] / 2)

        object_position = self._locate_object(frame, image_size)
        if object_position:
            self._last_center = self._fill_get_center(object_position, frame, image_size)
        else:
            if self.debug:
                print("No red object found!")
            self._last_center = None

        return self._last_center

    def _locate_object(self, frame: np.ndarray, image_size: (int, int)) -> Optional[Vector]:
        width = image_size[0]
        height = image_size[1]
        step_size = self.find_step_size
        bound = step_size * 2 + 1
        for y in range(0, height, step_size):
            for x in range(0, width, bound):
                if y + self._last_center.y < height:
                    current_y = y + self._last_center.y
                    if all(self._is_red(z, current_y, frame) for z in range(x, x + bound, step_size)):
                        return Vector(x + step_size, current_y)
                if self._last_center.y - y > 0:
                    current_y = self._last_center.y - y
                    if all(self._is_red(z, current_y, frame) for z in range(x, x + bound, step_size)):
                        return Vector(x + step_size, current_y)
        return None

    def _get_neighbours(self, x: int, y: int, image_size: (int, int)) -> {Vector}:
        if x - self.fill_step_size < 0 or image_size[0] - self.fill_step_size <= x + self.fill_step_size + 1 or \
           y - self.fill_step_size < 0 or image_size[1] - self.fill_step_size <= y + self.fill_step_size + 1:
            return set()

        return {Vector(x - self.fill_step_size, y), Vector(x + self.fill_step_size, y),
                Vector(x, y - self.fill_step_size), Vector(x, y + self.fill_step_size)}

    def _fill_get_center(self, object_position: Vector, frame: np.ndarray, image_size: (int, int)) -> Vector:
        queue = deque()
        visited = {object_position}
        for neighbour in self._get_neighbours(object_position.x, object_position.y, image_size):
            queue.append(neighbour)
            visited.add(neighbour)
        sum_outline_x = object_position.x
        sum_outline_y = object_position.y
        total_elements_in_outline = 1
        while queue:
            element = queue.popleft()
            if not self._is_red(element.x, element.y, frame):
                sum_outline_x += element.x
                sum_outline_y += element.y
                total_elements_in_outline += 1
                if self.debug:
                    frame[int(element.y), int(element.x)] = [0, 255, 0]
                continue

            for neighbour in self._get_neighbours(element.x, element.y, image_size) - visited:
                visited.add(neighbour)
                queue.append(neighbour)

        return Vector(sum_outline_x / total_elements_in_outline, sum_outline_y / total_elements_in_outline)

    def _is_red(self, x: int, y: int, frame: np.ndarray) -> bool:
        x = int(x)
        y = int(y)
        return self.red_threshold < frame.item(y, x, 2) - frame.item(y, x, 1) - frame.item(y, x, 0)
