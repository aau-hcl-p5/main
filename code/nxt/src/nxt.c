#include "logic.h"
#include "nxt.h"
#include "movement.h"

DeclareTask(OSEK_Task_Background);

/* nxtOSEK hook to be invoked from an ISR in category 2 */
void user_1ms_isr_type2(void){ }

/* Initializes motors with their direction */
void ecrobot_device_initialize(void){
    init_motor(NXT_PORT_A, 'x', 20);
    init_motor(NXT_PORT_B, 'y', 20);
}

void ecrobot_device_terminate(void){
    release_motor(NXT_PORT_A);
    release_motor(NXT_PORT_B);
}

TASK(OSEK_Task_Background)
{
	while(1)
	{
		main_loop();
		move_motors();
	}
	TerminateTask();
}