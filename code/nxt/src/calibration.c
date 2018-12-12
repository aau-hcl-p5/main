#include <math.h>

#include "display_manager.h"
#include "nxt.h"
#include "calibration.h"
#include "vector.h"
#include "movement.h"
#include "usb.h"

// Checks whether revolutions are the same within a margin of error of MIN_REVOLUTION_THRESHOLD
bool revolutions_equals(T_REVOLUTION target1, T_REVOLUTION target2, char axis) {
    int16_t max_value, min_value;
    if (axis == 'x') {
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
    return revolutions_equals(first_revolution, get_current_revolution(), 'y') && power <= 100;
}

int8_t get_power_to_move_one_degree(char axis, T_DIRECTION direction) {
    char axis_str[3];
    axis_str[0] = axis;
    axis_str[1] = direction == POSITIVE ? '+' : '-';
    axis_str[2] = '\0';
    int8_t power = MIN_POWER;
    T_REVOLUTION first_revolution = get_current_revolution();

    do {
        set_motor_speed(axis, power * (direction == POSITIVE ? 1 : -1));
        power++;

        display_calibration_status(axis_str, first_revolution, power);
        // wait 30ms but make sure we don't move in that timeframe
        for(int i = 0; i < 30; i++)
        {
            systick_wait_ms(1);
            if (!should_stop_moving(first_revolution, power))
                break;
        }

    } while(should_stop_moving(first_revolution, power));

    set_motor_speed(axis, 0);

    return power;
}

void calibrate_axis_in_direction(char axis, T_DIRECTION direction) {
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

void calibrate(bool internal) {
    // calibrate the y axis
    for (int i = 0; i < 2; i++) {
        calibrate_axis_in_direction('y', i % 2 == 0 ? POSITIVE : NEGATIVE);
    }
}

