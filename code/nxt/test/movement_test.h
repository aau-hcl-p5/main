#ifndef MOVEMENT_TEST_H
#define MOVEMENT_TEST_H

#include "test_framework.h"

extern T_TC_RESULT test_motor_init();
extern T_TC_RESULT test_motor_init_illegal_axis();
extern T_TC_RESULT test_stop_motors();
extern T_TC_RESULT test_motor_release();

#endif