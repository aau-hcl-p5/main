#ifndef TARGET_LOCATION_H
#define TARGET_LOCATION_H

#include <stdint.h>

#define TARGET_FOUND 0
#define NO_TARGET_FOUND 1
#define DISCONNECT_REQ 2
#define READY_FOR_CALIBRATION 3

typedef struct __attribute__((packed)) {
    int16_t x : 8;
    int16_t y : 8;
} T_VECTOR;

typedef struct __attribute__((packed)) {
    T_VECTOR location;
    uint16_t status;
} T_TARGET_INFORMATION;

#endif
