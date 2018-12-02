"""
The module handling communication between this device (the RASP)
and the NXT, which controls the actual motors and "turret".
"""
from typing import Union

from .screen_debugger import screen_debug_wrapper
from .nxt_usb import NxtUsb
from .status import Status
from .print_communication import PrintCommunication


def get_from_str(name) -> Union[NxtUsb, PrintCommunication]:
    if name == "usb":
        return NxtUsb()
    elif name == "print":
        return PrintCommunication()
