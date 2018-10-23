#include "movement.h"

T_TARGET_LOCATION get_current_location() {
    T_TARGET_LOCATION loc = {0, 0, 0};
    return loc;
}

bool init_motor(uint8_t motor_id, char orientation, uint16_t speed) {
    return true;
}

bool release_motor(uint8_t motor_id) {
    return true;
}
bool move_to(T_TARGET_LOCATION target_location) {
    return true;
}

void move_motors() {}
void stop_motors() {}
void move_motor(uint8_t motor_id, int32_t speed) {}