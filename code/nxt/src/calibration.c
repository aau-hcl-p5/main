#include <math.h>

#include "display_data.h"
#include "nxt.h"
#include "calibration.h"
#include "movement.h"
#include "usb.h"

#define MIN_POWER 10
#define MOVEMENT_THRESHOLD 5
#define MAX_POWER 90


T_POWER_TUPLE y_axis_powers[360];

int8_t get_required_power(char axis, bool positive_direction) {
    if(axis == 'x')
        return 30;
    else {
        T_POWER_TUPLE power_set = y_axis_powers[get_current_location().y];
        return positive_direction ? power_set.positive : power_set.negative;
    }

}


bool calibrate(bool internal) {

    display_clear(0);
    // calibrate the y axis
    for(int i = 0; i < 360; i++) {
        int8_t y_position = get_current_location().y;
        y_axis_powers[y_position].positive = get_power_to_move_one_degree('y', true);
        // if power was set to more than 100 then we used all the power we could, but still couldn't move.
        // this means that this is the end.
        if(y_axis_powers[y_position].positive > MAX_POWER)
            break;

    }
    for(int i = 0; i < 360; i++) {
        int8_t y_position = get_current_location().y;
        y_axis_powers[y_position].negative = get_power_to_move_one_degree('y', false);
        // if power was set to more than 100 then we used all the power we could, but still couldn't move.
        // this means that this is the end.
        if(y_axis_powers[y_position].negative > MAX_POWER)
            break;

    }

}

void calibrate_axis_in_direction(char axis, bool direction) {
    display_clear(0);
    display_string_at_xy(0, 0, "Calibrating...");
    for(int i = 0; i < 360; i++) {
        int8_t y_position = get_current_location().y;
        y_axis_powers[y_position].negative = get_power_to_move_one_degree(axis, direction);
        // if power was set to more than 100 then we used all the power we could but still couldn't move.
        // this means that this is the end.
        if(y_axis_powers[y_position].negative >= MAX_POWER)
            break;

    }
}

double root(double n){
    double lo = 0, hi = n, mid;
    for(int i = 0 ; i < 1000 ; i++){
        mid = (lo+hi)/2;
        if(mid*mid == n) return mid;
        if(mid*mid > n) hi = mid;
        else lo = mid;
    }
    return mid;
}


int sq(int x) {
    return (x * x);
}


// Checks whether locations are the same within a margin of error of MOVEMENT_THRESHOLD
bool is_locations_equals(T_VECTOR target1, T_VECTOR target2) {

    display_string_at_xy(0, 3, "pXs");
    display_int_at_xy(4, 3, target1.x - target2.x, 3);
    display_int_at_xy(4, 4, target1.y - target2.y, 3);
    display_string_at_xy(0, 6, "dist");
    int distance = root(sq(target1.x - target2.x) + sq(target1.y - target2.y));
    display_int_at_xy(4, 6, distance, 3);
    return distance < MOVEMENT_THRESHOLD;
    //return target1.x == target2.x && target1.y == target2.y;
}

int8_t get_power_to_move_one_degree(char axis, bool positive_direction) {
    char axis_str[2];
    axis_str[0] = axis;
    axis_str[1] = '\0';
    int8_t power = MIN_POWER;
    T_VECTOR first_location = get_current_location();
    display_string_at_xy(0, 2, "dir");
    display_string_at_xy(4, 2, positive_direction ? "+" : "-");
    display_string_at_xy(5, 2, axis_str);
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

    int8_t location_on_axis = first_location.y;
    if(axis == 'x') {
        location_on_axis = first_location.x;
    }
    send_calibration_data(location_on_axis, axis, power, positive_direction);

    return power;
}
