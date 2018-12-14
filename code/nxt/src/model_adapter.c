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


int8_t get_minimum_power(char axis, T_DIRECTION direction) {
    if (axis == 'x') {
        return 25;
    } 
    T_MODEL_INPUT input = { get_current_revolution().y + REVOLUTION_OFFSET };
    if (direction == POSITIVE) {
        return calculate_model_up(input).output_0;
    }
    return calculate_model_down(input).output_0;
}