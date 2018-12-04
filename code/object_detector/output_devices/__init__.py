"""
The module handling output_devices between this device (the RASP)
and the NXT, which controls the actual motors and "turret".
"""
from typing import Union

from .screen_debugger import render_debugscreen
from .nxt_usb import NxtUsb
from .status import Status
from .printer import Printer


def get_from_str(name) -> Union[NxtUsb, Printer]:
    if name == "usb":
        return NxtUsb()
    return Printer()
