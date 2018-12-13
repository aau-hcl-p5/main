#include "model_adapter.h"
#include "movement.h"
#include "calibration.h"

typedef struct {
    double input_0;
} T_MODEL_INPUT;

typedef struct {
    double output_0;
} T_MODEL_EXECUTION_RESULT;

extern T_MODEL_EXECUTION_RESULT calculate_model_down(T_MODEL_INPUT input);
extern T_MODEL_EXECUTION_RESULT calculate_model_up(T_MODEL_INPUT input);

/*
 * Function: get_required_power
 * ----------------------------
 *   Using get_current_revolution() and the y_axis_powers for determining
 *     the required power on a direction.
 *     for x, this is always 15.
 *
 *   axis: AXIS_X or AXIS_Y for which axis power is required
 *   positive_direction: POSITIVE or NEGATIVE for which direction, on the axis.
 *
 *   returns: the required power for moving a given direction on a given axis.
 */
int8_t get_required_power(char axis, T_DIRECTION direction) {
    if (axis == 'x') {
        return 25;
    } 
    T_MODEL_INPUT input = { get_current_revolution().y + REVOLUTION_OFFSET };
    if (direction == POSITIVE) {
        return calculate_model_up(input).output_0;
    }
    return calculate_model_down(input).output_0;
}