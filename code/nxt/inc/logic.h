#ifndef LOGIC_H
#define LOGIC_H
#include <stdbool.h>

#include "target_location.h"

extern void main_loop();
extern bool move_to(uint32_t motor_id, int32_t degrees_x, int32_t degrees_y);
extern bool toggle_laser();
extern bool standby();
extern uint32_t get_distance(uint32_t sensor_id);
extern bool predict_trajectory(T_TARGET_LOCATION point);

#endif
