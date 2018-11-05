#include <stdio.h>

#include "nxt.h"
#include "display_data.h"
#include "data_receive.h"
#include "movement.h"

void display_string_at_xy(uint8_t x, uint8_t y, char *str){
    display_goto_xy(x, y);
    display_string(str);
}

void display_int_at_xy(uint8_t x, uint8_t y, int32_t number, int32_t spaces){
    display_goto_xy(x, y);
    display_int(number, spaces);
}

void display_target_location(T_TARGET_LOCATION loc)
{
    display_clear(0);
    display_update();

    /* Is target found? */
    T_TARGET_LOCATION target_location;
    get_target_location(&target_location);     
    display_string_at_xy(0, 1, "Target");
    if(target_location.timestamp == 0x00FF) {
        display_string_at_xy(9, 1, "gone");
    } else {
        display_string_at_xy(9, 1, "found");
    }


    /* Position */
    T_TARGET_LOCATION current_location = get_current_location();
    display_string_at_xy(0, 2, "Position");
    display_string_at_xy(0, 3, "X:");
    display_int_at_xy(3, 3, current_location.x, 4);
    display_string_at_xy(9, 3, "Y:");
    display_int_at_xy(12, 3, current_location.y, 4);

    /* Power */
    display_string_at_xy(0, 4, "Power:");
    display_string_at_xy(0, 5, "X:");
    display_int_at_xy(3, 5, get_speed_by_distance(loc.x, 'x'), 4);
    display_string_at_xy(9, 5, "Y:");
    display_int_at_xy(12, 5, get_speed_by_distance(loc.y, 'y'), 4);

    /* Modifier */
    display_string_at_xy(0, 6, "Modifier:");
    display_string_at_xy(0, 7, "X:");
    display_int_at_xy(3, 7, x_lower_bound_modifier, 4);

    display_string_at_xy(9, 7, "Y:");
    display_int_at_xy(12, 7, y_lower_bound_modifier, 4);

    display_update();
}