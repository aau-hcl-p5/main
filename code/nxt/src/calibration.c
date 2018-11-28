#include <math.h>

#include "display.h"
#include "nxt.h"
#include "calibration.h"
#include "vector.h"
#include "movement.h"
#include "usb.h"

#define MIN_POWER 0
#define MAX_POWER 100

T_POWER_TUPLE y_axis_powers[POINTS_ON_AXIS];
bool calibrated = false;



int8_t get_required_power(char axis, bool positive_direction) {
    if(axis == 'x')
        return 30;
    else {
        T_POWER_TUPLE power_set = y_axis_powers[get_current_location().y];
        return positive_direction ? power_set.positive : power_set.negative;
    }

}


void calibrate(bool internal) {

    // calibrate the y axis
    calibrate_axis_in_direction('y',true);
    calibrate_axis_in_direction('y',false);
    calibrate_axis_in_direction('y',true);
    calibrate_axis_in_direction('y',false);
    calibrated = true;
}

void calibrate_axis_in_direction(char axis, bool direction) {
    uint8_t power = 0;
    do
    {
        int8_t y_position = get_current_location().y;
        power = get_power_to_move_one_degree(axis, direction);
        uint16_t index = POINTS_ON_AXIS/2 + y_position;
        if(direction) {
            y_axis_powers[index].positive = power;
        }
        else {
            y_axis_powers[index].negative = power;

        }
        // if power was set to more than MAX_POWER then we used all the power we could but still couldn't move.
        // this means that this is the end

    } while(power < MAX_POWER);
}

bool is_not_enough_power(T_VECTOR original_location, int8_t power) {
    return is_locations_equals(first_location, get_current_location()) && power <= 100
}


int8_t get_power_to_move_one_degree(char axis, bool positive_direction) {
    char axis_str[3];
    axis_str[0] = axis;
    axis_str[1] = positive_direction ? '+' : '-';
    axis_str[2] = '\0';
    int8_t power = MIN_POWER;
    T_VECTOR first_location = get_current_location();

    do {
        set_motor_speed(axis, power * (positive_direction ? 1 : -1));
        power++;

        display_calibration_status(axis_str, first_location, power);
        // wait 50ms but make sure we don't move in that timeframe
        for(int i = 0; i < 50; i++)
        {
            systick_wait_ms(1);
            if(should_stop_moving(first_location, power))
                break;
        }

    } while(should_stop_moving(first_location, power));

    set_motor_speed(axis, 0);

    return power;
}
