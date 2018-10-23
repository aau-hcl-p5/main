/*
 * This files is mostly created in order to have a starting point for additional files besides nxt.c
 * Feel free to remove it.
 */
#include <stdbool.h>
#include <stdint.h>

#include "nxt.h"
#include "target_location.h"
#include "movement.h"
#include "movement.c"

// TODO: Not global var
bool laser_state = false;

//TODO: Test variables, should be replaced with receiving data from USB.
int test = 0;
T_TARGET_LOCATION info;


void main_loop() {
  // Everything in here should be replaced with receiving data from USB.
  if(test < 5*10000){
    info.x = 0;
    info.y = 0;
  }
  else if(test > 5*10000 && test < 10*10000){
    info.x = -30;
  }
  else if(test > 10*10000 && test < 15*10000){
    info.y = -30;
  }
  else if(test > 15*10000 && test < 20*10000){
    info.x = 30;
  }
  else if(test > 20*10000 && test < 25*10000){
    info.y = 30;
  }


  if(test < 25*10000)
    test++;
  else
    test = 0;

  move_to(info);
}

bool toggle_laser() {
  return laser_state = !laser_state;
}

bool standby() {
  T_TARGET_LOCATION standby = { standby.x = 0, standby.y = 0 };
  move_to(standby);
  return true;
}

uint32_t get_distance(uint32_t sensor_id) {
  return 0;
}

bool predict_trajectory(T_TARGET_LOCATION point){
  return 0;
}
