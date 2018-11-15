#include <stdbool.h>

#include "test_framework.h"
#include "data_receive.h"
#include "data_receive_test.h"
#include "target_information.h"
#include "stubs.h"

T_TC_RESULT test_usb_read() {
    T_TC_RESULT result = TC_SUCCESS;
    T_TARGET_INFORMATION expected_information = {7, 12, TARGET_FOUND};
    T_TARGET_INFORMATION out_information;
    set_usb_input_to_target_information(expected_information);
    result |= assert_bool_equals(true, get_target_information(&out_information));
    result |= assert_equals(&expected_information, &out_information, sizeof(T_TARGET_INFORMATION));
    return result;
}

T_TC_RESULT test_usb_disconnect() {
    T_TC_RESULT result = TC_SUCCESS;
    T_TARGET_INFORMATION expected_information = {0xAB, 0xCD, DISCONNECT_REQ};
    T_TARGET_INFORMATION out_information;
    set_usb_input_to_target_information(expected_information);
    result |= assert_bool_equals(false, get_target_information(&out_information));
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
