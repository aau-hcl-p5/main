#ifndef NXT_H
#define NXT_H
#include <stdbool.h>

void KeepUSBAlive();
void RunCalibration();
void UpdateDisplay();
void ToggleLaser();
void ReceiveData();
void MoveMotors();


#ifndef TEST
#include "kernel.h"
#include "kernel_id.h"
#include "ecrobot_interface.h"
#else
#include "stubs.h"
#endif

#endif
