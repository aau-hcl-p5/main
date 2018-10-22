import usb.core
import usb.util

from algorithms.result import Result

ID_VENDOR_LEGO = 0x0694
ID_PRODUCT_NXT = 0x0002


class NxtUsb:
    ep = None

    def init_usb_communication(self):
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

        self.ep = usb.util.find_descriptor(
            intf,
            # match the first OUT endpoint
            custom_match=lambda e: usb.util.endpoint_direction(e.bEndpointAddress) == usb.util.ENDPOINT_OUT)
        # handshake with nxt device ("are you ready?")
        assert self.ep is not None
        self.ep.write(b'\x01\xFF')

    def write_data(self, data: Result):
        if not self.ep:
            self.init_usb_communication()
        self.ep.write(bytes([data.delta_x & 0xFF,
                             data.delta_y & 0xFF,
                             data.timestamp & 0xFF,
                             (data.timestamp >> 8) & 0xFF]))

    def disconnect(self):
        self.ep.write(b'\xFF\xFF\xFF\xFF')
        self.ep = None
