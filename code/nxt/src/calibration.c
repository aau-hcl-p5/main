#include <math.h>

#include "display_data.h"
#include "nxt.h"
#include "calibration.h"
#include "vector.h"
#include "movement.h"
#include "usb.h"

#define MIN_POWER 10
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
    calibrated = true;
    display_clear(0);
    display_string_at_xy(0, 0, "Finished calibration!");
}

void calibrate_axis_in_direction(char axis, bool direction) {
    display_clear(0);
    display_string_at_xy(0, 0, "Calibrating...");
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


int8_t get_power_to_move_one_degree(char axis, bool positive_direction) {
    char axis_str[2];
    axis_str[0] = axis;
    axis_str[1] = '\0';
    int8_t power = MIN_POWER;
    T_VECTOR first_location = get_current_location();
    display_string_at_xy(0, 2, "dir");
    display_string_at_xy(4, 2, positive_direction ? "+" : "-");
    display_string_at_xy(6, 2, axis_str);
    display_string_at_xy(0, 3, "pos");
    display_int_at_xy(4, 3, first_location.x, 3);
    display_int_at_xy(4, 4, first_location.y, 3);

    do {
        set_motor_speed(axis, power * (positive_direction ? 1 : -1));
        power++;

        display_string_at_xy(0, 5, "pow");
        display_int_at_xy(4, 5, power, 4);
        display_update();
        systick_wait_ms(50);

    } while(is_locations_equals(first_location, get_current_location()) && power <= 100);
    set_motor_speed(axis, 0);

    return power;
}
