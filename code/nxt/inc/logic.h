#ifndef LOGIC_H
#define LOGIC_H
#include <stdbool.h>

#include "vector.h"

extern bool toggle_laser();
extern bool standby();
extern uint32_t get_distance(uint32_t sensor_id);
extern bool predict_trajectory(T_VECTOR point);

#endif