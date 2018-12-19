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
#define MIN_POWER 0
#define MAX_POWER 100
#define MIN_REVOLUTION_THRESHOLD 2
#define REVOLUTION_OFFSET 20

extern T_POWER_TUPLE y_axis_powers[POINTS_ON_AXIS];

/*
 * Function: calibrate
 * ----------------------------
 *   Begins calibration on both directions, AXIS_X and AXIS_Y.
 *
 *   returns: void
 */
extern void calibrate();



#endif //NXT_CALIBRATION_H
