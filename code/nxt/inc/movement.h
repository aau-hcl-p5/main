#ifndef MOVEMENT_H
#define MOVEMENT_H

#include "target_location.h"
#include <stdbool.h>

int MOTOR_SPEED_UPPER_BOUND = 30;
int MOTOR_SPEED_LOWER_BOUND = 15;
int MAX_INPUT_VALUE = 127;

// actual methods
extern T_TARGET_LOCATION get_current_location();

extern bool init_motor(uint8_t motor_id, char orientation, uint16_t speed);
extern bool release_motor(uint8_t motor_id);
extern bool move_to(T_TARGET_LOCATION target_location);

extern void move_motors();
extern void stop_motors();
void move_motor(uint8_t motor_id, int32_t speed);
int get_speed_by_distance(int distance);
#endif
