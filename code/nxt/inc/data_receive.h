#ifndef USB_H
#define USB_H

#include <stdbool.h>

#include "target_location.h"

#define DISCONNECT_REQ 0xFFFFFFFF
extern bool get_target_location(T_TARGET_LOCATION *out_location);

#endif
