#include <stdint.h>
#include <stdio.h>

#ifndef N
#define N 4096
#endif

static int32_t xvals[N];
static int32_t coeff[8];

static void init() {
    for (int i = 0; i < N; i++) {
        xvals[i] = (i * 7 + 3) % 23 + 1;
    }

    coeff[0] = 3;
    coeff[1] = 5;
    coeff[2] = 7;
    coeff[3] = 11;
    coeff[4] = 13;
    coeff[5] = 17;
    coeff[6] = 19;
    coeff[7] = 23;
}

int main() {
    init();

    long long sum = 0;

    for (int i = 0; i < N; i++) {
        int32_t x  = xvals[i];
        int32_t x2 = x * x;
        int32_t x4 = x2 * x2;

        int32_t g0 = coeff[0] + coeff[1] * x;
        int32_t g1 = coeff[2] + coeff[3] * x;
        int32_t g2 = coeff[4] + coeff[5] * x;
        int32_t g3 = coeff[6] + coeff[7] * x;

        int32_t h0 = g0 + g1 * x2;
        int32_t h1 = g2 + g3 * x2;

        int32_t y = h0 + h1 * x4;

        sum += y;
    }

    printf("estrin_2level=%lld\n", sum);
    return 0;
}
