#ifndef STUBS_H
#define STUBS_H

#include <stdint.h>
#include <stdbool.h>
#include "target_location.h"

#define DeclareTask(x) 
#define DeclareResource(x) 
#define GetResource(x) 
#define ReleaseResource(x) 
#define TASK(x) void x ()
#define TerminateTask() return

// General

extern void ecrobot_status_monitor(char *status);
extern void systick_wait_ms(int delay);
extern char *stub_ecrobot_status;
extern int stub_last_delay;

// Ports

#define NXT_PORT_A 0
#define NXT_PORT_B 1

// Display

extern void display_goto_xy(uint8_t x, uint8_t y);
extern void display_string(char *str);
extern void display_int(int num, int len);
extern void display_update();
extern void display_clear(uint32_t update_too);

// USB

extern void set_usb_input(uint8_t *buffer);
extern void set_usb_input_to_target(T_TARGET_LOCATION target_location);
extern bool usb_connected;
extern uint32_t usb_processes;

extern uint32_t ecrobot_read_usb(uint8_t *buffer, uint32_t buffer_offset, uint32_t max_len);
extern uint32_t ecrobot_send_usb(uint8_t *buffer, uint32_t buffer_offset, uint32_t max_len);
extern void ecrobot_disconnect_usb();
extern void ecrobot_process1ms_usb();

// Movement

typedef struct {
    int speed;
    int rev;
    int should_break;
} T_MOTOR;

extern T_MOTOR get_motor_attributes(uint32_t motor);

extern uint8_t ecrobot_get_motor_rev(uint32_t motor);
extern void ecrobot_set_motor_speed(uint32_t motor, int speed);
extern void nxt_motor_set_speed(uint32_t motor, int speed, int should_break);
extern void nxt_motor_set_count(uint32_t motor, int count);

#endif