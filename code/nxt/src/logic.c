#include <stdbool.h>
#include <stdint.h>

#include "nxt.h"
#include "target_information.h"
#include "movement.h"
#include "data_receive.h"

// TODO: Not global var
bool laser_state = false;

void main_loop() {}

bool toggle_laser() {
    return laser_state = !laser_state;
}

bool standby() {
    return true;
}

uint32_t get_distance(uint32_t sensor_id) {
    return 0;
}

bool predict_trajectory(T_TARGET_LOCATION point) {
    return 0;
}