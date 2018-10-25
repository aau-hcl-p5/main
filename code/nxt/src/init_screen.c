#include "nxt.h"
#include "init_screen.h"

void show_init_screen(void)
{
	display_clear(0);
	display_goto_xy(0, 0);
	display_string("USB TEST");
	display_goto_xy(0, 1);
	display_string("Run usbhost.exe");
	display_update();	
}