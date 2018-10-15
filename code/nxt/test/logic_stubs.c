#include "logic_stubs.h"

char *stub_ecrobot_status;
int stub_last_delay;

void ecrobot_status_monitor(char *status) {
    stub_ecrobot_status = status;
}
void systick_wait_ms(int delay) {
    stub_last_delay = delay;
}