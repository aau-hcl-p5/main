#include <stdint.h>

#include "stubs.h"

T_MOTOR motors[8];

T_MOTOR get_motor_attributes(uint32_t motor) {
    return motors[motor];
}

uint8_t ecrobot_get_motor_rev(uint32_t motor) {
    return motors[motor].rev;
}
void ecrobot_set_motor_speed(uint32_t motor, int speed) {
    nxt_motor_set_speed(motor, speed, true);
}
void nxt_motor_set_speed(uint32_t motor, int speed, int should_break) {
    motors[motor].speed = speed;
    motors[motor].should_break = should_break;
}
void nxt_motor_set_count(uint32_t motor, int count) {
    motors[motor].rev = count;
}
