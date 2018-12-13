#ifndef LASER_H
#define LASER_H
#include <stdbool.h>

#include "vector.h"

extern bool laser_state;
extern bool laser_state_0;

/*
 * Function: init_laser
 * ----------------------------
 *   Initialises the laser on a given ID
 *
 *   l_id: Laser ID on Port, e.g NXT_PORT_C
 *   l_id_0: Shadow variable of above. Must be equal.
 */
extern void init_laser(uint8_t l_id, uint8_t l_id_0);

/*
 * Function: release_laser
 * ----------------------------
 *   Releases and stops the laser from shooting. Must re-initialize after called.
 */
extern void release_laser();

/*
 * Function: toggle_laser
 * ----------------------------
 *   Toggles the laser. If on then off, otherwise on.
 */
extern void toggle_laser();

/*
 * Function: enable_laser
 * ----------------------------
 *   Enables laser, even if on already.
 */
extern void enable_laser();

/*
 * Function: disable_laser
 * ----------------------------
 *   Disables laser, even if off already.
 */
extern void disable_laser();

/*
 * Function: update_laser_power
 * ----------------------------
 *   Sets the power to ON on the laser, given the current laser state.
 *     Called from toggle_laser, enable_laser and disable_laser.
 */
extern void update_laser_power();

#endif
