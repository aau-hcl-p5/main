#include "calibration.h"

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
int8_t get_required_power(char axis, T_DIRECTION direction);