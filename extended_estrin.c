#include <stdint.h>
#include <stdio.h>

#ifndef N
#define N 4096
#endif

static int32_t xvals[N];
static int32_t c[16];

static void init() {
    for (int i = 0; i < N; i++) {
        xvals[i] = (i * 7 + 3) % 23 + 1;
    }
    for (int i = 0; i < 16; i++) {
        c[i] = (i * 5 + 3) % 29 + 1;
    }
}

int main() {
    init();

    long long sum = 0;

    for (int i = 0; i < N; i++) {
        int32_t x   = xvals[i];
        int32_t x2  = x * x;
        int32_t x4  = x2 * x2;
        int32_t x8  = x4 * x4;

        int32_t g0 = c[0]  + c[1]  * x;
        int32_t g1 = c[2]  + c[3]  * x;
        int32_t g2 = c[4]  + c[5]  * x;
        int32_t g3 = c[6]  + c[7]  * x;
        int32_t g4 = c[8]  + c[9]  * x;
        int32_t g5 = c[10] + c[11] * x;
        int32_t g6 = c[12] + c[13] * x;
        int32_t g7 = c[14] + c[15] * x;

        int32_t h0 = g0 + g1 * x2;
        int32_t h1 = g2 + g3 * x2;
        int32_t h2 = g4 + g5 * x2;
        int32_t h3 = g6 + g7 * x2;

        int32_t q0 = h0 + h1 * x4;
        int32_t q1 = h2 + h3 * x4;

        int32_t y = q0 + q1 * x8;

        sum += y;
    }

    printf("extended_estrin=%lld\n", sum);
    return 0;
}
