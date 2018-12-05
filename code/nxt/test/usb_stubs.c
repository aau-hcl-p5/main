#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#include "usb.h"

bool usb_connected = true;
bool usb_buffer[256];
uint32_t usb_len;

uint32_t usb_processes = 0; 
bool usb_initialized = false;

void ecrobot_init_usb() {
    usb_initialized = true;
}
void ecrobot_term_usb() {
    usb_initialized = false;
}

void set_usb_input(uint8_t *buffer, uint32_t len) {
    usb_connected = true;
    memcpy(usb_buffer, buffer, len);
    usb_len = len;
}

void set_usb_input_to_target_location(T_VECTOR target_location) {
    set_usb_input((uint8_t *)&target_location, sizeof(T_VECTOR));
}

uint32_t ecrobot_read_usb(uint8_t *buffer, uint32_t buffer_offset, uint32_t max_len) {
    uint32_t len = max_len < usb_len ? max_len : usb_len;
    memcpy(buffer, usb_buffer, len);
    usb_len = 0;
    return len;
}

uint32_t ecrobot_send_usb(uint8_t *buffer, uint32_t buffer_offset, uint32_t max_len) {
    uint32_t len = max_len < usb_len ? max_len : usb_len;
    return len;
}


void ecrobot_disconnect_usb() {
    usb_connected = false;
}

void ecrobot_process1ms_usb() {
    usb_processes++;
}
