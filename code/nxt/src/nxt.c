#include "logic.h"
#include "nxt.h"
#include "init_screen.h"
#include "movement.h"
#include "calibration.h"

/* OSEK declarations */
DeclareTask(Task_background);
DeclareCounter(SysTimerCnt);

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
void user_1ms_isr_type2(void)
{
  /* Increment System Timer Count to activate periodical Tasks */
  (void)SignalCounter(SysTimerCnt);
}

TASK(Task_background)
{
  show_init_screen();{
  calibrate(false);
  while(1)
  {
    main_loop();
  }
  TerminateTask();
}
