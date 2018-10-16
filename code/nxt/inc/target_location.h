#ifndef TARGET_LOCATION_H
#define TARGET_LOCATION_H

#include <stdint.h>

typedef struct {
  int32_t x : 10;
  int32_t y : 10;
  uint32_t timestamp : 12;
} T_TARGET_LOCATION;

#endif
