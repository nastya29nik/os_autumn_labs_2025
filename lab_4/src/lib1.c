#include <math.h>
#include <stdio.h>

#include "interface.h"


int GCF(int A, int B) {
    if (A <= 0 || B <= 0) {
        fprintf(stderr, "Error: GCF arguments must be natural (>0)\n");
        return -1;
    }
    
    while (B != 0) {
        int temp = B;
        B = A % B;
        A = temp;
    }
    return A;
}

float E(int x) {
    if (x == 0) { 
        return 1.0f;
    }
    return powf(1.0f + 1.0f / (float)x, (float)x);
}