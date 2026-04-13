#include <stdint.h>
#include <stdio.h>

#ifndef N
#define N 4096
#endif

static int32_t xs[N];

static void init() {
    for (int i = 0; i < N; i++) {
        xs[i] = (i * 7 + 3) % 23;
    }
}

int main() {
    init();

    long long sum = 0;

    for (int i = 0; i < N; i++) {
        volatile int32_t x = xs[i];

        int32_t c0 = 3;
        int32_t c1 = 5;
        int32_t c2 = 7;
        int32_t c3 = 11;
        int32_t c4 = 13;
        int32_t c5 = 17;
        int32_t c6 = 19;
        int32_t c7 = 23;

        int32_t x2 = x * x;
        int32_t x4 = x2 * x2;

        int32_t p0 = c0 + c1 * x;
        int32_t p1 = c2 + c3 * x;
        int32_t p2 = c4 + c5 * x;
        int32_t p3 = c6 + c7 * x;

        int32_t q0 = p0 + p1 * x2;
        int32_t q1 = p2 + p3 * x2;

        int32_t y = q0 + q1 * x4;

        sum += y;
    }

    printf("estrin_sum=%lld\n", sum);
    return 0;
}
