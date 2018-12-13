#include <stdlib.h>

#include "movement.h"
#include "nxt.h"
#include "calibration.h"
#include "revolution.h"
#include "model_adapter.h"
#include "display_manager.h"
#include "math.h"

uint8_t x_motor = 0;
uint8_t y_motor = 0;
int16_t x_motor_speed = 0;
int16_t y_motor_speed = 0;

uint8_t x_lower_bound_modifier = 0;
uint8_t y_lower_bound_modifier = 0;

T_VECTOR last_location = {0, 0};


/*--------------------------------------------------------------------------*/
/* move_motors:                                                             */
/* ------------------------------------------------------------------------ */
/* Description:                                                             */
/* Params  : T_VECTOR target: Information about the target                  */
/*              location.                                                   */
/* Returns : None                                                           */
/*--------------------------------------------------------------------------*/

void move(T_VECTOR target) {
    // speed is 0 when distance is small enough.
    x_motor_speed = get_speed_by_distance(target.x, 'x');
    y_motor_speed = get_speed_by_distance(target.y, 'y');
    set_motor_speed('x', x_motor_speed);
    set_motor_speed('y', y_motor_speed);
}

void set_motor_speed(T_AXIS_TYPE axis, int8_t speed) {
    uint8_t motor = y_motor;
    if (axis == AXIS_X){
        motor = x_motor;
    }

    ecrobot_set_motor_speed(motor, speed);
}


/*--------------------------------------------------------------------------*/
/* init_motor:                                                              */
/* ------------------------------------------------------------------------ */
/* Description: Used to initialize a motor before it is used the first time.*/
/* Params  : motor_id: The ID of the motor. Value should be NXT_PORT_(port).*/
/*           axis: Specifies if the motor handles horizontal (x) or         */
/*                 vertical (y) movement.                                   */
/*           speed: The speed of the motor. Value between 0 and 100.        */
/* Returns : None                                                           */
/*--------------------------------------------------------------------------*/

bool init_motor(uint8_t motor_id, T_AXIS_TYPE axis, uint16_t speed) {
    if (axis == AXIS_X) {
        x_motor = motor_id;
        x_motor_speed = speed;
        ecrobot_set_motor_speed(x_motor, 0);
        nxt_motor_set_count(x_motor, 0);
        last_location.x = ecrobot_get_motor_rev(motor_id);
        return true;
    } else if(axis == AXIS_Y) {
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


/*
 * Description: Gets the motor speed needed, based on distance on axis
 * Params  :
 *      distance:   range: -127 -> 127 on axis
 *      axis:       'x' or 'y'
 * Returns : the motor speed (-100->100) that the motor should move
 */
int8_t get_speed_by_distance(int8_t distance, T_AXIS_TYPE axis) {
    if (distance < MOTOR_DEADZONE && distance > -MOTOR_DEADZONE) {
        return 0;
    }

    int8_t lower_bound = get_required_power(axis, distance >= 0) * ((distance >= 0) ? 1 : -1);
    //lower_bound = lower_bound - (lower_bound / 5);

    //return (POWER_RANGE * distance / MAX_INPUT_VALUE) + lower_bound;
    return (distance / 5) + lower_bound - (lower_bound / 5);
}


T_REVOLUTION get_current_revolution() {
    T_REVOLUTION revolution = {ecrobot_get_motor_rev(x_motor), ecrobot_get_motor_rev(y_motor)};
    return revolution;
}
