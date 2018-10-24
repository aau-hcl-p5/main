#include "data_receive.h"
#include "stdbool.h"

bool get_target_location(T_TARGET_LOCATION *loc) {
    T_TARGET_LOCATION new_loc = {0, 0, 0};
    *loc = new_loc;
    return true;
}