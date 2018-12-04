"""
Used for USB output_devices with the NXT
based on: https://github.com/walac/pyusb/blob/master/docs/tutorial.rst
"""

import usb.core
import usb.util

from algorithms import Vector
from output_devices.status import Status

ID_VENDOR_LEGO = 0x0694
ID_PRODUCT_NXT = 0x0002


class DeviceNotFound(Exception):
    """
    If the USB device  was not found
    """
    pass


class NxtUsb:
    """
    Used for USB output_devices with the NXT
    """

    def __enter__(self):
        """
        Initializes the usb output_devices,
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

        self.out_endpoint, self.in_endpoint = self.device[0][(0, 0)]
        self.out_endpoint.write(b'\x01\xFF')  # Tell NXT we want to init usb output_devices
        self.device.read(self.in_endpoint.bEndpointAddress, 8)  # Read the initial ".ecrobot" from nxt usb accept init
        self.initialized = True
        return self

    def __exit__(self, exc_type, exc_val, exc_tb):
        """
        This broadcasts a "TURNOFF" signal, and sets the endpoint to None
        """
        if self.initialized:
            self.write_status(Status.DISCONNECT_REQ)

    def read(self) -> bytes:
        """
        Read stream from device
        :return: the bytes from the device
        """
        return self.device.read(self.in_endpoint.bEndpointAddress, 8)

    def write_location(self, data: Vector) -> None:
        """
        Send a package of data which the NXT
        should react upon by moving the turret
        :param data: a result data
        """
        self.out_endpoint.write(bytes([
            0,
            0,
            int(data.x) & 0xFF,
            int(data.y) & 0xFF
        ]))

    def write_status(self, status: Status):
        value = status.value
        if type(value) is tuple:
            value = value[0]
        self.out_endpoint.write(bytes([
            int(value) & 0xFF,
            0
        ]))
