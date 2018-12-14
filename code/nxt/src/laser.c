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

/*
 * Function: init_laser
 * ----------------------------
 *   Initialises the laser on a given ID
 *
 *   l_id: Laser ID on Port, e.g NXT_PORT_C
 *   l_id_0: Shadow variable of above. Must be equal.
 */
void init_laser(uint8_t l_id, uint8_t l_id_0) {
    laser_id = l_id;
    laser_id_0 = l_id_0;

    if (l_id != l_id_0) bitflip_error();
}

/*
 * Function: release_laser
 * ----------------------------
 *   Releases and stops the laser from shooting. Also unsets `laser_id`.
 */
void release_laser() {
    ecrobot_set_motor_speed(laser_id, 0);
    if (laser_id != laser_id_0) bitflip_error();

    laser_state = false;
    laser_state_0 = false;
    laser_id = 0;
    laser_id_0 = 0;
}

/*
 * Function: toggle_laser
 * ----------------------------
 *   Toggles the laser. If on then off, otherwise on.
 *     Relies on laser_state and uses enable_laser and disable_laser.
 */
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

/*
 * Function: enable_laser
 * ----------------------------
 *   Enables laser, even if on already.
 *     Calls update_laser_power() to ensure power to the NXT Port.
 */
void enable_laser() {
    laser_state = true;
    laser_state_0 = true;

    update_laser_power();
}

/*
 * Function: disable_laser
 * ----------------------------
 *   Disables laser, even if off already.
 *     Calls update_laser_power() to ensure power to the NXT Port.
 */
void disable_laser() {
    laser_state = false;
    laser_state_0 = false;

    update_laser_power();
}

/*
 * Function: update_laser_power
 * ----------------------------
 *   Sets the power to ON on the laser, given the current laser state.
 *     Called from toggle_laser, enable_laser and disable_laser.
 *     Uses ecrobot_set_motor_speed, to the laser_id, NXT_PORT_X from init_laser
 */
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

/*
 * Function: bitflip_error
 * ----------------------------
 *   Fallback method, to ensure motor is off, state is ok, and be a fault tolerance and recovery,
 *     and reinitialize to NXT_PORT_C.
 */
void bitflip_error() {
    // Fault Handling; Kill all lasers, both normal and shadow variable, to ensure bitflipping may/may not have changed
    //   the id
    ecrobot_set_motor_speed(laser_id, 0);
    ecrobot_set_motor_speed(laser_id_0, 0);
    laser_state = false;
    laser_state_0 = false;
    init_laser(NXT_PORT_C, NXT_PORT_C);
}
