#include <stdio.h>

#include "nxt.h"
#include "display_manager.h"
#include "usb.h"
#include "movement.h"
#include "laser.h"

void display_string_at_xy(uint8_t x, uint8_t y, char *str) {
    display_goto_xy(x, y);
    display_string(str);
}


void display_int_at_xy(uint8_t x, uint8_t y, int32_t number, int32_t spaces) {
    display_goto_xy(x, y);
    display_int(number, spaces);
}

void display_hex_at_xy(uint8_t x, uint8_t y, int32_t number, int32_t spaces) {
    display_goto_xy(x, y);
    display_hex(number, spaces);
}

void display_calibration_status(char* direction, T_REVOLUTION position, int power) {
    display_clear(0);
    display_string_at_xy(0, 0, "Calibrating...");
    display_string_at_xy(0, 2, "dir");
    display_string_at_xy(4, 2, direction);
    display_string_at_xy(0, 3, "Pos:");
    display_string_at_xy(0, 4, "X:");
    display_string_at_xy(0, 5, "Y:");
    display_int_at_xy(4, 4, position.x, 3);
    display_int_at_xy(4, 5, position.y, 3);
    display_string_at_xy(0, 6, "pow");
    display_int_at_xy(4, 6, power, 4);
    display_update();
}

void display_hex_value(uint32_t value) {
    static int line_num = 0;
    if (line_num == 0) {
        display_clear(0);
    }
    display_hex_at_xy(0, line_num++, value, 8);
    display_update();
    line_num = line_num % 7;
}

void display_calibration_transfer_status(int i, T_POWER_TUPLE tuple) {
    display_clear(0);
    display_string_at_xy(0, 0, "Sending cali-data");
    display_int_at_xy(1, 1, i, 3);
    display_string_at_xy(0, 3, "Positive =");
    display_int_at_xy(3, 4, tuple.positive, 3);
    display_string_at_xy(0, 5, "Negative =");
    display_int_at_xy(3, 6, tuple.negative, 3);
    display_update();
}

void display_target_information(STATUS_CODE status_code, T_VECTOR target_last_location) {
    display_clear(0);

    display_string_at_xy(0, 1, "Target");
    if (status_code == NO_TARGET_FOUND) {
        display_string_at_xy(9, 1, "gone");
    } else if (status_code == READY_FOR_CALIBRATION) {
        display_string_at_xy(9, 1, "sending calibration");
    } else if (status_code == TARGET_FOUND) {
        display_string_at_xy(9, 1, "found");
    } else {
        display_hex_at_xy(9, 1, status_code, 4);
    }

    /* Position */
    display_string_at_xy(0, 2, "Position");
    T_REVOLUTION position = get_current_revolution();
    display_string_at_xy(0, 3, "X:");
    display_int_at_xy(3, 3, position.x, 4);
    display_string_at_xy(9, 3, "Y:");
    display_int_at_xy(12, 3, position.y, 4);

    /* Power */
    display_string_at_xy(0, 4, "Power:");
    display_string_at_xy(0, 5, "X:");
    display_int_at_xy(3, 5, x_motor_speed, 4);
    display_string_at_xy(9, 5, "Y:");
    display_int_at_xy(12, 5, y_motor_speed, 4);

    /* Modifier */
    display_string_at_xy(0, 6, "Distance:");
    display_string_at_xy(0, 7, "X:");
    display_int_at_xy(3, 7, target_last_location.x, 4);

    display_string_at_xy(9, 7, "Y:");
    display_int_at_xy(12, 7, target_last_location.y, 4);

    display_update();
}

void show_init_screen() {
    display_clear(0);
    display_string_at_xy(0, 0, "F.L.A.T");
    display_string_at_xy(0, 1, "Awaiting USB Host.");
    display_string_at_xy(0, 3, "Compilation time:");
    display_string_at_xy(0, 4, __TIME__);
    display_update();
}
