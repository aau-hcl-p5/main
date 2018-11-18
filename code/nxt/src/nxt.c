#include "nxt.h"
#include "init_screen.h"
#include "target_information.h"
#include "movement.h"
#include "data_receive.h"
#include "display_data.h"
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

int UpdateDisplayStart = 0, UpdateDisplayEnd = 0, 
    ToggleLaserStart = 0,   ToggleLaserEnd = 0,
    ReceiveDataStart = 0,   ReceiveDataEnd = 0, 
    MoveMotorsStart = 0,    MoveMotorsEnd = 0;

int UpdateDisplayWCET = 0,  UpdateDisplayBCET = 0,
    ToggleLaserWCET = 0,    ToggleLaserBCET = 0,
    ReceiveDataWCET = 0,    ReceiveDataBCET = 0,
    MoveMotorsWCET = 0,     MoveMotorsBCET = 0;


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
int count = 0;
/* nxtOSEK hook to be invoked from an ISR in category 2 */
void user_1ms_isr_type2(void)
{
  /* Increment System Timer Count to activate periodical Tasks */
  (void)SignalCounter(SysTimerCnt);
  count++;
}

TASK(UpdateDisplay)
{
  UpdateDisplayStart = count;

  if(target_information.status == DISCONNECT_REQ)
    {
      show_init_screen();
    }
    else
    {
      /* Timing methods */
      display_clear(0);
      display_int_at_xy(0, 0, UpdateDisplayWCET, 6);
      display_int_at_xy(0, 1, ToggleLaserWCET, 6);
      display_int_at_xy(0, 2, ReceiveDataWCET, 6);
      display_int_at_xy(0, 3, MoveMotorsWCET, 6);
      display_int_at_xy(0, 3, count, 6);

      display_update();
      
      // display_target_information(target_information);
    }
 
  UpdateDisplayEnd = count;

  if(UpdateDisplayWCET < (UpdateDisplayEnd-UpdateDisplayStart))
    UpdateDisplayWCET = (UpdateDisplayEnd-UpdateDisplayStart);
  if(UpdateDisplayBCET > (UpdateDisplayEnd-UpdateDisplayStart))
    UpdateDisplayBCET = (UpdateDisplayEnd-UpdateDisplayStart);

  TerminateTask();
}

TASK(ToggleLaser)
{
  ToggleLaserStart = count;
  while(1){
    WaitEvent(LaserOnEvent);
    ClearEvent(LaserOnEvent);

    WaitEvent(LaserOffEvent);
    ClearEvent(LaserOffEvent);
  }
  ToggleLaserEnd = count;

  if(ToggleLaserWCET < (ToggleLaserEnd-ToggleLaserStart))
    ToggleLaserWCET = (ToggleLaserEnd-ToggleLaserStart);
  if(ToggleLaserBCET > (ToggleLaserEnd-ToggleLaserStart))
    ToggleLaserBCET = (ToggleLaserEnd-ToggleLaserStart);

  TerminateTask();
}

TASK(ReceiveData)
{
  ReceiveDataStart = count;
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
  ReceiveDataEnd = count;

  if(ReceiveDataWCET < (ReceiveDataEnd-ReceiveDataStart))
    ReceiveDataWCET = (ReceiveDataEnd-ReceiveDataStart);
  if(ReceiveDataBCET > (ReceiveDataEnd-ReceiveDataStart))
    ReceiveDataBCET = (ReceiveDataEnd-ReceiveDataStart);
  
  TerminateTask();
}

TASK(MoveMotors)
{
  MoveMotorsStart = count;
  while(1){
    WaitEvent(MoveMotorsOnEvent);
    ClearEvent(MoveMotorsOnEvent);
    move(target_information.location);
    readjust_lower_bound(target_information.location);

    WaitEvent(MoveMotorsOffEvent);
    ClearEvent(MoveMotorsOffEvent);
    stop_motors();
  }
  MoveMotorsEnd = count;

  if(MoveMotorsWCET < (MoveMotorsEnd-MoveMotorsStart))
    MoveMotorsWCET = (MoveMotorsEnd-MoveMotorsStart);
  if(MoveMotorsBCET > (MoveMotorsEnd-MoveMotorsStart))
    MoveMotorsBCET = (MoveMotorsEnd-MoveMotorsStart);

  TerminateTask();
}