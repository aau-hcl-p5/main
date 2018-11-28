#ifndef DISPLAY_H
#define DISPLAY_H

#include "vector.h"
#include "usb.h"
#include "calibration.h"

//extern void display_string_at_xy(uint8_t x, uint8_t y, char *str);
//extern void display_int_at_xy(uint8_t x, uint8_t y, int32_t number, int32_t spaces);
extern void display_target_information(STATUS_CODE status_code, T_VECTOR target_last_location);
extern void display_calibration_transfer_status(bool positive_direction, T_POWER_TUPLE tuple);
extern void display_calibration_status(char* direction, T_VECTOR position, int power);
extern void show_init_screen();
#endif
