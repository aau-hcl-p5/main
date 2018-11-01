#include <stdio.h>

#include "nxt.h"
#include "display_data.h"
#include "movement.h"

void display_target_location(T_TARGET_LOCATION loc)
{
  display_goto_xy(0, 1);
  display_string("t: "); // timestamp
  display_goto_xy(4, 1);
  display_int(loc.timestamp, 7);

  display_goto_xy(0, 1);
  display_string("dir: ");
  display_goto_xy(4, 1);
  display_int(loc.x, 5);
  display_goto_xy(10, 1);
  display_int(loc.y, 5);


  display_goto_xy(0, 2);
  display_string("spd: "); // speed
  display_goto_xy(4, 2);
  display_int(get_speed_by_distance(loc.x,'x'), 5);
  display_goto_xy(10, 2);
  display_int(get_speed_by_distance(loc.y,'y'), 5);

  display_goto_xy(0, 3);
  display_string("loc: "); // location
  display_goto_xy(4, 3);
  display_int(nxt_motor_get_count(0), 5);
  display_goto_xy(10, 3);
  display_int(nxt_motor_get_count(1), 5);


  display_goto_xy(0, 4);
  display_string("mod: "); // modifiers
  display_goto_xy(4, 4);
  display_int(x_lower_bound_modifier, 5);
  display_goto_xy(10, 4);
  display_int(y_lower_bound_modifier, 5);



  display_update();
}