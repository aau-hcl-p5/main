#include <stdio.h>
#include <string.h>

#include "test_framework.h"

T_TC_RESULT assert_equals(void *expected, void *actual, int length) {
    if (memcmp(expected, actual, length) == 0) {
        return TC_SUCCESS;
    }
    printf("%sAssert equals failed!%s\n", TERM_RED, TERM_RESET);
    for (int i = 0; i < length; i++) {
        printf("  Byte %2d - Expected: %02hhx ", i + 1, ((char *)expected)[i]);
        if (((char *)expected)[i] >= ' ') {
            printf("(%c) ", ((char *)expected)[i]);
        }
        printf("\tbut got: %02hhx ", ((char *)actual)[i]);
        if (((char *)actual)[i] >= ' ') {
            printf("(%c) ", ((char *)actual)[i]);
        }
        printf("\n");
    }
    if (length == 4) {
        printf("  Int representation (%d) -- (%d)\n", *((int*)expected), *((int*)actual));
    }
    return TC_ERROR;
}