#include <stdio.h>

#include "nxt.h"
#include "display_data.h"

void display_target_location(T_TARGET_LOCATION loc)
{
    display_goto_xy(0, 0);
    display_string("x: ");
    display_goto_xy(4, 0);
    display_int(loc.x, 7);
    display_goto_xy(0, 1);
    display_string("y: ");
    display_goto_xy(4, 1);
    display_int(loc.y, 7);
    display_update();
}