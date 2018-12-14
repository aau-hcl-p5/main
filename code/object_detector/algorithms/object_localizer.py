from typing import Optional

import numpy as np

from .utilities import Vector


class ObjectLocalizer:
    def locate_center(self, frame: np.ndarray) -> Optional[Vector]:
        raise NotImplementedError

