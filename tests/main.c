#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <math.h>
#include <stdbool.h>

// #include <gmp.h>

#include "logf.h"
#include "conv_utils.h"

float ulp_error(float test, float ideal) {

    if (isnan(ideal) || isnan(test)) { return NAN; }
    
    if (!isfinite(ideal)) {
        float ret_val = !isfinite(test) && (signbit(test) == signbit(ideal)) ? 0.0f : INFINITY;
        return ret_val;
    }

    float delta = fabsf(test - ideal);

    if (ideal == 0.0f) {
        float ulp = nextafterf(0.0f, 1.0f);
        return delta / ulp;
    }

    uint32_t bits = F32ToU32(ideal);
    uint32_t abs_bits = bits & 0x7FFFFFFF; // Mask out the sign bit
    // Check if the value is denormal
    int exponent;
    bool is_denormal = (abs_bits & 0x7F800000) == 0;
    if (is_denormal) {
        exponent = -126; // Denormals use exponent -126
    } else {
        exponent = (int)((abs_bits >> 23) & 0xFF) - 127; // Extract exponent
    }
    // Compute ULP
    float ulp;
    if (is_denormal) {
        ulp = ldexpf(1.0f, -149); // ULP for denormals is 2^-149
    } else {
        ulp = ldexpf(1.0f, exponent - 23); // ULP = 2^(exponent - 23)
    }
    // Calculate and return ULP error
    return delta / ulp;
}

int main(const int argc, const char* argv[]) {
    // if (argc < 2) {
    //     fprintf(stderr, "not enought args: %s <log arg>\n", argv[0]);
    //     return EXIT_FAILURE;
    // }

    // float x = atof(argv[1]);
    // float calc = LogF(x);

    // uint32_t val = 0;
    // memcpy(&val, &calc, sizeof(calc));

    // printf("%x\n", val);
    
    float test_val = 1.9f;

    float x1 = LogF(test_val);
    float x2 = logf(test_val);

    printf("my log:   %f, %x\n", x1, F32ToU32(x1));
    printf("libc log: %f, %x\n", x2, F32ToU32(x2));

    double ulp = ulp_error(x1, x2);
    printf("ulp: %lf\n", ulp);

    return 0;
}
