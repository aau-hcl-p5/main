#ifndef MOVEMENT_H
#define MOVEMENT_H

#include <stdbool.h>
#include <stdlib.h>

#include "target_location.h"

#define MOTOR_RANGE_Y 10 // 50
#define MOTOR_SPEED_LOWER_BOUND_Y 20

#define MOTOR_RANGE_X 10 // 80
#define MOTOR_SPEED_LOWER_BOUND_X 15


#define MOTOR_DEADZONE 10

#define MAX_INPUT_VALUE 127


extern uint8_t x_lower_bound_modifier;
extern uint8_t y_lower_bound_modifier;

// actual methods

extern bool init_motor(uint8_t motor_id, char orientation, uint16_t speed);
extern bool release_motor(uint8_t motor_id);

extern bool move(T_TARGET_LOCATION target_location);
extern void stop_motors();
extern int get_speed_by_distance(int distance, char axis);
extern void move(uint8_t motor_id, int32_t speed);
extern T_TARGET_LOCATION get_current_location();

extern int readjust_lower_bound(T_TARGET_LOCATION target);


bool is_moving_too_slow(int degrees, int distance);
bool is_moving_too_fast(int degrees, int distance);

int get_range(char axis);
int get_lower_bound(char axis);
#endif
