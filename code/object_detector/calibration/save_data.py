import dataclasses
import datetime

import usb

from calibration.utils import Package
from communication import NxtUsb, Status


def save_packages(usb_controller: NxtUsb):
    print("Received packages until newline:")
    packages = []

    usb_controller.write_status(Status.READY_FOR_CALIBRATION)
    while 1:
        try:
            data = usb_controller.read()
            if all(val == 0 for val in data):
                continue
            print(f"{len(packages)} - {data}")
            packages.append(Package(data[0], data[1], data[2], data[3]))
        except usb.core.USBError as e:
            print(f"{len(packages)} - ERROR {e}")
        except KeyboardInterrupt:
            break

    FILE = open(datetime.datetime.now().strftime('%m_%d_%H_%M_%S.result'), 'w')

    FILE.write("\n".join(str(dataclasses.asdict(p)) for p in packages))
