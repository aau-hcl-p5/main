#include "logic.h"
#include "nxt.h"

/* OSEK declarations */
DeclareTask(Task_background);
DeclareCounter(SysTimerCnt);

/* nxtOSEK hook to be invoked from an ISR in category 2 */
void user_1ms_isr_type2(void)
{
	/* Increment System Timer Count to activate periodical Tasks */
	(void)SignalCounter(SysTimerCnt);
}

TASK(Task_background)
{
    for(;;)
    {
        main_loop();
    }
}
