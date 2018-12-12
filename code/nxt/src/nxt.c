#include <stdlib.h>

#include "nxt.h"
#include "vector.h"
#include "movement.h"
#include "calibration.h"
#include "usb.h"
#include "display_manager.h"
#include "laser.h"

/* OSEK declarations */
DeclareTask(MainTask);
DeclareCounter(SysTimerCnt);
DeclareResource(USB_Rx);
DeclareEvent(newMajorCycleEvent);

/* Global variables */
T_VECTOR last_target_location = {0, 0};
STATUS_CODE current_status = DISCONNECTED_REQ;
bool calibrating = false;

/* Initializes motors with their direction */
void ecrobot_device_initialize(void) {
    init_motor(NXT_PORT_A, 'y', 20);
    init_motor(NXT_PORT_B, 'x', 20);
    init_laser(NXT_PORT_C, NXT_PORT_C);
    ecrobot_init_usb(); /* init USB */
}

void ecrobot_device_terminate(void) {
    release_motor(NXT_PORT_A);
    release_motor(NXT_PORT_B);
    release_laser(NXT_PORT_C);
    ecrobot_term_usb(); /* terminate USB */
}

/* nxtOSEK hook to be invoked from an ISR in category 2 */
void user_1ms_isr_type2(void) {
    /* Increment System Timer Count to activate periodical Tasks */
    (void)SignalCounter(SysTimerCnt);
    SetEvent(MainTask, newMajorCycleEvent);
    if(calibrating)
        keep_USB_alive();
}

void stop() {
    stop_motors();
    ecrobot_disconnect_usb();
}

TASK(MainTask) {
    for (;;) {
        calibrating = true;
        show_init_screen();
        while(!get_status_code(&current_status, 0));

        if (current_status == READY_FOR_CALIBRATION) {
            calibrate(false);
        }
        calibrating = false;
        for(;;) {
            WaitEvent(newMajorCycleEvent); /* Wait for the event signalling that a new major cycle is starting */
            keep_USB_alive();
            receive_data();
            if (current_status == DISCONNECTED_REQ) {
                stop();
                break;
            }
            keep_USB_alive();
            move_motors();
            handle_laser();
            update_display();
            ClearEvent(newMajorCycleEvent); /* Clear the event, signalling that the cycle is over */
        }
    }

    TerminateTask();
}

void keep_USB_alive() {
    GetResource(USB_Rx);
    ecrobot_process1ms_usb();
    ReleaseResource(USB_Rx);
}

void update_display() {
    if (current_status == DISCONNECTED_REQ) {
        show_init_screen();
    } else {
        display_target_information(current_status, last_target_location);
    }
}

void handle_laser() {
    if (current_status == TARGET_FOUND && abs(last_target_location.x) < 5 && abs(last_target_location.y) < 5) {
        enable_laser();
    } else {
        disable_laser();
    }
}

void receive_data() {
    get_status_code(&current_status, &last_target_location);
}

void move_motors() {
    if (current_status == TARGET_FOUND) {
        move(last_target_location);
    } else {
        stop_motors();
    }
}
