#include "nxt.h"
#include "target_information.h"
#include "movement.h"
#include "data_receive.h"
#include "display.h"
#include "movement.h"


/* OSEK declarations */
DeclareTask(ReceiveData);
DeclareTask(UpdateDisplay);
DeclareTask(ToggleLaser);
DeclareTask(MoveMotors);

DeclareCounter(SysTimerCnt);

DeclareEvent(MoveMotorsOnEvent);
DeclareEvent(MoveMotorsOffEvent);
DeclareEvent(LaserOnEvent);
DeclareEvent(LaserOffEvent);

DeclareResource(USB_Rx);

/* Global variables */
T_TARGET_INFORMATION target_information = { 0, 0, DISCONNECT_REQ };


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
}

TASK(UpdateDisplay)
{
  if(target_information.status == DISCONNECT_REQ)
    {
      show_init_screen();
    }
    else
    {
      display_target_information(target_information);
    }
  TerminateTask();
}

TASK(ToggleLaser)
{
  while(1){
    WaitEvent(LaserOnEvent);
    ClearEvent(LaserOnEvent);

    WaitEvent(LaserOffEvent);
    ClearEvent(LaserOffEvent);
  }
  TerminateTask();
}

TASK(ReceiveData)
{
	GetResource(USB_Rx);
  ecrobot_process1ms_usb();
  ReleaseResource(USB_Rx);
  if (get_target_information(&target_information)) {
    if(target_information.status == TARGET_FOUND)
    {
      SetEvent(MoveMotors, MoveMotorsOnEvent);
    }
    else if(target_information.status == NO_TARGET_FOUND) {
      SetEvent(MoveMotors, MoveMotorsOffEvent);
    }
  }
  TerminateTask();
}

TASK(MoveMotors)
{
  while(1){
    WaitEvent(MoveMotorsOnEvent);
    ClearEvent(MoveMotorsOnEvent);
    move(target_information.location);
    readjust_lower_bound(target_information.location);

    WaitEvent(MoveMotorsOffEvent);
    ClearEvent(MoveMotorsOffEvent);
    stop_motors();
  }
  TerminateTask();
}