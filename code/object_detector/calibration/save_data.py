import datetime
import time
from typing import List

import usb

from calibration.utils import Package
from output_devices import NxtUsb, Status

import matplotlib.pyplot as plt

MAX_SEQUENTIAL_TIMEOUTS = 3


def combine_bytes(data, index):
    return (data[index + 1] << 8) | data[index]


# noinspection PyArgumentList
def save_packages(usb_controller: NxtUsb):
    packages: List[Package] = []

    usb_controller.write_status(Status.READY_FOR_CALIBRATION)
    from calibration.averaged_list import AveragedList
    result_up = AveragedList(360, 7)
    result_down = AveragedList(360, 7)
    timeout_counter = 0
    while 1:
        try:
            data = usb_controller.read()
            print(f"{len(packages)} - {data}")
            package = Package(
                                combine_bytes(data, 0),
                                bool(combine_bytes(data, 2)),
                                combine_bytes(data, 4),
                                combine_bytes(data, 6)
                              )
            packages.append(package)
            timeout_counter = 0
            if package.power_up:
                result_up[package.position] = package.power_up
            if package.power_down:
                result_down[package.position] = package.power_down
        except usb.core.USBError as e:
            print(f"- ERROR {e}")
            timeout_counter += 1
            if timeout_counter > MAX_SEQUENTIAL_TIMEOUTS:
                break
        except KeyboardInterrupt:
            break

    plt.plot([x for x in result_down], label="Down")
    plt.plot([x for x in result_up], label="Up")
    plt.legend()
    file = open(datetime.datetime.now().strftime('%m_%d_%H_%M_%S.result'), 'w')
    file.write("\n".join(str(p) for p in packages))
    plt.show()
