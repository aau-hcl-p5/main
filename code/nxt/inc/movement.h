#ifndef MOVEMENT_H
#define MOVEMENT_H

#include "target_location.h"
#include <stdbool.h>

// actual methods
extern T_TARGET_LOCATION get_current_location();

extern bool init_motor(uint8_t motor_id, char orientation, uint16_t speed);
extern bool release_motor(uint8_t motor_id);
extern bool move_to(T_TARGET_LOCATION target_location);

extern void move_motors();
extern void stop_motors();
void move_motor(uint8_t motor_id, int32_t speed);
#endif
