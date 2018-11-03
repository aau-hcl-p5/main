#include "nxt.h"
#include "init_screen.h"
#include "display_data.h"

void show_init_screen(void)
{
	display_clear(0);
	display_string_at_xy(0, 0, "F.L.A.T");
	display_string_at_xy(0, 1, "Awaiting USB Host.");
	display_string_at_xy(0, 3, "Compilation time:");
	display_string_at_xy(0, 4, __TIME__);
	display_update();	
}