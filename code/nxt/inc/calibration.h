#ifndef NXT_CALIBRATION_H
#define NXT_CALIBRATION_H

#include <stdbool.h>
#include "vector.h"

typedef struct {
    uint8_t negative;
    uint8_t positive;
} T_POWER_TUPLE;

typedef enum {
    POSITIVE,
    NEGATIVE
} T_DIRECTION;

#define POINTS_ON_AXIS 360

extern T_POWER_TUPLE y_axis_powers[POINTS_ON_AXIS];

extern void calibrate(bool internal);
extern int8_t get_required_power(char axis, T_DIRECTION positive_direction);

#endif //NXT_CALIBRATION_H
