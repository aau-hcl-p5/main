#include <stdbool.h>
#include <stdint.h>

#include "laser.h"
#include "nxt.h"
#include "vector.h"
#include "movement.h"
#include "usb.h"

uint8_t laser_id = 0;
uint8_t laser_id_0 = 0;

bool laser_state = false;
bool laser_state_0 = false;

void bitflip_error();

void init_laser(uint8_t l_id, uint8_t l_id_0) {
    laser_id = l_id;
    laser_id_0 = l_id_0;

    if (l_id != l_id_0) bitflip_error();
}

void release_laser() {
    ecrobot_set_motor_speed(laser_id, 0);
    if (laser_id != laser_id_0) bitflip_error();

    laser_id = 0;
    laser_id_0 = 0;
}

void toggle_laser() {
    if (!laser_state) {
        if (laser_state) bitflip_error();
        if (laser_state != laser_state_0) bitflip_error();

        enable_laser();
    } else {
        if (!laser_state) bitflip_error();
        if (laser_state != laser_state_0) bitflip_error();

        disable_laser();
    }
}

void enable_laser() {
    laser_state = true;
    laser_state_0 = true;

    update_laser_power();
}

void disable_laser() {
    laser_state = false;
    laser_state_0 = false;

    update_laser_power();
}

void update_laser_power() {
    if (laser_state) {
        if (laser_state != laser_state_0) bitflip_error();
        if (!laser_state) bitflip_error();

        ecrobot_set_motor_speed(laser_id, 100);

        if (laser_id != laser_id_0) bitflip_error();
    } else {
        if (laser_state) bitflip_error();
        if (laser_state != laser_state_0) bitflip_error();

        ecrobot_set_motor_speed(laser_id, 0);

        if (laser_id != laser_id_0) bitflip_error();
    }
}

void bitflip_error() {
    // Fault Handling; Kill all lasers, both normal and shadow variable, to ensure bitflipping may/may not have changed
    //   the id
    ecrobot_set_motor_speed(laser_id, 0);
    ecrobot_set_motor_speed(laser_id_0, 0);
}
