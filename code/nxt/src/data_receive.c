/* usbtest.c */
#include <string.h>
#include <stdio.h>
#include <stdint.h>

#include "nxt.h"
#include "target_location.h"
#include "data_receive.h"
#include "init_screen.h"
#include "display_data.h"

/* OSEK declarations */
DeclareTask(Task_ts1);
DeclareResource(USB_Rx);

T_TARGET_LOCATION old_location;

#define SIZEOF_USB_DATA sizeof(T_TARGET_LOCATION)

T_TARGET_LOCATION get_target_location() {
	int len;
	U8 data[SIZEOF_USB_DATA]; /* first byte is preserved for disconnect request from host */

    memset(data, 0, SIZEOF_USB_DATA); /* flush buffer */
	/* critical section */
	GetResource(USB_Rx);
	len = ecrobot_read_usb(data, 0, SIZEOF_USB_DATA); /* read USB data */
	ReleaseResource(USB_Rx);
	
	T_TARGET_LOCATION target_location = *((T_TARGET_LOCATION *)data);

	if (len > 0)
	{
		if (*((uint32_t *)&target_location) == DISCONNECT_REQ)
		{
			/* disconnect current connection */
			ecrobot_disconnect_usb();
			show_init_screen();
		}
		else
		{
			display_target_location(target_location);
			old_location = target_location;
		}
	}

	return old_location;
}

/* 1msec periodical Task */
TASK(Task_ts1)
{
	GetResource(USB_Rx);
	ecrobot_process1ms_usb(); /* USB process handler (must be invoked every 1msec) */
	ReleaseResource(USB_Rx);
	TerminateTask();
}