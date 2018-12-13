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
#define REVOLUTION_OFFSET 55

extern T_POWER_TUPLE y_axis_powers[POINTS_ON_AXIS];

/*
 * Function: calibrate
 * ----------------------------
 *   Begins calibration on both directions, AXIS_X and AXIS_Y.
 *
 *   returns: void
 */
extern void calibrate();

/*
 * Function: get_required_power
 * ----------------------------
 *   Returns required power, for moving on an axis, in a given direction
 *     on the current angle on the motor.
 *
 *   axis: AXIS_X or AXIS_Y for which axis power is required
 *   positive_direction: POSITIVE or NEGATIVE for which direction, on the axis.
 *
 *   returns: the required power for moving a given direction on a given axis.
 */
extern int8_t get_required_power(T_AXIS_TYPE axis, T_DIRECTION positive_direction);


#endif //NXT_CALIBRATION_H
