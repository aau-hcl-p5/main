"""
Used for USB communication with the NXT
This is one-way and only broadcasting.
The information this class is build for sending,
is the Result class from the algorithms module.

based on: https://github.com/walac/pyusb/blob/master/docs/tutorial.rst
"""

import usb.core
import usb.util

from algorithms.result import Result

ID_VENDOR_LEGO = 0x0694
ID_PRODUCT_NXT = 0x0002


class DeviceNotFound(Exception):
    """
    If the USB device  was not found
    """
    pass


class NxtUsb:
    """
    Used for USB communication with the NXT
    This is one-way and only broadcasting.
    The information this class is build for sending,
    is the Result class from the algorithms module.
    """

    def __init__(self):
        """
        Initializes the usb communication,
        by finding the specific USB port based on
        vendor_id of the NXT, and then writes an
        "ON" signal to the NXT.
        """
        # find our device
        dev = usb.core.find(idVendor=ID_VENDOR_LEGO, idProduct=ID_PRODUCT_NXT)
        # was it found?
        if dev is None:
            raise DeviceNotFound('Device not found')

        # set the active configuration. With no arguments, the first
        # configuration will be the active one
        dev.set_configuration()

        config = dev.get_active_configuration()
        interface = config[(0, 0)]

        self.endpoint = usb.util.find_descriptor(
            interface,
            # match the first OUT endpoint
            custom_match=_is_endpoint_out)
        # handshake with nxt device ("are you ready?")
        assert self.endpoint is not None
        self.endpoint.write(b'\x01\xFF')

    def write_data(self, data: Result) -> None:
        """
        Send a package of data which the NXT
        should react upon by moving the turret
        :param data: a result data
        """
        self.endpoint.write(bytes([int(data.location.x) & 0xFF,
                                   int(data.location.y) & 0xFF,
                                   data.timestamp & 0xFF,
                                   (data.timestamp >> 8) & 0xFF]))

    def __del__(self):
        """
        This broadcasts a "TURNOFF" signal, and sets the endpoint to None
        """
        if hasattr(self, 'endpoint') and self.endpoint is not None:
            self.endpoint.write(b'\xFF\xFF\xFF\xFF')
        self.endpoint = None


def _is_endpoint_out(endpoint) -> bool:
    return usb.util.endpoint_direction(endpoint.bEndpointAddress) == usb.util.ENDPOINT_OUT
