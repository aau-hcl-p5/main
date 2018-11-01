#ifndef TARGET_LOCATION_H
#define TARGET_LOCATION_H

#include <stdint.h>

typedef struct {
  int32_t x : 8;
  int32_t y : 8;
  uint32_t timestamp : 16;
} T_TARGET_LOCATION;

#endif
