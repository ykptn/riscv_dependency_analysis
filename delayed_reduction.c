#include <stdint.h>
#include <stdio.h>

#ifndef N
#define N 4096
#endif

static int32_t A[N];
static int32_t B[N];
static int64_t TMP[N];

static void init() {
    for (int i = 0; i < N; i++) {
        A[i] = (i * 3 + 1) % 17;
        B[i] = (i * 11 + 5) % 29;
        TMP[i] = 0;
    }
}

int main() {
    init();

    for (int i = 0; i < N; i++) {
        TMP[i] = (int64_t)A[i] * B[i];
    }

    long long sum = 0;
    for (int i = 0; i < N; i++) {
        sum += TMP[i];
    }

    printf("delayed_reduction=%lld\n", sum);
    return 0;
}
