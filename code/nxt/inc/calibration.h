#include <stdbool.h>

#ifndef NXT_CALIBRATION_H
#define NXT_CALIBRATION_H

extern bool calibrate(bool internal);
int get_power_to_move_one_degree(char axis, bool positive_direction);

#endif //NXT_CALIBRATION_H
