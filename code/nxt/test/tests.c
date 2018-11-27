#include <stdio.h>

#include "test_framework.h"
#include "logic_test.h"
#include "data_receive_test.h"
#include "movement_test.h"

int main() {
    T_TEST testcases[] = {
        {"Ensure sizeof target_information is 4 byte", test_target_information_size},
        {"Ensure sizeof target_location is 2 byte", test_target_location_size},
        {"Test read from usb", test_usb_read},
        {"Test usb disconnect", test_usb_disconnect},
        {"Test motor initialization", test_motor_init},
        {"Test motor init fails on illegal axis", test_motor_init_illegal_axis},
        {"Test stop motors", test_stop_motors},
        {"Test release motor", test_motor_release},
        {"Test toggle laser", test_toggle_laser},
        {"Test go to standby", test_standby},
        {"Test get distance to target", test_get_distance},
        {"Test predict trajectory", test_predict_trajectory},
    };
    int passes = 0;
    int fails = 0;
        printf("=================================================================\n\n"
               "                      Starting tests.\n\n"
               "=================================================================\n");
    for (int i = 0; i < sizeof(testcases) / sizeof(testcases[0]); i++) {
        printf("Executing TC: %s\n", testcases[i].name);
        T_TC_RESULT result = testcases[i].testcase();
        if (result == TC_ERROR) {
            fails++;
            printf(" - %sFAIL!%s\n", TERM_RED, TERM_RESET);
        } else {
            passes++;
            printf(" - %sPASS!%s\n", TERM_GREEN, TERM_RESET);
        }
    }
    printf("=================================================================\n"
            "                   All tests finished.\n\n"
            "  Result: %d/%d passed!\n\n", passes, passes + fails);
    return fails;
}
