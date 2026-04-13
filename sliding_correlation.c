#include <stdint.h>
#include <stdio.h>

#ifndef N
#define N 4096
#endif

static int32_t X[N];
static int32_t Y[N];

static void init() {
    for (int i = 0; i < N; i++) {
        X[i] = (i * 7 + 3) % 23;
        Y[i] = (i * 5 + 1) % 19;
    }
}

int main() {
    init();

    long long total = 0;

    for (int i = 4; i < N; i++) {
        long long c =
            (long long)X[i]   * Y[i]   +
            (long long)X[i-1] * Y[i-1] +
            (long long)X[i-2] * Y[i-2] +
            (long long)X[i-3] * Y[i-3] +
            (long long)X[i-4] * Y[i-4];
        total += c;
    }

    printf("sliding_correlation=%lld\n", total);
    return 0;
}
