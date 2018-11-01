#include "nxt.h"
#include "init_screen.h"

void show_init_screen(void)
{
	display_clear(0);
	display_goto_xy(0, 0);
	display_string("F.L.A.T.");
	display_goto_xy(0, 1);
	display_string("Awaiting USB host.");
	display_update();	
}