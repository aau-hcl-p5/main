#include <math.h>

#include "display_manager.h"
#include "nxt.h"
#include "calibration.h"
#include "vector.h"
#include "movement.h"
#include "usb.h"

#define MIN_POWER 0
#define MAX_POWER 100
#define MIN_REVOLUTION_THRESHOLD 3
#define REVOLUTION_OFFSET 55

// Checks whether revolutions are the same within a margin of error of MIN_REVOLUTION_THRESHOLD
bool revolutions_equals(T_REVOLUTION target1, T_REVOLUTION target2, T_AXIS_TYPE axis) {
    int16_t max_value, min_value;
    if (axis == AXIS_X) {
        if (target1.x > target2.x) {
            max_value = target1.x;
            min_value = target2.x;
        } else {
            max_value = target2.x;
            min_value = target1.x;
        }
    } else {
        if (target1.y > target2.y) {
            max_value = target1.y;
            min_value = target2.y;
        } else {
            max_value = target2.y;
            min_value = target1.y;
        }
    }
    return max_value - min_value < MIN_REVOLUTION_THRESHOLD;
}

T_POWER_TUPLE y_axis_powers[POINTS_ON_AXIS];

bool should_stop_moving(T_REVOLUTION first_revolution, int8_t power) {
    return revolutions_equals(first_revolution, get_current_revolution(), AXIS_Y) && power <= 100;
}

int8_t get_power_to_move_one_degree(T_AXIS_TYPE axis, T_DIRECTION direction) {
    char axis_str[3];
    axis_str[0] = axis == AXIS_X ? 'x' : 'y';
    axis_str[1] = direction == POSITIVE ? '+' : '-';
    axis_str[2] = '\0';
    int8_t power = MIN_POWER;
    T_REVOLUTION first_revolution = get_current_revolution();

    do {
        set_motor_speed(axis, power * (direction == POSITIVE ? 1 : -1));
        power++;

        display_calibration_status(axis_str, first_revolution, power);
        // wait 15ms but make sure we don't move in that timeframe
        for(int i = 0; i < 15; i++)
        {
            systick_wait_ms(1);
            if (!should_stop_moving(first_revolution, power))
                break;
        }

    } while(should_stop_moving(first_revolution, power));

    set_motor_speed(axis, 0);

    return power;
}

/*
 * Function: calibrate_axis_in_direction
 * ----------------------------
 *   Runs a loop for current angle returns when failed attempts of movement has happend.
 *     Otherwise it sets the y_axis_powers accordingly, and updates variables for movement, until done.
 *
 *   axis: AXIS_X or AXIS_Y for which axis power is required
 *   direction: a direction, positive or negative.
 *
 *   returns: void
 */
void calibrate_axis_in_direction(T_AXIS_TYPE axis, T_DIRECTION direction) {
    int16_t last_revolution = direction == POSITIVE ? -1 : 0xFFF;
    uint8_t failed_movements = 0;
    for (;;) {
        int16_t y_revolution = get_current_revolution().y;
        if ((y_revolution <= last_revolution && direction == POSITIVE) ||
            (y_revolution >= last_revolution && direction == NEGATIVE)) {
            failed_movements++;
            if (failed_movements > 5) {
                return;
            }
        }

        int8_t power = get_power_to_move_one_degree(axis, direction);
        if (direction == POSITIVE) {
            y_axis_powers[y_revolution + REVOLUTION_OFFSET].positive = power;
            T_POWER_TUPLE power_tuple = { 0, power };
            send_calibration_data(y_revolution + REVOLUTION_OFFSET, false, power_tuple);
        }
        else {
            y_axis_powers[y_revolution + REVOLUTION_OFFSET].negative = power;
            T_POWER_TUPLE power_tuple = { power, 0 };
            send_calibration_data(y_revolution + REVOLUTION_OFFSET, false, power_tuple);
        }
        last_revolution = y_revolution;
    }
}

/*
 * Function: calibrate
 * ----------------------------
 *   Begins calibration on both directions on the AXIS_Y axis
 *     using calibrate_axis_in_direction(AXIS_Y, direction), and direction
 *
 *   returns: void
 */
void calibrate() {
    // calibrate the y axis
    for (int i = 0; i < 2; i++) {
        calibrate_axis_in_direction(AXIS_Y, i % 2 == 0 ? POSITIVE : NEGATIVE);
    }
}

/*
 * Function: get_required_power
 * ----------------------------
 *   Using get_current_revolution() and the y_axis_powers for determining
 *     the required power on a direction.
 *     for x, this is always 15.
 *
 *   axis: AXIS_X or AXIS_Y for which axis power is required
 *   positive_direction: POSITIVE or NEGATIVE for which direction, on the axis.
 *
 *   returns: the required power for moving a given direction on a given axis.
 */
int8_t get_required_power(T_AXIS_TYPE axis, T_DIRECTION positive_direction) {
    if (axis == AXIS_X) {
        return 15;
    } else {
        T_POWER_TUPLE power_set = y_axis_powers[get_current_revolution().y + REVOLUTION_OFFSET];
        return positive_direction ? power_set.positive : power_set.negative;
    }
}
