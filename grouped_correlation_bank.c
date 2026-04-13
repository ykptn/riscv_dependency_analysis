#include <stdint.h>
#include <stdio.h>

#ifndef N
#define N 4096
#endif

static int32_t X[N];
static int32_t Y[N];

static void init() {
    for (int i = 0; i < N; i++) {
        X[i] = (i * 13 + 7) % 31;
        Y[i] = (i * 9 + 5) % 27;
    }
}

int main() {
    init();

    long long s0 = 0, s1 = 0, s2 = 0, s3 = 0;

    for (int i = 8; i < N; i += 4) {
        long long c0 = (long long)X[i]   * Y[i]   + (long long)X[i-1] * Y[i-1];
        long long c1 = (long long)X[i+1] * Y[i+1] + (long long)X[i-2] * Y[i-2];
        long long c2 = (long long)X[i+2] * Y[i+2] + (long long)X[i-3] * Y[i-3];
        long long c3 = (long long)X[i+3] * Y[i+3] + (long long)X[i-4] * Y[i-4];

        s0 += c0;
        s1 += c1;
        s2 += c2;
        s3 += c3;
    }

    long long total = s0 + s1 + s2 + s3;
    printf("grouped_correlation_bank=%lld\n", total);
    return 0;
}
