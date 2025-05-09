#include "logf.h"

#include <math.h>
#include <stdint.h>

#include "conv_utils.h"

#define LN2      (U32ToF32(0x3f317218u))
#define LN32     (U32ToF32(0x3ecf991fu))
#define RATION23 (U32ToF32(0x3f2aaaabu))

// approximation on [2/3; 4/3]
static float LogF2343(float x);
static int ExtractExpF(float x);
static float ExtractMantF(float x);

// FIXME subnormal
float LogF(float x) {
    if (x <= 0) {
        return NAN;
    }

    float m = ExtractMantF(x);
    float e = (float)ExtractExpF(x);

    return LogF2343(m * RATION23) + LN32 + (e * LN2);
}

// minimax approximation on [2/3; 4/3] in horner form
// degree n = 8
static float LogF2343(float x) {
    const float a0 = U32ToF32(0xc0314438u);
    const float a1 = U32ToF32(0x41065d70u);
    const float a2 = U32ToF32(0xc1752b73u);
    const float a3 = U32ToF32(0x41a94921u);
    const float a4 = U32ToF32(0xc1a34beau);
    const float a5 = U32ToF32(0x4155acfcu);
    const float a6 = U32ToF32(0xc0b4def3u);
    const float a7 = U32ToF32(0x3fb2d8b9u);
    const float a8 = U32ToF32(0xbe1cfda8u);

    float val = 0;
    val = (x * a8 + a7);
    val = val * x + a6;
    val = val * x + a5;
    val = val * x + a4;
    val = val * x + a3;
    val = val * x + a2;
    val = val * x + a1;
    val = val * x + a0;

    return val;
}

#define FLOAT_SIGN_MASK         0b10000000000000000000000000000000u
#define FLOAT_EXPONENT_MASK     0b01111111100000000000000000000000u
#define FLOAT_MANTISSA_MASK     0b00000000011111111111111111111111u
#define FLOAT_EXPONENT_MSB_OFF  0b00111111100000000000000000000000u

#define FLOAT_SIGN_LEN 1
#define FLOAT_EXPONENT_LEN 8
#define FLOAT_MANTISSA_LEN 23

#define FLOAT_SIGN(x_)     ( F32ToU32(x_) & FLOAT_SIGN_MASK )
#define FLOAT_EXPONENT(x_) ( F32ToU32(x_) & FLOAT_EXPONENT_MASK)
#define FLOAT_MANTISSA(x_) ( F32ToU32(x_) & FLOAT_MANTISSA_MASK)


static int ExtractExpF(float x) {
    int e = FLOAT_EXPONENT(x) >> FLOAT_MANTISSA_LEN;
    return e - 127; // 127 = 2^8 - 1
}

static float ExtractMantF(float x) {
    uint32_t m = FLOAT_MANTISSA(x) | FLOAT_EXPONENT_MSB_OFF;
    return U32ToF32(m);
}
