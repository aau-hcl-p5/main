/* usbtest.c */
#include <string.h>
#include <stdio.h>
#include <stdint.h>

#include "nxt.h"
#include "target_location.h"
#include "usb.h"
#include "init_screen.h"
#include "display_data.h"

/* OSEK declarations */
DeclareTask(Task_ts1);
DeclareResource(USB_Rx);

#define SIZEOF_USB_DATA sizeof(T_TARGET_LOCATION)

bool get_target_location(T_TARGET_LOCATION *out_location) {
	int32_t len;
	uint8_t data[SIZEOF_USB_DATA];

    memset(data, 0, SIZEOF_USB_DATA); /* flush buffer */
	/* critical section */
	GetResource(USB_Rx);
	len = ecrobot_read_usb(data, 0, SIZEOF_USB_DATA); /* read USB data */
	ReleaseResource(USB_Rx);

	if (len > 0)
	{
		if (*((uint32_t *)data) == DISCONNECT_REQ)
		{
			/* disconnect current connection */
			ecrobot_disconnect_usb();
			show_init_screen();
			return false;
		}
		*out_location = *((T_TARGET_LOCATION *)data);
		display_target_location(*out_location);
		return true;
	}
	return false;
}



void send_calibration_data(int8_t position, char axis, uint8_t power, bool positive_direction) {
    T_SEND_PACKAGE send_package = {
        position,
        axis,
        power,
        positive_direction,
    };
    ecrobot_send_usb((uint8_t *)&send_package, 0, sizeof(T_SEND_PACKAGE));
}


/* 1msec periodical Task */
TASK(Task_ts1)
{
	GetResource(USB_Rx);
	ecrobot_process1ms_usb(); /* USB process handler (must be invoked every 1msec) */
	ReleaseResource(USB_Rx);
	TerminateTask();
}