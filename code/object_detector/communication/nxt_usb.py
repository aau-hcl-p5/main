"""
Used for USB communication with the NXT
This is one-way and only broadcasting.
The information this class is build for sending,
is the Result class from the algorithms module.

based on: https://github.com/walac/pyusb/blob/master/docs/tutorial.rst
"""

import usb.core
import usb.util

from algorithms import Vector
from communication.status import Status

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
        self.device = usb.core.find(idVendor=ID_VENDOR_LEGO, idProduct=ID_PRODUCT_NXT)
        # was it found?
        if self.device is None:
            raise DeviceNotFound('Device not found')

        # set the active configuration. With no arguments, the first
        # configuration will be the active one
        self.device.set_configuration()

        config = self.device.get_active_configuration()
        interface = config[(0, 0)]

        self.in_endpoint = self.device[0][(0, 0)][0]
        self.endpoint = usb.util.find_descriptor(
            interface,
            # match the first OUT endpoint
            custom_match=_is_endpoint_out)
        # handshake with nxt device ("are you ready?")
        assert self.endpoint is not None
        self.endpoint.write(b'\x01\xFF')

    def read(self):
        """
        Read stream from device
        :return: the bytes from the device
        """
        return self.device.read(self.in_endpoint.bEndpointAddress,
                                8)
                                #self.in_endpoint.wMaxPacketSize)

    def write_location(self, data: Vector) -> None:
        """
        Send a package of data which the NXT
        should react upon by moving the turret
        :param data: a result data
        """
        self.write_status(Status.TARGET_FOUND)
        self.endpoint.write(bytes([
            int(data.x) & 0xFF,
            int(data.y) & 0xFF,
            0
        ]))

    def write_status(self, status: Status):
        value = status.value
        if type(value) is tuple:
            value = value[0]
        self.endpoint.write(bytes([
            int(value) & 0xFF,
            0
        ]))

    def __del__(self):
        """
        This broadcasts a "TURNOFF" signal, and sets the endpoint to None
        """
        if hasattr(self, 'endpoint') and self.endpoint is not None:
            self.write_status(Status.DISCONNECT_REQ)
        self.endpoint = None


def _is_endpoint_out(endpoint) -> bool:
    return usb.util.endpoint_direction(endpoint.bEndpointAddress) == usb.util.ENDPOINT_OUT
