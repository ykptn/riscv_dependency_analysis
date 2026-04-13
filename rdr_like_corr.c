#include <stdint.h>
#include <stdio.h>

#ifndef N
#define N 4096
#endif

#ifndef K
#define K 16
#endif

static int32_t x[N];
static int32_t h[K];
static int32_t y[N];

static void init() {
    for (int i = 0; i < N; i++) {
        x[i] = (i * 7 + 3) % 23;
        y[i] = 0;
    }

    // Intentionally use non-power-of-two, nontrivial coefficients
    int32_t coeffs[K] = {3, 5, 7, 11, 13, 17, 19, 23,
                         29, 31, 37, 41, 43, 47, 53, 59};
    for (int k = 0; k < K; k++) {
        h[k] = coeffs[k];
    }
}

static long long checksum() {
    long long s = 0;
    for (int i = 0; i < N; i++) {
        s += y[i];
    }
    return s;
}

int main() {
    init();

    for (int i = K; i < N; i++) {
        int32_t s0 = 0, s1 = 0, s2 = 0, s3 = 0;

        for (int k = 0; k < K; k += 4) {
            s0 += x[i - (k + 0)] * h[k + 0];
            s1 += x[i - (k + 1)] * h[k + 1];
            s2 += x[i - (k + 2)] * h[k + 2];
            s3 += x[i - (k + 3)] * h[k + 3];
        }

        y[i] = (s0 + s1) + (s2 + s3);
    }

    printf("rdr_like_sum=%lld\n", checksum());
    return 0;
}
