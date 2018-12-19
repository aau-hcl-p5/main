 from typing import List
 
 import usb
 
 from calibration.utils import Package
 from output_devices import NxtUsb, Status
 
 MAX_SEQUENTIAL_TIMEOUTS = 3
 
 
 def combine_bytes(data, index):
     return (data[index + 1] << 8) | data[index]
 
 
 def read_calibration_data(usb_controller: NxtUsb) -> List[Package]:
     """
     Listens on the USB port for packages of calibration data
     when it received enough timeouts it automatically terminates and returns the list of packages
 
     :param usb_controller: the controller attached to the NXT
     :return: returns the packages retrieved from the NXT
     """
     packages: List[Package] = []
 
     usb_controller.write_status(Status.READY_FOR_CALIBRATION)
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
         except usb.core.USBError as e:
             print(f"- ERROR {e}")
             timeout_counter += 1
             if timeout_counter > MAX_SEQUENTIAL_TIMEOUTS:
                 break
         except KeyboardInterrupt:
             break
 
     return packages
