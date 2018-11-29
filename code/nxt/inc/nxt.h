#ifndef NXT_H
#define NXT_H
#include <stdbool.h>

extern void KeepUSBAlive();
extern void RunCalibration();
extern void UpdateDisplay();
extern void ToggleLaser();
extern void ReceiveData();
extern void MoveMotors();


#ifndef TEST
#include "kernel.h"
#include "kernel_id.h"
#include "ecrobot_interface.h"
#else
#include "stubs.h"
#endif

#endif
