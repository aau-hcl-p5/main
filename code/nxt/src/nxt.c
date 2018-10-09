#include "logic.h"
#include "nxt.h"

/* nxtOSEK hook to be invoked from an ISR in category 2 */
void user_1ms_isr_type2(void){ /* do nothing */ }

TASK(OSEK_Task_Background)
{
    for(;;)
    {
        main_loop();
    }
}
