#ifndef DISPLAY_DATA_H
#define DISPLAY_DATA_H

#include "target_information.h"

extern void show_init_screen();
extern void display_string_at_xy(uint8_t x, uint8_t y, char *str);
extern void display_int_at_xy(uint8_t x, uint8_t y, int32_t number, int32_t spaces);
extern void display_target_information(T_TARGET_INFORMATION target_information);

#endif
