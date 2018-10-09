#include <string.h>

#include "logic_stubs.h"
#include "logic_test.h"
#include "logic.h"

T_TC_RESULT test_main_loop() {
    main_loop();
    char *expected_str = "OSEK HelloWorld!";
    assert_equals(expected_str, stub_ecrobot_status, strlen(expected_str));
    int expected_value = 500;
    assert_equals(&expected_value, &stub_last_delay, sizeof(expected_value));
}