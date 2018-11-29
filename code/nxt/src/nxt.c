#include "nxt.h"
#include "vector.h"
#include "movement.h"
#include "calibration.h"
#include "usb.h"
#include "display_manager.h"

/* OSEK declarations */
DeclareTask(MainTask);
DeclareCounter(SysTimerCnt);
DeclareResource(USB_Rx);

/* Global variables */
T_VECTOR last_target_location = {0, 0};
STATUS_CODE current_status = DISCONNECTED_REQ;
bool newMajorCycle = true;
bool calibrating = false;

/* Initializes motors with their direction */
void ecrobot_device_initialize(void)
{
    init_motor(NXT_PORT_A, 'y', 20);
    init_motor(NXT_PORT_B, 'x', 20);
    ecrobot_init_usb(); /* init USB */
}

void ecrobot_device_terminate(void)
{
    release_motor(NXT_PORT_A);
    release_motor(NXT_PORT_B);
    ecrobot_term_usb(); /* terminate USB */
}

/* nxtOSEK hook to be invoked from an ISR in category 2 */
void user_1ms_isr_type2(void)
{
    /* Increment System Timer Count to activate periodical Tasks */
    (void)SignalCounter(SysTimerCnt);
    newMajorCycle = true;

    if(calibrating)
        keep_USB_alive();
}

TASK(MainTask)
{
    while(!get_status_code(&current_status));

    if (current_status == READY_FOR_CALIBRATION)
    {
        calibrating = true;
        calibrate(false);
        calibrating = false;
    }

    for(;;)
    {
        // Check if 1 ms has passed and a new cycle should begin
        if (newMajorCycle)
        {
            keep_USB_alive();
            receive_data();
            move_motors();
            toggle_laser();
            update_display();
            newMajorCycle = false;
        }
    }
    TerminateTask();
}

void keep_USB_alive()
{
    GetResource(USB_Rx);
    ecrobot_process1ms_usb();
    ReleaseResource(USB_Rx);
}

void update_display()
{
    if (current_status == DISCONNECTED_REQ)
    {
        show_init_screen();
    }
    else
    {
        display_target_information(current_status, last_target_location);
    }
}

void toggle_laser()
{
    /* Toggle laser */
}

void receive_data()
{
    if (get_status_code(&current_status))
    {
        if (current_status == TARGET_FOUND)
        {
            /* Wait for a target location */
            /* TODO: This should not be blocking */
            while (!get_target_location(&last_target_location)){}
        }
    }
}

void move_motors()
{
    if (current_status == TARGET_FOUND)
    {
        stop_motors();
    }

    else if (current_status == NO_TARGET_FOUND)
    {
        move(last_target_location);
    }
}