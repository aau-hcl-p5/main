#include "movement.h"
#include "nxt.h"


uint32_t max_x = 360;
uint32_t max_y = 360;
uint32_t current_x = 0;
uint32_t current_y = 0;
uint8_t x_motor = 0;
uint8_t y_motor = 0;

bool init_motor(uint8_t motor_id, char orientation){
  if(orientation == 'x'){
  	x_motor = motor_id;
    ecrobot_set_motor_speed(x_motor, 0);
	  nxt_motor_set_count(x_motor, 0);
    current_x = get_position(x_motor);
    return true;
	}
	else if(orientation == 'y'){
    y_motor = motor_id;
    ecrobot_set_motor_speed(y_motor, 0);
	  nxt_motor_set_count(y_motor, 0);
    current_y = get_position(y_motor);
    return true;
  }

  return false;
}

void display_show(int32_t data){
	display_clear(1);
	display_goto_xy(0,0);
	display_string("Input: ");
	display_goto_xy(0,1);
	display_int(data, 7);

	display_goto_xy(0,2);
	display_string("Get_pos: ");
	display_goto_xy(0,3);
	display_int(get_position(), 7);


	display_goto_xy(0,4);
	display_string("Current_x: ");
	display_goto_xy(0,5);
	display_int(current_x, 7);
}

bool move_to(uint8_t motor_id, int32_t degrees){
	if(degrees < 0){
		ecrobot_set_motor_speed(motor_id, -100);
		degrees = -degrees;
	}
	else{
		ecrobot_set_motor_speed(motor_id, 100);
	}
	display_show(degrees);

  nxt_motor_set_count(motor_id, degrees);
	while(get_position() >= degrees + 10 && get_position() <= degrees - 10){
		systick_wait_ms(1);
	}
	ecrobot_set_motor_speed(motor_id, 0);
  return true;
}

// should return x and y as one number set.
uint32_t get_position(){
  return ecrobot_get_motor_rev(x_motor);
}

// check if you are trying to move beyond max_x and max_y.
bool move(char direction, int32_t degrees){
	display_show(degrees);
	if(direction == 'r'){
		current_x += degrees;
		move_to(x_motor, degrees);
	}
	else if(direction == 'l'){
		current_x -= degrees;
		move_to(x_motor, -degrees);
	}
	else if(direction == 'u'){
		current_y += degrees;
		move_to(y_motor, current_y);	
	}
	else if(direction == 'd'){
		current_y -= degrees;
		move_to(y_motor, -current_y);
	}
	systick_wait_ms(500);
  return false;
}

// Should probably check whether motor_id is in use.
bool release_motor(uint8_t motor_id){
  nxt_motor_set_speed(motor_id, 0, 1);
  return true;
}
