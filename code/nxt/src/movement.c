#include "movement.h"
#include "nxt.h"

uint32_t current_x = 0;
uint32_t current_y = 0;
uint8_t x_motor = 0;
uint8_t y_motor = 0;

// This method is solely for debugging and should be removed.
void display_show(int32_t data){
	ecrobot_status_monitor("STATUS");
	
	display_clear(1);
	display_goto_xy(0,0);
	display_string("Data: ");
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

// This method initializes motors and sets their speed and current position.
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

// This is called by move() and does the interaction with the motor
bool move_to(uint8_t motor_id, int32_t degrees){
	y_motor++;
	display_show(y_motor);
	GetResource(x_motor);
	get_position();
	if(degrees < 0){
		ecrobot_set_motor_mode_speed(motor_id, 1, 100);
		//degrees = -degrees;
	}
	else{
		ecrobot_set_motor_mode_speed(motor_id, 1, -100);
	}

	if(current_x <= degrees - 5 || current_x >= degrees + 5){
		display_show(666);
		ecrobot_set_motor_speed(motor_id, degrees);
		systick_wait_ms(500);
  }
		ecrobot_set_motor_mode_speed(motor_id, 1, 0);
		ReleaseResource(x_motor);
		TerminateTask();
	
  return true;
}

// Gets current motor revolution value in degrees.
// This should save both the x and y coords when another motor works.
uint32_t get_position(){
	current_x = nxt_motor_get_count(x_motor);
  return current_x;
}

// This is the method that should be called to move, the input is a direction (right, left, up or down) and an amount of degrees.
// Discuss: Should this just have negative values for left / down instead of a char?
bool move(char direction, int32_t degrees){
	if(direction == 'r'){
		move_to(x_motor, degrees);
	}
	else if(direction == 'l'){
		move_to(x_motor, -degrees);
	}
	else if(direction == 'u'){
		move_to(y_motor, degrees);	
	}
	else if(direction == 'd'){
		move_to(y_motor, -degrees);
	}
  return false;
}

// Should probably check whether motor_id is in use. But it releases the motor.
bool release_motor(uint8_t motor_id){
  nxt_motor_set_speed(motor_id, 0, 1);
  return true;
}
