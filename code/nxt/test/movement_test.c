#include <stdbool.h>

#include "stubs.h"
#include "movement_test.h"
#include "test_framework.h"
#include "movement.h"

T_TC_RESULT test_motor_init() {
    T_TC_RESULT res = TC_SUCCESS;
    res |= assert_bool_equals(true, init_motor(NXT_PORT_A, 'y', 20));
    res |= assert_bool_equals(true, init_motor(NXT_PORT_B, 'x', 20));
    T_MOTOR motor_a = get_motor_attributes(NXT_PORT_A);
    T_MOTOR motor_b = get_motor_attributes(NXT_PORT_B);
    res |= assert_num_equals(0, motor_a.speed);
    res |= assert_num_equals(0, motor_b.speed);
    res |= assert_num_equals(1, motor_a.should_break);
    res |= assert_num_equals(1, motor_b.should_break);
    res |= assert_num_equals(0, motor_a.rev);
    res |= assert_num_equals(0, motor_b.rev);
    return res;
}
T_TC_RESULT test_motor_init_illegal_axis() {
    return init_motor(NXT_PORT_A, 'z', 20) ? TC_ERROR : TC_SUCCESS;
}
T_TC_RESULT test_stop_motors() {
    T_TC_RESULT res = TC_SUCCESS;
    res |= assert_bool_equals(true, init_motor(NXT_PORT_A, 'y', 20));
    res |= assert_bool_equals(true, init_motor(NXT_PORT_B, 'x', 20));
    stop_motors();
    T_MOTOR motor_a = get_motor_attributes(NXT_PORT_A);
    T_MOTOR motor_b = get_motor_attributes(NXT_PORT_B);
    res |= assert_num_equals(0, motor_a.speed);
    res |= assert_num_equals(0, motor_b.speed);
    res |= assert_num_equals(1, motor_a.should_break);
    res |= assert_num_equals(1, motor_b.should_break);
    return res;
}
T_TC_RESULT test_motor_release() {
    T_TC_RESULT res = TC_SUCCESS;
    res |= assert_bool_equals(true, init_motor(NXT_PORT_A, 'y', 20));
    res |= assert_bool_equals(true, init_motor(NXT_PORT_B, 'x', 20));
    release_motor(NXT_PORT_A);
    release_motor(NXT_PORT_B);
    T_MOTOR motor_a = get_motor_attributes(NXT_PORT_A);
    T_MOTOR motor_b = get_motor_attributes(NXT_PORT_B);
    res |= assert_num_equals(0, motor_a.speed);
    res |= assert_num_equals(0, motor_b.speed);
    res |= assert_num_equals(1, motor_a.should_break);
    res |= assert_num_equals(1, motor_b.should_break);
    return res;
}