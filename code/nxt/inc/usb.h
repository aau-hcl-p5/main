#ifndef USB_H
#define USB_H

#include <stdbool.h>

#include "target_location.h"

#define DISCONNECT_REQ 0xFFFFFFFF

typedef struct {
    int8_t position;
    char axis;
    uint8_t power;
    bool positive_direction;
} T_SEND_PACKAGE;
extern bool get_target_location(T_TARGET_LOCATION *out_location);

extern void send_calibration_data(int8_t position, char axis, uint8_t power, bool positive_direction);

#endif
