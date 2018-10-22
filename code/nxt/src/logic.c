/*
 * This files is mostly created in order to have a starting point for additional files besides nxt.c
 * Feel free to remove it.
 */
#include <stdbool.h>
#include <stdint.h>

#include "nxt.h"
#include "target_location.h"

// TODO: Not global var
bool laser_state = false;

void main_loop() {
    ecrobot_status_monitor("HCL-P5 READY!");
    systick_wait_ms(500); /* 500msec wait */
}

bool move_to(uint32_t motor_id, int32_t degrees_x, int32_t degrees_y) {
    return true;
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

