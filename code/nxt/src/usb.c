/* usbtest.c */
#include <string.h>
#include <stdio.h>
#include <stdint.h>

#include "nxt.h"
#include "vector.h"
#include "usb.h"
#include "display_manager.h"
#include "calibration.h"


#define MAX_SIZE_OF_USB_DATA sizeof(STATUS_CODE) + sizeof(T_VECTOR)

DeclareResource(USB_Rx);

/*
 * Function: get_status_code
 * ----------------------------
 *   Gets statuscode from USB, using STATUS_CODe and T_VECTOR for buffer reading sizes.
 *
 *   *out_code: the response value for the response code
 *   *out_location: the response value for the response code
 */
bool get_status_code(STATUS_CODE *out_code, T_VECTOR *out_location) {
    int32_t len;
    uint8_t buffer[MAX_SIZE_OF_USB_DATA];

    /* critical section */
    GetResource(USB_Rx);
    /* read USB data */
    len = ecrobot_read_usb(buffer, 0, MAX_SIZE_OF_USB_DATA);
    ReleaseResource(USB_Rx);

    if (len == sizeof(STATUS_CODE)) {
        memcpy(out_code, buffer, sizeof(STATUS_CODE));
        return true;
    }
    if (len == MAX_SIZE_OF_USB_DATA) {
        memcpy(out_code, buffer, sizeof(STATUS_CODE));
        memcpy(out_location, buffer + sizeof(STATUS_CODE), sizeof(T_VECTOR));
        return true;
    }
    return false;
}

bool send_calibration_data(int16_t angle, bool is_x, T_POWER_TUPLE pwr) {
    SEND_PACKAGE pkg = {angle, is_x, pwr.positive, pwr.negative};
    GetResource(USB_Rx);
    int resp = ecrobot_send_usb((uint8_t *)&(pkg), 0, sizeof(SEND_PACKAGE)) > 0;
    ReleaseResource(USB_Rx);
    return resp;
}
