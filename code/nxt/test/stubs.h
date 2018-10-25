#ifndef STUBS_H
#define STUBS_H

#include <stdint.h>
#include <stdbool.h>

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

// Display

extern void display_goto_xy(uint8_t x, uint8_t y);
extern void display_string(char *str);
extern void display_int(int num, int len);
extern void display_update();
extern void display_clear(uint32_t update_too);

// USB

extern uint32_t ecrobot_read_usb(uint8_t *buffer, uint32_t buffer_offset, uint32_t max_len);
extern void ecrobot_disconnect_usb();
extern void ecrobot_process1ms_usb();

// Movement

extern uint8_t ecrobot_get_motor_rev(uint32_t motor);
extern void ecrobot_set_motor_speed(uint32_t motor, int speed);
extern void nxt_motor_set_speed(uint32_t motor, int speed, int break_power);
extern void nxt_motor_set_count(uint32_t motor, int count);

#endif