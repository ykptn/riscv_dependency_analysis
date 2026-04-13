#include <stdint.h>
#include <stdio.h>

#ifndef N
#define N 4096
#endif

static int32_t x[N];
static int32_t h0[4], h1[4], h2[4], h3[4];

static void init() {
    for (int i = 0; i < N; i++) {
        x[i] = (i * 7 + 3) % 23;
    }

    for (int k = 0; k < 4; k++) {
        h0[k] = (k * 3 + 1) % 17;
        h1[k] = (k * 5 + 2) % 19;
        h2[k] = (k * 7 + 3) % 23;
        h3[k] = (k * 11 + 4) % 29;
    }
}

int main() {
    init();

    long long s0 = 0, s1 = 0, s2 = 0, s3 = 0;

    for (int i = 3; i < N; i++) {
        int32_t x0 = x[i];
        int32_t x1 = x[i-1];
        int32_t x2 = x[i-2];
        int32_t x3 = x[i-3];

        long long y0 = (long long)x0*h0[0] + (long long)x1*h0[1] + (long long)x2*h0[2] + (long long)x3*h0[3];
        long long y1 = (long long)x0*h1[0] + (long long)x1*h1[1] + (long long)x2*h1[2] + (long long)x3*h1[3];
        long long y2 = (long long)x0*h2[0] + (long long)x1*h2[1] + (long long)x2*h2[2] + (long long)x3*h2[3];
        long long y3 = (long long)x0*h3[0] + (long long)x1*h3[1] + (long long)x2*h3[2] + (long long)x3*h3[3];

        s0 += y0;
        s1 += y1;
        s2 += y2;
        s3 += y3;
    }

    long long total = s0 + s1 + s2 + s3;
    printf("filter_bank_4out=%lld\n", total);
    return 0;
}
