#include "nxt.h"
#include "init_screen.h"

void show_init_screen(void)
{
	display_clear(0);
	display_goto_xy(0, 0);
	display_string("F.L.A.T.");
	display_goto_xy(0, 1);
	display_string("Awaiting USB host.");
	display_goto_xy(0, 3);
    display_string("Compilation time:");
    display_goto_xy(0, 4);
    display_string(__TIME__);
	display_update();	
}