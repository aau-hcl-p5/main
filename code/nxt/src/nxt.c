#include <stdlib.h>

#include "nxt.h"
#include "vector.h"
#include "movement.h"
#include "calibration.h"
#include "usb.h"
#include "display_manager.h"
#include "laser.h"

/* OSEK declarations */
DeclareTask(background_task);
DeclareTask(keep_USB_alive);
DeclareTask(update_display);
DeclareTask(handle_laser);
DeclareTask(receive_data);
DeclareTask(move_motors);
DeclareCounter(SysTimerCnt);
DeclareResource(USB_Rx);

/* Global variables */
T_VECTOR last_target_location = {0, 0};
STATUS_CODE current_status = DISCONNECTED_REQ;
bool calibrated = false;

/*
 * Function: ecrobot_device_initialize
 * ----------------------------
 *   Initializes motors with their direction
 */
void ecrobot_device_initialize(void) {
    init_motor(NXT_PORT_A, AXIS_Y, 20);
    init_motor(NXT_PORT_B, AXIS_X, 20);
    init_laser(NXT_PORT_C, NXT_PORT_C);
    ecrobot_init_usb(); /* init USB */
}

/*
 * Function: ecrobot_device_terminate
 * ----------------------------
 *   Kills motors, and unsets their ID's
 */
void ecrobot_device_terminate(void) {
    release_motor(NXT_PORT_A);
    release_motor(NXT_PORT_B);
    release_laser(NXT_PORT_C);
    ecrobot_term_usb(); /* terminate USB */
}

/*
 * Function: user_1ms_isr_type2
 * ----------------------------
 *   nxtOSEK hook to be invoked from an ISR in category 2.
 */
void user_1ms_isr_type2(void) {
    /* Increment System Timer Count to activate periodical Tasks */
    (void)SignalCounter(SysTimerCnt);
}

void stop() {
    stop_motors();
    disable_laser();
    ecrobot_disconnect_usb();
}

/*
 * Task: background_task
 * ----------------------------
 * The background task handles invoking the calibration and the disconnect status.
 *
 * PRIORITY: 5
 * PREEMPTIVE: YES
 * RESOURCE: USB_Rx
*/
TASK(background_task) {
    if (!calibrated && current_status == READY_FOR_CALIBRATION) {
        calibrate(false);
        calibrated = true;
    }
    TerminateTask();
}

/*
 * Task: keep_USB_alive
 * ----------------------------
 *   Keep USB Alive is invoked every 1 millisecond and
 *   handles pinging the USB connection to keep it alive.
 *
 *   PRIORITY: 6
 *   PREEMPTIVE: NO
 *   RESOURCE: USB_Rx
*/
TASK(keep_USB_alive) {

    GetResource(USB_Rx);
    ecrobot_process1ms_usb();
    ReleaseResource(USB_Rx);
    TerminateTask();
}

/*
 * Task: update_display
 * ----------------------------
 *   Update Display updates the display to show current target information.
 *
 *   PRIORITY: 6
 *   PREEMPTIVE: YES
 */
TASK(update_display) {
    if (current_status == DISCONNECTED_REQ) {
        show_init_screen();
    } else {
        display_target_information(current_status, last_target_location);
    }
    TerminateTask();
}

/*
 * Task: handle_laser
 * ----------------------------
 *   Handle Laser checks if the target is found and is within an
 *   allowed distance of center.
 *   In this case it enables the laser.
 *
 *   PRIORITY: 3
 *   PREEMPTIVE: NO
 */
TASK(handle_laser) {
    if (current_status == ON_TARGET) {
        enable_laser();
    } else {
        disable_laser();
    }
    TerminateTask();
}

/*
 * Task: receive_data
 * ----------------------------
 *   Receive data is responsible for receiving data from the USB
 *     and sets the status code of the system according to the
 *     data that was received.
 *
 *   PRIORITY: 4
 *   PREEMPTIVE: NO
 *   RESOURCE: USB_Rx
 */
TASK(receive_data) {
    int updated = get_status_code(&current_status, &last_target_location);

    if (updated && current_status == DISCONNECTED_REQ) {
        stop();
    }
    TerminateTask();
}

/*
 * Task: move_motors
 * ----------------------------
 *   Move motors is responsible for sending a signal to the co-processor
 *     that handles movement of motors.
 *
 *   PRIORITY: 2
 *   PREEMPTIVE: YES
 */
TASK(move_motors) {
    if (current_status == TARGET_FOUND || current_status == ON_TARGET) {
        move(last_target_location);
    } else {
        stop_motors();
    }
    TerminateTask();
}
