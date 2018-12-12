#ifndef TEST_FRAMEWORK_H
#define TEST_FRAMEWORK_H

#include <stdint.h>
#include <stdbool.h>

#define TERM_GREEN "\033[0;32m"
#define TERM_RED "\033[0;31m"
#define TERM_RESET "\033[0;0m"

typedef enum {
    TC_SUCCESS = 0,
    TC_ERROR
} T_TC_RESULT;

typedef struct {
    const char *name;
    T_TC_RESULT (*testcase)(void);
} T_TEST;

extern T_TC_RESULT assert_equals(void *ptr1, void *ptr2, int length);
extern T_TC_RESULT assert_num_equals(uint32_t expected, uint32_t actual);
extern T_TC_RESULT assert_bool_equals(bool expected, bool actual);

#endif
