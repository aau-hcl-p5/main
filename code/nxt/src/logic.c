/*
 * This files is mostly created in order to have a starting point for additional files besides nxt.c
 * Feel free to remove it.
 */
#include "stdbool.h"
#include "nxt.h"

// TODO: Not global var
bool laser_state = false;

void main_loop() {
  ecrobot_status_monitor("HCL-P5 READY!");
  systick_wait_ms(500); /* 500msec wait */
}


bool move_to(uint motor_id, int degrees) { 
  return true;
}

bool toggle_laser() {
  return (laser_state = !laser_state);
}

bool standby(bool standby) { 
  // Do actual stuff here
  return standby;
}

int get_distance(uint sensor_id) { 
  return 0;
}

int predict_trajectory(int pos_x, int pos_y){
	return 0;
}