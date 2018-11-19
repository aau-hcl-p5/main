/* usbtest.c */
#include <string.h>
#include <stdio.h>
#include <stdint.h>

#include "nxt.h"
#include "target_information.h"
#include "data_receive.h"
#include "init_screen.h"
#include "display_data.h"

/* OSEK declarations */
DeclareTask(Task_ts1);
DeclareResource(USB_Rx);

#define SIZEOF_USB_DATA sizeof(T_TARGET_INFORMATION)

bool get_target_information(T_TARGET_INFORMATION *out_information) {
	int32_t len;
	T_TARGET_INFORMATION new_target_information;

	/* critical section */
	GetResource(USB_Rx);
	/* read USB data */
	len = ecrobot_read_usb((uint8_t*)&new_target_information, 0, SIZEOF_USB_DATA);
	ReleaseResource(USB_Rx);

	if (len > 0)
	{
		if (new_target_information.status == DISCONNECT_REQ)
		{
			/* disconnect current connection */
			ecrobot_disconnect_usb();
			show_init_screen();
			return false;
		}
		memcpy(out_information, &new_target_information, sizeof(T_TARGET_INFORMATION));
		display_target_information(*out_information);
		return true;
	}
	return false;
}

/* 1msec periodical Task */
TASK(Task_ts1)
{
	GetResource(USB_Rx);
	ecrobot_process1ms_usb(); /* USB process handler (must be invoked every 1msec) */
	ReleaseResource(USB_Rx);
	TerminateTask();
}