#ifndef MOVEMENT_H
#define MOVEMENT_H

#include <stdbool.h>

#include "vector.h"
#include "revolution.h"

#define MOTOR_RANGE_Y 10
#define MOTOR_SPEED_LOWER_BOUND_Y 20

#define MOTOR_RANGE_X 10
#define MOTOR_SPEED_LOWER_BOUND_X 15

#define AXIS_X 0
#define AXIS_Y 1

#define MAX_POWER_MODIFIER 40

#define MOTOR_DEADZONE 1

#define MAX_INPUT_VALUE 127

typedef uint8_t T_AXIS_TYPE;


extern uint8_t x_lower_bound_modifier;
extern uint8_t y_lower_bound_modifier;

/*
 * Function: init_motor
 * ----------------------------
 *   Initialises the motor on a given ID
 *
 *   motor_id: Laser ID on Port, e.g NXT_PORT_C
 *   axis: Laser ID on Port, e.g NXT_PORT_C
 *   speed: Laser ID on Port, e.g NXT_PORT_C
 */
extern bool init_motor(uint8_t motor_id, T_AXIS_TYPE axis, uint16_t speed);

/*
 * Function: release_laser
 * ----------------------------
 *   Releases and stops the laser from shooting. Must re-initialize after called.
 */
extern bool release_motor(uint8_t motor_id);

extern void move(T_VECTOR target_location);
extern void set_motor_speed(T_AXIS_TYPE axis, int8_t speed);
extern void stop_motors();
extern int8_t get_speed_by_distance(int8_t distance, T_AXIS_TYPE axis);
extern T_REVOLUTION get_current_revolution();

#endif
