"""
Used for USB communication with the NXT
This is one-way and only broadcasting.
The information this class is build for sending,
is the Result class from the algorithms module.

"""
from typing import Optional

import usb.core
import usb.util
from usb import Device

from algorithms.result import Result

ID_VENDOR_LEGO = 0x0694
ID_PRODUCT_NXT = 0x0002


class NxtUsb:
    """
Used for USB communication with the NXT
This is one-way and only broadcasting.
The information this class is build for sending,
is the Result class from the algorithms module.
    """
    def __init__(self):
        self.endpoint: Device = None

    def init_usb_communication(self) -> None:
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
            raise ValueError('Device not found')

        # set the active configuration. With no arguments, the first
        # configuration will be the active one
        dev.set_configuration()

        cfg = dev.get_active_configuration()
        intf = cfg[(0, 0)]

        self.endpoint = usb.util.find_descriptor(
            intf,
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
        if not self.endpoint:
            self.init_usb_communication()
        self.endpoint.write(bytes([data.delta_x & 0xFF,
                                   data.delta_y & 0xFF,
                                   data.timestamp & 0xFF,
                                   (data.timestamp >> 8) & 0xFF]))

    def disconnect(self) -> None:
        """
        This broadcasts a "TURNOFF" signal, and sets the endpoint to None
        """
        if self.endpoint:
            self.endpoint.write(b'\xFF\xFF\xFF\xFF')
        self.endpoint = None

    def __del__(self):
        self.disconnect()


def _is_endpoint_out(endpoint) -> bool:
    return usb.util.endpoint_direction(endpoint.bEndpointAddress) == usb.util.ENDPOINT_OUT
