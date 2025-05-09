#ifndef CONV_UTILS_H_
#define CONV_UTILS_H_

#include <string.h>
#include <stdint.h>

static float U32ToF32(uint32_t val) {
    float conv = 0;
    memcpy(&conv, &val, sizeof(val));
    return conv;
}

static uint32_t F32ToU32(float val) {
    uint32_t conv = 0;
    memcpy(&conv, &val, sizeof(val));
    return conv;
}

static double U64ToF64(uint64_t val) {
    double conv = 0;
    memcpy(&conv, &val, sizeof(val));
    return conv;
}

static uint64_t F64ToU64(double val) {
    uint64_t conv = 0;
    memcpy(&conv, &val, sizeof(val));
    return conv;
}

#endif // CONV_UTILS_H_