#ifndef MOVEMENT_H
#define MOVEMENT_H

#include <stdbool.h>

#include "vector.h"
#include "revolution.h"

#define MOTOR_RANGE_Y 10
#define MOTOR_SPEED_LOWER_BOUND_Y 20

#define MOTOR_RANGE_X 10
#define MOTOR_SPEED_LOWER_BOUND_X 15


#define MAX_POWER_MODIFIER 40

#define MAGIC_NUMBER_1 100


#define MOTOR_DEADZONE 10

#define MAX_INPUT_VALUE 127


extern uint8_t x_lower_bound_modifier;
extern uint8_t y_lower_bound_modifier;

extern bool init_motor(uint8_t motor_id, char orientation, uint16_t speed);
extern bool release_motor(uint8_t motor_id);

extern void move(T_VECTOR target_location);
extern void set_motor_speed(char axis, int8_t speed);
extern void stop_motors();
extern int8_t get_speed_by_distance(int8_t distance, char axis);
extern T_REVOLUTION get_current_revolution();

#endif
