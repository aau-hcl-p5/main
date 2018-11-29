#ifndef NXT_H
#define NXT_H
#include <stdbool.h>

void keepUSBAlive();
void runCalibration();
void updateDisplay();
void toggleLaser();
void receiveData();
void moveMotors();


#ifndef TEST
#include "kernel.h"
#include "kernel_id.h"
#include "ecrobot_interface.h"
#else
#include "stubs.h"
#endif

#endif
