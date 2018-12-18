#ifndef NXT_H
#define NXT_H
#include <stdbool.h>

#define INITIAL_SPEED 20

#ifndef TEST
#include "kernel.h"
#include "kernel_id.h"
#include "ecrobot_interface.h"
#else
#include "stubs.h"
#endif

#endif
