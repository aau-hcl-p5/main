#include <stdio.h>

#include "nxt.h"
#include "display_data.h"
#include "data_receive.h"
#include "movement.h"

void display_target_location(T_TARGET_LOCATION loc)
{
    display_clear(0);
    display_update();

    /* Is target found? */
    T_TARGET_LOCATION target_location;
    get_target_location(&target_location);     
    display_goto_xy(0, 1);
    display_string("TARGET");
    display_goto_xy(9, 1);
    if(target_location.timestamp == 0x00FF) {
        display_string("GONE");
    } else {
        display_string("FOUND");
    }


    /* Position */
    T_TARGET_LOCATION current_location = get_current_location();
    display_goto_xy(0, 2);
    display_string("POSITION:");

    display_goto_xy(0, 3);
    display_string("X:");
    display_goto_xy(3, 3);
    display_int(current_location.x, 4);

    display_goto_xy(9, 3);
    display_string("Y:");
    display_goto_xy(12, 3);
    display_int(current_location.y, 4);

    /* Power */
    display_goto_xy(0, 4);
    display_string("POWER:");

    display_goto_xy(0, 5);
    display_string("X:");
    display_goto_xy(3, 5);
    display_int(get_speed_by_distance(loc.x,'x'), 4);

    display_goto_xy(9, 5);
    display_string("Y:");
    display_goto_xy(12, 5);
    display_int(get_speed_by_distance(loc.y,'y'), 4);

    /* Modifier */
    display_goto_xy(0, 6);
    display_string("MODIFIER:");

    display_goto_xy(0, 7);
    display_string("X:");
    display_goto_xy(3, 7);
    display_int(x_lower_bound_modifier, 4);

    display_goto_xy(9, 7);
    display_string("Y:");
    display_goto_xy(12, 7);
    display_int(y_lower_bound_modifier, 4);

    display_update();
}