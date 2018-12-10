#ifndef LASER_H
#define LASER_H
#include <stdbool.h>

#include "vector.h"

extern bool laser_state;

extern void init_laser(uint8_t l_id, uint8_t l_id_0);
extern void release_laser();
extern void toggle_laser();
extern void enable_laser();
extern void disable_laser();
extern void update_laser_power();

#endif
