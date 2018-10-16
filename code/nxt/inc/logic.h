#ifndef LOGIC_H
#define LOGIC_H
#include <stdbool.h>

typedef struct T_POINT {
  int x;
  int y;
  unsigned int timestamp;
} T_POINT;

extern void main_loop();

extern bool move_to(unsigned int motor_id, int degrees_x, int degrees_y);

extern bool toggle_laser(bool toggle);

extern bool standby();

extern int get_distance(unsigned int sensor_id);

extern bool predict_trajectory(T_POINT point);

#endif
