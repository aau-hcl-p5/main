"""
The module handling communication between this device (the RASP)
and the NXT, which controls the actual motors and "turret".
"""
from algorithms.result import Result
from .screen_debugger import screen_debug_wrapper


def send_package(package: Result) -> None:
    """
    Send a package to the connected NXT
    :param package: The data to send.
    """
    print(f"HUR DUR SENDING {package}")
    raise NotImplementedError
