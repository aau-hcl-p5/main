"""
Handling sound output of the image recognition

The intent of this is to supply auditory debugging.
All sound effects are taken from the Turret from portal, because that seemed fun.
Source:  http://p1.portal2sounds.com/#w=turret
"""
from enum import Enum
from random import random
from typing import List, Dict


class SoundType(Enum):
    """
    The different types of sounds.
    Each type reflects a given state the object detector can be in.
    These types are supplied when wanting a sound effect to play.
    """
    FOUND_TARGET = 0
    LOST_TARGET = 1
    ROAMING = 2
    SHUT_DOWN = 3
    ERROR = 4


def play_random_sound(sound_type: SoundType) -> None:
    """
    Play a random sound based on the requested type.
    The sound_type reflects the current state of the object detector
    :param sound_type: The sound_type to base the sound on
    """
    _play_sound(_get_sound_file_from_type(sound_type))


def _get_sound_file_from_type(sound_type: SoundType) -> str:
    files: Dict[SoundType, List[str]] = {
        SoundType.FOUND_TARGET: [

        ],
        SoundType.LOST_TARGET: [

        ],
        SoundType.ROAMING: [

        ],
        SoundType.SHUT_DOWN: [

        ],
        SoundType.ERROR: [

        ]
    }
    sounds = files[sound_type]
    return sounds[int(random() * len(sounds))]


def _play_sound(file: str):
    print(f"we are now playing '{file}'")
    raise NotImplementedError
