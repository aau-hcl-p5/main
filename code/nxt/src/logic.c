#include <stdbool.h>
#include <stdint.h>

#include "nxt.h"
#include "target_location.h"
#include "movement.h"
#include "data_receive.h"

// TODO: Not global var
bool laser_state = false;

void main_loop() {
    T_TARGET_LOCATION target_location;
    if (get_target_location(&target_location)) {
        target_location.x -= 64;
        target_location.y -= 48;
        move_to(target_location);
        move_motors();
    }
}

bool toggle_laser() {
    return laser_state = !laser_state;
}

bool standby() {
    return true;
}

uint32_t get_distance(uint32_t sensor_id) {
    return 0;
}

bool predict_trajectory(T_TARGET_LOCATION point){
    return 0;
}
