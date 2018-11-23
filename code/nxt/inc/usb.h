#ifndef USB_H
#define USB_H

#include <stdbool.h>
#include "calibration.h"

#include "target_information.h"


extern bool get_target_information(T_TARGET_INFORMATION *out_location);

extern void send_calibration_data(T_POWER_TUPLE data);

#endif
