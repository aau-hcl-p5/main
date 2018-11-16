#include <stdbool.h>

#ifndef NXT_CALIBRATION_H
#define NXT_CALIBRATION_H

typedef struct {
    uint8_t negative;
    uint8_t positive;
} T_POWER_TUPLE;


extern bool calibrate(bool internal);
extern int8_t get_required_power(char axis, bool positive_direction);

int8_t get_power_to_move_one_degree(char axis, bool positive_direction);
void calibrate_axis_in_direction(char axis, bool direction);
bool compare_locations(T_TARGET_LOCATION target1, T_TARGET_LOCATION target2);

#endif //NXT_CALIBRATION_H
