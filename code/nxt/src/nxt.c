#include "nxt.h"
#include "vector.h"
#include "movement.h"
#include "calibration.h"
#include "usb.h"
#include "display_manager.h"


/* OSEK declarations */
DeclareTask(RunCalibration);
DeclareTask(ReceiveData);
DeclareTask(UpdateDisplay);
DeclareTask(ToggleLaser);
DeclareTask(MoveMotors);
DeclareTask(KeepUSBAlive);

DeclareCounter(SysTimerCnt);

DeclareEvent(MoveMotorsOnEvent);
DeclareEvent(MoveMotorsOffEvent);
DeclareEvent(LaserOnEvent);
DeclareEvent(LaserOffEvent);

DeclareResource(USB_Rx);

/* Global variables */
T_VECTOR last_target_location = { 0, 0 };
STATUS_CODE current_status = DISCONNECTED_REQ;


/* Initializes motors with their direction */
void ecrobot_device_initialize(void) {
    init_motor(NXT_PORT_A, 'y', 20);
    init_motor(NXT_PORT_B, 'x', 20);
    ecrobot_init_usb(); /* init USB */
}

void ecrobot_device_terminate(void) {
    release_motor(NXT_PORT_A);
    release_motor(NXT_PORT_B);
    ecrobot_term_usb(); /* terminate USB */
}

/* nxtOSEK hook to be invoked from an ISR in category 2 */
void user_1ms_isr_type2(void) {
    /* Increment System Timer Count to activate periodical Tasks */
    (void)SignalCounter(SysTimerCnt);
}

TASK(RunCalibration) {
    if(!calibrated) {
        show_init_screen();
        while (!get_status_code(&current_status));
        if (current_status == READY_FOR_CALIBRATION) {
            calibrate(false);
        }
    }
    TerminateTask();
}

TASK(UpdateDisplay) {
    if(current_status == DISCONNECTED_REQ)
    {
        show_init_screen();
    }
    else
    {
        display_target_information(current_status, last_target_location);
    }
    TerminateTask();
}

TASK(ToggleLaser) {
    while(1) {
        WaitEvent(LaserOnEvent);
        ClearEvent(LaserOnEvent);

        WaitEvent(LaserOffEvent);
        ClearEvent(LaserOffEvent);
    }
    TerminateTask();
}

TASK(KeepUSBAlive) {
    GetResource(USB_Rx);
    ecrobot_process1ms_usb();
    ReleaseResource(USB_Rx);
    TerminateTask();
}

TASK(ReceiveData) {
    if (get_status_code(&current_status)) {
        if(current_status == TARGET_FOUND)
        {
            /* Wait for a target location */
            while(!get_target_location(&last_target_location));
            SetEvent(MoveMotors, MoveMotorsOnEvent);
        }
        else if(current_status == NO_TARGET_FOUND) {
            SetEvent(MoveMotors, MoveMotorsOffEvent);
        }
    }
    TerminateTask();
}

TASK(MoveMotors) {
    // This task is going to be preempted so this is not an issue
    while(1) {

        // we wait for the motor event, from ReceiveData, to be sent.
        WaitEvent(MoveMotorsOnEvent);
        ClearEvent(MoveMotorsOnEvent);
        move(last_target_location);

        WaitEvent(MoveMotorsOffEvent);
        ClearEvent(MoveMotorsOffEvent);
        stop_motors();
    }
    TerminateTask();
}