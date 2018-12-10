#include <string.h>

#include "stubs.h"
#include "laser_test.h"
#include "laser.h"

T_TC_RESULT test_target_information_size() {
    return assert_num_equals(4, sizeof(T_TARGET_INFORMATION));
}

T_TC_RESULT test_t_vector_size() {
    return assert_num_equals(2, sizeof(T_VECTOR));
}

T_TC_RESULT test_toggle_laser() {
    laser_state = false;

    toggle_laser();

    return assert_bool_equals(laser_state, true);
}