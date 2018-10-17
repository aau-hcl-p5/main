#include "movement.h"
#include "nxt.h"

uint32_t current_x = 0;
uint32_t current_y = 0;
uint8_t x_motor = 0;
uint8_t y_motor = 0;

bool init_motor(uint8_t motor_id, char orientation){
  if(orientation == 'x'){
  	x_motor = motor_id;
    current_x = get_position(x_motor);
    ecrobot_set_motor_speed(x_motor, 0);
    return true;
	}else if(orientation = 'y'){
    y_motor = motor_id;
    current_y = get_position(y_motor);
    ecrobot_set_motor_speed(y_motor, 0);
    return true;
  }
  return false;
}

bool move_to(uint8_t motor_id, int32_t degrees){
  nxt_motor_set_count(motor_id, degrees);
  return true;
}

// should return x and y as one number set.
uint32_t get_position(){
  return ecrobot_get_motor_rev(x_motor);
}

bool move(char direction, int32_t degrees){
	if(direction = 'r'){
		current_x += degrees;
		move_to(x_motor, current_x);
	}
	else if(direction = 'l'){
		current_x -= degrees;
		move_to(x_motor, current_x);
	}
	else if(direction = 'u'){
		current_y += degrees;
		move_to(y_motor, current_y);	
	}
	else if(direction = 'd'){
		current_y -= degrees;
		move_to(y_motor, current_y);
	}
  return false;
}

// Should probably check whether motor_id is in use.
bool release_motor(uint8_t motor_id){
  ecrobot_set_motor_speed(motor_id, 0);
  return true;
}
