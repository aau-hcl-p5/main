from enum import Enum


class Status(Enum):
    TARGET_FOUND = 0
    NO_TARGET_FOUND = 1
    DISCONNECT_REQ = 2
    READY_FOR_CALIBRATION = 3
