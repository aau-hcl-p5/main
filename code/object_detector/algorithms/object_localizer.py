from typing import Optional, Tuple

import numpy as np

from .utilities import Vector


class ObjectLocalizer:
    def locate_center(self, frame: np.ndarray) -> Optional[Tuple[Vector, bool]]:
        raise NotImplementedError

