#ifndef DISPLAY_H_H
#define DISPLAY_H_H

#include <stdbool.h>

#include "vector.h"
#include "usb.h"
#include "calibration.h"

extern void show_init_screen();
extern void display_target_information(STATUS_CODE status_code, T_VECTOR target_last_location);
extern void display_calibration_transfer_status(int i, T_POWER_TUPLE tuple);
extern void display_calibration_status(char* direction, T_VECTOR position, int power);
#endif
