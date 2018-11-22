import dataclasses
import datetime

import usb

from calibration.utils import Package

ID_VENDOR_LEGO = 0x0694
ID_PRODUCT_NXT = 0x0002


def _is_endpoint_in(endpoint) -> bool:
    """
    Is the endpoint a 'in' or an 'out'?
    to fetch data we need an 'in'
    """
    return usb.util.endpoint_direction(endpoint.bEndpointAddress) == usb.util.ENDPOINT_IN


def save_packages():
    device = usb.core.find(idVendor=ID_VENDOR_LEGO, idProduct=ID_PRODUCT_NXT)
    device.set_configuration()
    config = device.get_active_configuration()
    interface = config[(0, 0)]

    endpoint = usb.util.find_descriptor(interface, custom_match=_is_endpoint_in)
    print("Received packages until newline:")
    packages = []
    packages = 0
    while 1:
        print(packages, end='r')
        try:
            data = device.read(endpoint.bEndpointAddress, endpoint.wMaxPacketSize)

            packages.append(Package(data[0], data[1], data[2], data[3]))
        except KeyboardInterrupt:
            break
            
        packages += 1

    FILE = open(datetime.datetime.now().strftime('%m_%d_%H_%M_%S.result'), 'w')

    FILE.write("\n".join(dataclasses.asdict(p) for p in packages))
