#include "vector.h"


#define MOVEMENT_THRESHOLD 3

/*
 * Custom function for getting the square root as there is issues with math.h
 * returning incorrect answers
 */
double root(double n){
    double lo = 0, hi = n, mid;
    for(int i = 0 ; i < 1000 ; i++){
        mid = (lo+hi)/2;
        if(mid*mid == n) return mid;
        if(mid*mid > n) hi = mid;
        else lo = mid;
    }
    return mid;
}

/*
 * Custom function for getting the squared version of an int, as there is issues with math.h
 * returning incorrect answers
 */
int sq(int x) {
    return (x * x);
}


// Checks whether locations are the same within a margin of error of MOVEMENT_THRESHOLD
bool is_locations_equals(T_VECTOR target1, T_VECTOR target2) {
    int distance = root(sq(target1.x - target2.x) + sq(target1.y - target2.y));
    return distance < MOVEMENT_THRESHOLD;
}