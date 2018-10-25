#include <string.h>

#include "stubs.h"
#include "logic_test.h"
#include "logic.h"

T_TC_RESULT test_target_location_size() {
    return assert_num_equals(4, sizeof(T_TARGET_LOCATION));
}
