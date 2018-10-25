#include <stdbool.h>

#include "test_framework.h"
#include "data_receive.h"
#include "data_receive_test.h"
#include "target_location.h"
#include "stubs.h"

T_TC_RESULT test_usb_read() {
    T_TC_RESULT result = TC_SUCCESS;
    T_TARGET_LOCATION expected_location = {7, 12, 15};
    T_TARGET_LOCATION out_location;
    set_usb_input_to_target(expected_location);
    result |= assert_bool_equals(true, get_target_location(&out_location));
    result |= assert_equals(&expected_location, &out_location, sizeof(T_TARGET_LOCATION));
    return result;
}

T_TC_RESULT test_usb_disconnect() {
    T_TC_RESULT result = TC_SUCCESS;
    T_TARGET_LOCATION expected_location = {0xFF, 0xFF, 0xFFFF};
    T_TARGET_LOCATION out_location;
    set_usb_input_to_target(expected_location);
    result |= assert_bool_equals(false, get_target_location(&out_location));
    result |= assert_bool_equals(false, usb_connected);
    return result;
}

extern void Task_ts1();

T_TC_RESULT test_task_ts1() {
    T_TC_RESULT result = TC_SUCCESS;
    uint32_t old_usb_processes = usb_processes;
    Task_ts1();
    assert_num_equals(old_usb_processes + 1, usb_processes);
    return result;
}
