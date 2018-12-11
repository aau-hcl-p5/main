#include <stdint.h>

#include <math.h>

typedef struct {
    double input_0;
} T_MODEL_INPUT;

typedef struct {
    double output_0;
} T_MODEL_EXECUTION_RESULT;


double sigmoid(double x)
{
     double exp_value;
     double return_value;

     /*** Exponential calculation ***/
     exp_value = exp((double) -x);

     /*** Final sigmoid value ***/
     return_value = 1 / (1 + exp_value);

     return return_value;
}
double WEIGHTS_LAYER_0[1][30] = {
    { 41.02362739423132, 0.07326578123183776, -0.35225531640487057, 68.54660253440136, 0.3403204332633309, -3.003420120497935, 41.36178888850476, 33.92166738318459, 1.444383198470362, 4.607787602364251, -0.20232091142289793, 55.97634680977362, 7.822450689392026, 9.80162799971571, -0.627977435885111, -0.5640833716689001, 0.02542635598370202, -2.242139244260901, -2.704235183450073, 58.06162779547464, 3.7377855952589703, 0.5754924582771261, 25.22167340639746, 1.2296295870521183, 11.516630656611337, 0.5548089973871464, 0.2658099104560499, -0.003887410573051304, 9.075862754180028, 1.486448402516184 }
};
double WEIGHTS_LAYER_1[30][1] = {
    { -3.1479984775579664 },
    { 2.34833859088355 },
    { 1.0892992371894035 },
    { -3.5825763977689906 },
    { -1.425461938896987 },
    { 0.3160355143297681 },
    { -2.0349314029556798 },
    { -2.0844983196538815 },
    { -1.335164382404256 },
    { -1.1627207165551536 },
    { 0.02024325007027454 },
    { -2.692828691557629 },
    { -1.3565476768518434 },
    { 1.6812739646157326 },
    { -0.09554411920011949 },
    { -0.12566358070699366 },
    { 2.8903094910215126 },
    { -0.08137968699235854 },
    { 0.517635487306487 },
    { -2.6266001285888154 },
    { -0.41452102922743694 },
    { -1.1761446172959846 },
    { -2.4940560053516143 },
    { -1.5435744888883252 },
    { 1.553116709371428 },
    { -1.3878182446802394 },
    { -1.304636719009192 },
    { 41.3127699381189 },
    { -1.3840083993575674 },
    { -1.5379264105093005 }
};
double BIAS_LAYER_0[30] = {
    0.8933869221990043, -0.1775978168757636, -0.1626072118349404, 1.580613794288218, -0.1625959324498769, -0.15577758166071085, 0.9908907795938928, 0.41235520000840903, 0.18248820236061722, 0.28427209967553024, 0.012971493292155745, 1.1400136031541968, 0.20996155281873813, 0.38760003804344023, -0.224308750419489, -0.12964634054932245, -0.4738266395381716, -0.28905224150822867, -0.2821389259544539, 1.2381269394372367, -0.018634471161338324, 0.20860837920612077, 0.2790508298092986, 0.14581457254834992, 0.12763025778386697, -0.08305053547492466, 0.12471147791408932, 2.841073065035026, 0.3718817695238158, 0.14783044317372415
};
double BIAS_LAYER_1[1] = {
    -1.0940552408392117
};
T_MODEL_EXECUTION_RESULT calculate_model_down(T_MODEL_INPUT input) {
    double intermediate_result_0[] = { input.input_0 };
    double intermediate_result_1[30];
    for (int i = 0; i < 30; i++) {
        double sum = 0;
        for (int j = 0; j < 1; j++) {
            sum += WEIGHTS_LAYER_0[j][i] * intermediate_result_0[j];
        }
        intermediate_result_1[i] = sigmoid(sum + BIAS_LAYER_0[i]);
    }
    double intermediate_result_2[1];
    for (int i = 0; i < 1; i++) {
        double sum = 0;
        for (int j = 0; j < 30; j++) {
            sum += WEIGHTS_LAYER_1[j][i] * intermediate_result_1[j];
        }
        intermediate_result_2[i] = (sum + BIAS_LAYER_1[i]);
    }
    T_MODEL_EXECUTION_RESULT result;
    result.output_0 = intermediate_result_2[0];
    return result;
}
