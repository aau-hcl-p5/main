#ifndef NXT_H
#define NXT_H
#include <stdbool.h>

void keep_USB_alive();
void run_calibration();
void update_display();
void toggle_laser();
void receive_data();
void move_motors();


#ifndef TEST
#include "kernel.h"
#include "kernel_id.h"
#include "ecrobot_interface.h"
#else
#include "stubs.h"
#endif

#endif
