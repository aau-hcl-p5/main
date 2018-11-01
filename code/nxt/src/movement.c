#include "movement.h"
#include "nxt.h"

uint8_t x_motor = 0;
uint8_t y_motor = 0;
uint16_t x_motor_speed = 0;
uint16_t y_motor_speed = 0;

T_TARGET_LOCATION target_location;
T_TARGET_LOCATION current_location;

/*--------------------------------------------------------------------------*/
/* Get_current_location:                                                    */
/* ------------------------------------------------------------------------ */
/* Description: This method is used to find the current location that the 	*/
/*							robot is aiming at.															            */
/* Params  : None                                                           */
/* Returns : Returns current location, so that it can be accessed from      */
/*           the outside.                                                   */
/*--------------------------------------------------------------------------*/

T_TARGET_LOCATION get_current_location(){
  return current_location;
}

/*--------------------------------------------------------------------------*/
/* move_to:                                                                 */
/* ------------------------------------------------------------------------ */
/* Description: This method evaluates if the robot can hit the target.      */
/* Params  : T_TARGET_LOCATION target: Information about the target         */
/*              location.                                                   */
/* Returns : A boolean value based on whether the move is possible in       */
/*            relation to the max_x and max_y values.                       */
/*--------------------------------------------------------------------------*/

bool move_to(T_TARGET_LOCATION target){
    target_location = target;
  return true;
}


/*--------------------------------------------------------------------------*/
/* move_motors:                                                             */
/* ------------------------------------------------------------------------ */
/* Description: The method that interacts with the motors, should be called */
/*               whenever the target_location is updated.                   */
/*               Updates the current location before each run.              */
/* Params  : None                                                           */
/* Returns : None                                                           */
/*--------------------------------------------------------------------------*/

void move_motors(){
  current_location.x = ecrobot_get_motor_rev(x_motor);
  current_location.y = ecrobot_get_motor_rev(y_motor);

  T_TARGET_LOCATION actual_target_location = {current_location.x + target_location.x,
                                              current_location.y + target_location.y,
                                              target_location.timestamp};

  // speed is 0 when distance is small enough.
  ecrobot_set_motor_speed(x_motor, get_speed_by_distance(actual_target_location.x));
  ecrobot_set_motor_speed(y_motor, get_speed_by_distance(actual_target_location.y));

}

/*--------------------------------------------------------------------------*/
/* init_motor:                                                              */
/* ------------------------------------------------------------------------ */
/* Description: Used to initialize a motor before it is used the first time.*/
/* Params  : motor_id: The ID of the motor. Value should be NXT_PORT_(port).*/
/*           orientation: Specifies if the motor handles horizontal (x) or  */
/*                        vertical (y) movement.                            */
/*           speed: The speed of the motor. Value between 0 and 100.        */
/* Returns : None                                                           */
/*--------------------------------------------------------------------------*/

bool init_motor(uint8_t motor_id, char orientation, uint16_t speed){
  if(orientation == 'x'){
    x_motor = motor_id;
    x_motor_speed = speed;
    ecrobot_set_motor_speed(x_motor, 0);
    nxt_motor_set_count(x_motor, 0);
    current_location.x = ecrobot_get_motor_rev(motor_id);
    return true;
  }
  else if(orientation == 'y'){
    y_motor = motor_id;
    y_motor_speed = speed;
    ecrobot_set_motor_speed(y_motor, 0);
    nxt_motor_set_count(y_motor, 0);
    current_location.y = ecrobot_get_motor_rev(motor_id);
    return true;
  }
  return false;
}

/*--------------------------------------------------------------------------*/
/* stop_motors:                                                             */
/* ------------------------------------------------------------------------ */
/* Description: Is used to stop all motion on the motors.                   */
/* Params  : None                                                           */
/* Returns : None                                                           */
/*--------------------------------------------------------------------------*/

void stop_motors(){
  nxt_motor_set_speed(x_motor, 0, 1);
  nxt_motor_set_speed(y_motor, 0, 1);
}

/*--------------------------------------------------------------------------*/
/* release_motors:                                                          */
/* ------------------------------------------------------------------------ */
/* Description: Used to release the motors when they are no longer in use.  */
/* Params  : motor_id specifies witch motor is released.                    */
/* Returns : returns true if the release was succesful.                     */
/*--------------------------------------------------------------------------*/
// Should probably check whether motor_id is in use. But it releases the motor.
bool release_motor(uint8_t motor_id){
  nxt_motor_set_speed(motor_id, 0, 1);
  return true;
}


/*--------------------------------------------------------------------------*/
/* get_speed_by_distance:                                                   */
/* ------------------------------------------------------------------------ */
/* Description: Gets the motor speed needed, based on distance on axis      */
/* Params  : distance on a given axis from center to target                 */
/* Returns : the motor speed (-100->100) that the motor should move         */
/*--------------------------------------------------------------------------*/
int get_speed_by_distance(int distance) {
  // 2 is a magic number that symbolizes the minimum distance for movement to be relevant.
  if(distance < 2){
    return 0;
  }

  int range = MOTOR_SPEED_UPPER_BOUND - MOTOR_SPEED_LOWER_BOUND;
  // if distance is negative, then MOTOR_SPEED_LOWER_BOUND should be negative,
  // otherwise we don't get a value in the expected range
  int actual_lower_bound = MOTOR_SPEED_LOWER_BOUND * ((distance >= 0) ? 1 : -1);

  return -(distance * range) / MAX_INPUT_VALUE + actual_lower_bound;
}
