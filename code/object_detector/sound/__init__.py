from enum import Enum


class SOUND_TYPES(Enum):
    FOUND_TARGET = 0
    LOST_TARGET = 1
    ROAMING = 2
    SHUT_DOWN = 3
    ERROR = 4

def play_random_sound(sound_type: SOUND_TYPES):
    raise NotImplementedError

def play_sound(file: str):
    raise NotImplementedError

