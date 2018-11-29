#ifndef USB_H
#define USB_H

#include <stdbool.h>
#include <stdint.h>
#include "calibration.h"
#include "vector.h"

#define TARGET_FOUND 0
#define NO_TARGET_FOUND 1
#define DISCONNECTED_REQ 2
#define READY_FOR_CALIBRATION 3

typedef uint16_t STATUS_CODE;

typedef struct {
    int16_t angle;
    bool is_x;
    int16_t x;
    int16_t y;
} SEND_PACKAGE;

extern bool get_status_code(STATUS_CODE *out_code);
extern bool get_target_location(T_VECTOR *out_location);
extern bool send_calibration_data(int16_t angle, bool is_x, T_POWER_TUPLE data) ;

#endif
