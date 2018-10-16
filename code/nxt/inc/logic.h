#ifndef LOGIC_H
#define LOGIC_H
#include <stdbool.h>

#include "target_location.h"

extern void main_loop();
extern bool move_to(unsigned int motor_id, int degrees_x, int degrees_y);
extern bool toggle_laser(bool toggle);
extern bool standby();
extern int get_distance(unsigned int sensor_id);
extern bool predict_trajectory(T_TARGET_LOCATION point);

#endif
