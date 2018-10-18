#include "logic.h"
#include "nxt.h"
#include "movement.h"

DeclareCounter(SysTimerCnt);
DeclareTask(OSEK_Task_Background);
DeclareTask(SET_MOTOR);
DeclareResource(x_motor);
DeclareEvent(EVENT_COORDS);

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

TASK(SET_MOTOR){
    while(1){
        move('r', 95);
        move('l', 50);
    }
    TerminateTask();
}
