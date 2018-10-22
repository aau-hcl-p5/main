#include "movement.h"
#include "nxt.h"

uint32_t current_x = 0;
uint32_t current_y = 0;
uint32_t target_x = 0;
uint32_t target_y = 0;

uint8_t x_motor = 0;
uint8_t y_motor = 0;

// This method is solely for debugging and should be removed.
void display_show(int32_t data){
	//ecrobot_status_monitor("STATUS");
	
	display_clear(1);
	display_goto_xy(0,0);
	display_string("Data: ");
	display_goto_xy(0,1);
	display_int(data, 7);

	display_goto_xy(0,2);
	display_string("Target_x: ");
	display_goto_xy(0,3);
	display_int(target_x, 7);

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
	// GetResource(x_motor);
	//display_show(degrees);
	get_position();
	display_show(degrees);
		if(current_x < target_x){
			ecrobot_set_motor_mode_speed(motor_id, 1, 100);
		}
		else{
			ecrobot_set_motor_mode_speed(motor_id, 1, -100);
		}
  systick_wait_ms(500);
	//Stop motion.
	//ecrobot_set_motor_mode_speed(motor_id, 1, 0);
	//ReleaseResource(x_motor);
	//TerminateTask();
	
  return true;
}

// Gets current motor revolution value in degrees.
// This should save both the x and y coords when another motor works.
uint32_t get_position(){
	current_x = nxt_motor_get_count(x_motor);
  return current_x;
}

// This is the method that should be called to move, the input is a direction (x or y) and an amount of degrees.
bool move(char direction, int32_t degrees){
	get_position();
	if(direction == 'x'){
		target_x = degrees;
		move_to(x_motor, degrees);
	}
	else if(direction == 'y'){
		target_y += degrees;	
		move_to(y_motor, degrees);
	}
  return false;
}

// Should probably check whether motor_id is in use. But it releases the motor.
bool release_motor(uint8_t motor_id){
  nxt_motor_set_speed(motor_id, 0, 1);
  return true;
}
