#ifndef TARGET_LOCATION_H
#define TARGET_LOCATION_H

#include <stdint.h>
#include <stdbool.h>

typedef struct __attribute__((packed)) {
    int16_t x : 8;
    int16_t y : 8;
} T_VECTOR;

typedef struct __attribute__((packed)) {
    T_VECTOR location;
    uint16_t status;
} T_TARGET_INFORMATION;


extern bool is_locations_equals(T_VECTOR target1, T_VECTOR target2);

#endif
