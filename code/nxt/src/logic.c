/*
 * This files is mostly created in order to have a starting point for additional files besides nxt.c
 * Feel free to remove it.
 */
#include <stdbool.h>
#include <stdint.h>

#include "nxt.h"
#include "target_location.h"
#include "movement.h"
#include "movement.c"

// TODO: Not global var
bool laser_state = false;

void main_loop() {
    move('l', 50);
}

bool toggle_laser() {
    return (laser_state = !laser_state);
}

bool standby() {
    // Do actual stuff here
    return standby;
}

uint32_t get_distance(uint32_t sensor_id) {
    return 0;
}

bool predict_trajectory(T_TARGET_LOCATION point){
    return 0;
}

