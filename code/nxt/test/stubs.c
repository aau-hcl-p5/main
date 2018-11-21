#include "stubs.h"

char *stub_ecrobot_status;
int stub_last_delay;
bool usb_initialized = false;

void ecrobot_init_usb() {
    usb_initialized = true;
}
void ecrobot_term_usb() {
    usb_initialized = false;
}

void ecrobot_status_monitor(char *status) {
    stub_ecrobot_status = status;
}
void systick_wait_ms(int delay) {
    stub_last_delay = delay;
}