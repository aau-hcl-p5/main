"""
This algorithm is a manually created one.
It splits the image into subzones and detects where there is the most red color.
As the target (in the simplest of cases) is a red ball
or ballon, the reddest spot on the image must be the balloon.
This obviously isn't perfect but is the first iteration of object detection
"""
from typing import Dict, Optional

from .object_localizer import ObjectLocalizer
from algorithms.utilities import Vector

PIXEL_SKIPPED = 30
MAX_LINES = 40
MIN_LINES = 5
# set MAX_ADJUST_COUNTER to -1 to disable adjusts
MAX_ADJUST_COUNTER = 5
DEFAULT_LINES = 20
REDNESS_THRESHOLD = 20


class ZoneAvgController(ObjectLocalizer):  # pylint: disable=too-few-public-methods
    """
    The controller for the algorithm looking at the level of redness in a given image.
    This holds the state of the adjusts and current lines, for dynamic adjust of precision.
    """

    def __init__(self, lines=DEFAULT_LINES) -> None:
        """
        Initializes the state of the algorithm, and exposes the possible settings.
        :param lines:
        """
        self.lines = lines
        self.adjust_counter = 0
        self.last_best_zone: Optional[Vector] = None

    def locate_center(self, frame) -> Optional[Vector]:
        """
        Takes a frame in a video feed and figures out where a target is, based on color.
        This takes the zone (subset of image) with the most distinct red color.
        This is Theta(xy), however is sub-optimized by only looking at some of the pixels pixel.
        :param frame: the image to search in
        :return: the target of the search. is nullable
        """
        image_size = Vector(frame.shape[1], frame.shape[0])
        size_of_zone = image_size // self.lines

        zones: Dict[Vector, int] = {}
        for x in range(0, int(image_size.x), PIXEL_SKIPPED):
            for y in range(0, int(image_size.y), PIXEL_SKIPPED):
                pixel_loc = Vector(x, y)
                current_zone = self._get_current_zone(pixel_loc, image_size)

                if current_zone not in zones:
                    zones[current_zone] = 0
                zones[current_zone] += _value_of_pixel(frame[pixel_loc.y, pixel_loc.x])

        zone = _get_best_zone(zones)

        loc = ((zone + 0.5) * size_of_zone).as_int() if zone else None

        self._draw_zones(frame, size_of_zone, image_size)
        self._adjust_lines(zone)
        return loc

    def _adjust_lines(self, best_zone: Optional[Vector]) -> None:
        if MAX_ADJUST_COUNTER == -1:
            return

        if best_zone:
            if best_zone == self.last_best_zone:
                self.adjust_counter += 1
            else:
                self.adjust_counter -= 1
        else:
            self.adjust_counter -= 2

        if -MAX_ADJUST_COUNTER > self.adjust_counter or self.adjust_counter > MAX_ADJUST_COUNTER:
            adjust_by_increase = self.adjust_counter > MAX_ADJUST_COUNTER
            self.adjust_counter = 0
            self.lines = self.lines + (1 if adjust_by_increase else -1)

            if MIN_LINES > self.lines or self.lines > MAX_LINES:
                self.lines = MAX_LINES if self.lines > MAX_LINES else MIN_LINES

        self.last_best_zone = best_zone

    def _get_current_zone(self, current_pixel: Vector, image_size: Vector) -> Vector:
        # can't divide vector with int, so we just make the int into a vector
        zone_size_inverse = Vector(self.lines, self.lines) / image_size
        vector = current_pixel * zone_size_inverse

        return Vector(int(vector.x), int(vector.y))

    def _draw_zones(self, frame, size_of_zones, size_image) -> None:
        """
        Used for debugging. This draws all the lines symbolising the subsections of the image.
        :param frame:
        :param size_of_zones:
        :param size_image:
        :return:
        """
        for x in range(0, size_image.x):
            for line_y in range(self.lines):
                frame[size_of_zones.y * line_y, x] = [255, 255, 255]
        for y in range(0, size_image.y):
            for line_x in range(self.lines):
                frame[y, size_of_zones.x * line_x] = [255, 255, 255]


def _value_of_pixel(pixel) -> int:
    val = int(pixel[2]) - (int(pixel[1]) + pixel[0])
    return val if val > 0 else 0


def _acceptance_criteria(best_value: int, total: int, amount_of_zones: int) -> bool:
    avg = total / amount_of_zones
    return best_value > avg * 1.5 and best_value > REDNESS_THRESHOLD


def _get_best_zone(zones) -> Optional[Vector]:
    best_value: int = 0
    best_loc: Optional[Vector] = None
    total = 0
    for zone, color in zones.items():
        total += color
        if best_value < color:
            best_value = color
            best_loc = zone

    accepted = _acceptance_criteria(best_value, total, len(zones))
    return best_loc if accepted else None
