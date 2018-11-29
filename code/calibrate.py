"""
A script that fetches all the calibration data from the NXT,
which can then be used to perform an analysis on.
"""

import datetime
import dataclasses
from time import sleep

import usb.core
import usb.util


def _is_endpoint_in(endpoint) -> bool:
	"""
	Is the endpoint a 'in' or an 'out'?
	to fetch data we need an 'in'
	"""
    return usb.util.endpoint_direction(endpoint.bEndpointAddress) == usb.util.ENDPOINT_IN


ID_VENDOR_LEGO = 0x0694
ID_PRODUCT_NXT = 0x0002
DEVICE = usb.core.find(idVendor=ID_VENDOR_LEGO, idProduct=ID_PRODUCT_NXT)
DEVICE = usb.core.find(idVendor=ID_VENDOR_LEGO, idProduct=ID_PRODUCT_NXT)
DEVICE.set_configuration()
CONFIG = DEVICE.get_active_configuration()
INTERFACE = CONFIG[(0, 0)]
ENDPOINT = None

print("waiting for usb to connect")

while ENDPOINT is None:
    ENDPOINT = usb.util.find_descriptor(INTERFACE, custom_match=_is_endpoint_in)
    sleep(1)


# handshake with nxt device ("are you ready?")
ENDPOINT.write(b'\x01\xFF')
PACKAGES = []
@dataclasses.dataclass
class Package:
    """
    The class that conforms to the data sent by the NXT.
    This has the same signature, but the data might need to change form.
    """
    position: int
    axis: bool
    power: int
    positive_direction: bool

    def is_x(self):
        return self.axis
    def is_y(self):
        return not self.axis


print("Press ctrl+c to exit")
while 1:
    try:
        data = DEVICE.read(ENDPOINT.bEndpointAddress, ENDPOINT.wMaxPacketSize)

        PACKAGES.append(Package(data[0], data[1], data[2], data[3]))
    except KeyboardInterupt:
        break


FILE = open(datetime.datetime.now().strftime('%m_%d_%H_%M_%S.result'), 'w')

FILE.write("\n".join(dataclasses.asdict(p) for p in PACKAGES))
