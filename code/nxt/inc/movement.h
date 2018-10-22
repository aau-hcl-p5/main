#ifndef MOVEMENT_H
#define MOVEMENT_H

#include "target_location.h"
#include <stdbool.h>



extern bool init_motor(uint8_t motor_id, char orientation);
bool move_to(uint8_t motor_id, int32_t degrees);
extern bool move(char direction, int32_t degrees);
extern bool release_motor(uint8_t motor_id);
extern uint32_t get_position();

#endif
