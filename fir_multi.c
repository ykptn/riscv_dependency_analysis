#include <stdint.h>
#include <stdio.h>

#ifndef N
#define N 1024
#endif

#define K 4  // number of outputs (multi-accumulator)

static int32_t x[N];
static int32_t h[K];
static int32_t y[K];

static void init() {
    for (int i = 0; i < N; i++) {
        x[i] = (i * 7 + 3) % 23;
    }
    for (int j = 0; j < K; j++) {
        h[j] = (j * 5 + 1) % 17;
        y[j] = 0;
    }
}

int main() {
    init();

    for (int i = 0; i < N; i++) {
        int32_t xi = x[i];

        // multi-output FIR (parallel accumulators)
        y[0] += xi * h[0];
        y[1] += xi * h[1];
        y[2] += xi * h[2];
        y[3] += xi * h[3];
    }

    int64_t checksum = 0;
    for (int j = 0; j < K; j++) {
        checksum += y[j];
    }

    printf("fir_multi_checksum=%lld\n", checksum);
    return 0;
}
