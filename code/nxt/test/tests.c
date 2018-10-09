#include <stdio.h>

#include "test_framework.h"
#include "logic_test.h"

int main() {
    T_TEST testcases[] = {
        {"Test main loop 1", test_main_loop},
        {"Test main loop 2", test_main_loop}
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