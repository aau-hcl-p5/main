#ifndef USB_H
#define USB_H

#include <stdbool.h>

#include "target_information.h"

extern bool get_target_information(T_TARGET_INFORMATION *out_information);

#endif
