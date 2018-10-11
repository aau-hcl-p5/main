/*
 * This files is mostly created in order to have a starting point for additional files besides nxt.c
 * Feel free to remove it.
 */
 #include "nxt.h"

 void main_loop() {
    ecrobot_status_monitor("OSEK HelloWorld!");
    systick_wait_ms(500); /* 500msec wait */
 }