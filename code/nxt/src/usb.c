/* usbtest.c */
#include <string.h>
#include <stdio.h>
#include <stdint.h>

#include "nxt.h"
#include "vector.h"
#include "usb.h"
#include "display.h"
#include "calibration.h"


#define SIZEOF_USB_DATA sizeof(T_TARGET_INFORMATION)
DeclareResource(USB_Rx);

bool get_status_code(STATUS_CODE *out_code) {
    int32_t len;
    STATUS_CODE new_code;

    /* critical section */
    GetResource(USB_Rx);
    /* read USB data */
    len = ecrobot_read_usb((uint8_t*)&new_code, 0, sizeof(STATUS_CODE));
    ReleaseResource(USB_Rx);

    if (len > 0)
    {
        memcpy(out_code, &new_code, sizeof(STATUS_CODE));
        return true;
    }
    return false;
}


bool get_target_location(T_VECTOR *out_location) {
	int32_t len;
    T_VECTOR new_location;

	/* critical section */
	GetResource(USB_Rx);
	/* read USB data */
	len = ecrobot_read_usb((uint8_t*)&new_location, 0, sizeof(T_VECTOR));
	ReleaseResource(USB_Rx);

	if (len > 0)
	{
		memcpy(out_location, &new_location, sizeof(T_VECTOR));
		return true;
	}
	return false;
}





bool send_calibration_data(int16_t angle, bool is_x, T_POWER_TUPLE pwr) {
    SEND_PACKAGE pkg = {angle, is_x, pwr.positive, pwr.negative};
    int16_t val = 15;
    GetResource(USB_Rx);
    int resp = ecrobot_send_usb((uint8_t *)&(pkg), 0, sizeof(SEND_PACKAGE)) > 0;
    ReleaseResource(USB_Rx);
    return resp;
}

