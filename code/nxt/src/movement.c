#include <stdlib.h>

#include "movement.h"
#include "nxt.h"
#include "calibration.h"

uint8_t x_motor = 0;
uint8_t y_motor = 0;
uint16_t x_motor_speed = 0;
uint16_t y_motor_speed = 0;



uint8_t x_lower_bound_modifier = 0;
uint8_t y_lower_bound_modifier = 0;

T_VECTOR last_location = {0, 0};


/*--------------------------------------------------------------------------*/
/* move_motors:                                                             */
/* ------------------------------------------------------------------------ */
/* Description:                                                             */
/* Params  : T_VECTOR target: Information about the target         */
/*              location.                                                   */
/* Returns : None                                                           */
/*--------------------------------------------------------------------------*/

void move(T_VECTOR target) {
    // speed is 0 when distance is small enough.
    set_motor_speed('x', get_speed_by_distance(target.x, 'x'));
    set_motor_speed('y', -get_speed_by_distance(target.y, 'y'));
}

void set_motor_speed(char axis, int8_t speed) {
    uint8_t motor = y_motor;
    if (axis == 'x'){
        motor = x_motor;
    }

    ecrobot_set_motor_speed(motor, speed);
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

bool init_motor(uint8_t motor_id, char orientation, uint16_t speed) {
    if(orientation == 'x') {
        x_motor = motor_id;
        x_motor_speed = speed;
        ecrobot_set_motor_speed(x_motor, 0);
        nxt_motor_set_count(x_motor, 0);
        last_location.x = ecrobot_get_motor_rev(motor_id);
        return true;
    }
    else if(orientation == 'y') {
        y_motor = motor_id;
        y_motor_speed = speed;
        ecrobot_set_motor_speed(y_motor, 0);
        nxt_motor_set_count(y_motor, 0);
        last_location.y = ecrobot_get_motor_rev(motor_id);
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

void stop_motors() {
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
bool release_motor(uint8_t motor_id) {
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
int8_t get_speed_by_distance(int8_t distance, char axis) {
    if(distance < MOTOR_DEADZONE && distance > -MOTOR_DEADZONE) {
        return 0;
    }


    uint8_t lower_bound = get_required_power(axis, distance >= 0);
    uint8_t range = 10;

    // if distance is negative, then MOTOR_SPEED_LOWER_BOUND should be negative,
    // otherwise we don't get a value in the expected range
    int8_t actual_lower_bound = lower_bound * ((distance >= 0) ? 1 : -1);

    return -((distance * range) / MAX_INPUT_VALUE + actual_lower_bound);
}


T_VECTOR get_current_location() {

    T_VECTOR location = {ecrobot_get_motor_rev(x_motor), ecrobot_get_motor_rev(y_motor), 0};
    return location;
}