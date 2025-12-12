#include <stdio.h>

#include "interface.h"

int GCF(int A, int B) {
    if (A <= 0 || B <= 0) {
        fprintf(stderr, "Error: GCF arguments must be natural (>0)\n");
        return -1;
    }

    int min = (A < B) ? A : B;
    for (int i = min; i > 0; i--) {
        if (A % i == 0 && B % i == 0) {
            return i;
        }
    }
    return 1;
}

float E(int x) {
    float sum = 1.0f;
    float term = 1.0f;
    
    for (int n = 1; n <= x; n++) {
        term = term / n;
        sum += term;
    }
    return sum;
}