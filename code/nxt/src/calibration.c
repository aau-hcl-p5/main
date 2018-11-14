#include "calibration.h"
#include "movement.h"
#include "usb.h"

#define MIN_POWER 0
typedef struct {
    uint8_t negative;
    uint8_t positive;
} T_POWER_TUPLE;

bool calibrate(bool internal) {
    T_POWER_TUPLE y_axis_powers[360];
    // calibrate the y axis
    for(int i = 0; i < 50; i++) {
        int8_t y_position = get_current_location().y;
        y_axis_powers[y_position].positive = get_power_to_move_one_degree('y', true);

    }
    for(int i = 0; i < 50; i++) {
        int8_t y_position = get_current_location().y;
        y_axis_powers[y_position].negative = get_power_to_move_one_degree('y', false);
    }

}

bool compare_locations(T_TARGET_LOCATION targ1, T_TARGET_LOCATION targ2) {
    return targ1.x == targ2.x && targ1.y == targ2.y;
}

int get_power_to_move_one_degree(char axis, bool positive_direction) {
    int power = MIN_POWER;
    T_TARGET_LOCATION first_location = get_current_location();
    do {
        set_motor_speed(axis, power);
        power++;


    } while(compare_locations(first_location, get_current_location()));
    set_motor_speed(axis, 0);

    int8_t location_on_axis = first_location.y;
    if(axis == 'x') {
        location_on_axis = first_location.x;
    }
    send_calibration_data(location_on_axis, axis, power, positive_direction);

    return power;
}

