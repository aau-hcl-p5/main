#include "logic.h"
#include "nxt.h"
#include "movement.h"

DeclareCounter(SysTimerCnt);
DeclareTask(OSEK_Task_Background);
DeclareTask(SET_MOTOR);
DeclareEvent(WrongLocationEvent);
DeclareEvent(RightLocationEvent);

/* nxtOSEK hook to be invoked from an ISR in category 2 */
void user_1ms_isr_type2(void){ 
    StatusType ercd;
    ercd = SignalCounter(SysTimerCnt); // Increment alarm counter
    if(ercd != E_OK){
        ShutdownOS(ercd);
    }
}

/* Initializes motors with their direction */
void ecrobot_device_initialize(void){
    init_motor(NXT_PORT_A, 'x');
    init_motor(NXT_PORT_B, 'y');
}

void ecrobot_device_terminate(void){
    release_motor(NXT_PORT_A);
    release_motor(NXT_PORT_B);
}

TASK(OSEK_Task_Background)
{
    for(;;)
    {
        main_loop();
    }
    TerminateTask();
}

TASK(CHECK_LOCATION)
{
    //if(target_x != current_x){
     //   SetEvent(SET_MOTOR, WrongLocationEvent);
   // }
    //else if(current_x == target_x){
     //   SetEvent(SET_MOTOR, RightLocationEvent);
    //}

    TerminateTask();
}

TASK(SET_MOTOR)
{
    WaitEvent(WrongLocationEvent);
    ClearEvent(WrongLocationEvent);
    move('x', 50);

    WaitEvent(RightLocationEvent);
    ClearEvent(RightLocationEvent);
    nxt_motor_set_speed(NXT_PORT_A, 0, 1);
TerminateTask();
}
