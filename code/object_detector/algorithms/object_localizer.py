from typing import Optional, Tuple

import numpy as np

from .utilities import Vector


class ObjectLocalizer:
    """
    The interface for each object localization algorithm
    """
    def locate_center(self, frame: np.ndarray) -> Optional[Tuple[Vector, bool]]:
        """
        Locating the center of the target in the image in frame.
        :param frame: the image from a video stream
        :return: a nullable tuple with target location and a bool flag whether the target
            covers the center
        """
        raise NotImplementedError

