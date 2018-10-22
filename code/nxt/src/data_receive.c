/* usbtest.c */
#include <string.h>
#include <stdio.h>
#include <stdint.h>

#include "nxt.h"
#include "target_location.h"
#include "data_receive.h"

/* OSEK declarations */
DeclareTask(Task_ts1);
DeclareTask(Task_usb_read);
DeclareResource(USB_Rx);

#define MAX_NUM_OF_CHAR 16
#define MAX_NUM_OF_LINE 8

#define SIZEOF_USB_DATA sizeof(T_TARGET_LOCATION)

static T_TARGET_LOCATION target_location;

T_TARGET_LOCATION last_target_location() {
    return target_location;
}

static void showInitScreen(void)
{
	display_clear(0);
	display_goto_xy(0, 0);
	display_string("USB TEST");
	display_goto_xy(0, 1);
	display_string("Run usbhost.exe");
	display_update();	
}

static void display_usb_data(T_TARGET_LOCATION loc, int len)
{
	display_clear(0);
	display_goto_xy(0, 0);
	char s[30];
	sprintf(s, "x: %u y: %u t: %hu\n", loc.x, loc.y, loc.timestamp);
	display_string(s);
	display_update();
}

/* ECRobot hooks */
void ecrobot_device_initialize()
{
	ecrobot_init_usb(); /* init USB */
}

void ecrobot_device_terminate()
{
	ecrobot_term_usb(); /* terminate USB */
}


/* 1msec periodical Task */
TASK(Task_ts1)
{
	GetResource(USB_Rx);
	ecrobot_process1ms_usb(); /* USB process handler (must be invoked every 1msec) */
	ReleaseResource(USB_Rx);

	TerminateTask();
}

/* background Task */
TASK(Task_usb_read)
{
	int len;
	U8 data[SIZEOF_USB_DATA]; /* first byte is preserved for disconnect request from host */

	showInitScreen();

	while(1)
  	{
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
				showInitScreen();
			}
			else
			{
				display_usb_data(target_location, len-1);
			}
  		}
	}
}