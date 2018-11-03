#ifndef DISPLAY_DATA_H
#define DISPLAY_DATA_H

#include "target_location.h"

extern void display_string_at_xy(uint8_t x, uint8_t y, char *str);
extern void display_int_at_xy(uint8_t x, uint8_t y, int number, int spaces);
extern void display_target_location(T_TARGET_LOCATION loc);

#endif
