#include <string.h>

#include "stubs.h"
#include "logic_test.h"
#include "logic.h"

T_TC_RESULT test_target_information_size() {
    return assert_num_equals(4, sizeof(T_TARGET_INFORMATION));
}

T_TC_RESULT test_target_location_size() {
    return assert_num_equals(2, sizeof(T_TARGET_LOCATION));
}

T_TC_RESULT test_toggle_laser() {
    return assert_bool_equals(toggle_laser(), !toggle_laser());
}

T_TC_RESULT test_standby() {
    return assert_bool_equals(true, standby());
}

T_TC_RESULT test_get_distance() {
    return assert_num_equals(0, get_distance(0));
}

T_TC_RESULT test_predict_trajectory() {
    T_TARGET_LOCATION loc;
    return assert_num_equals(0, predict_trajectory(loc));
}
