#include <stdint.h>
#include <stdio.h>

#ifndef N
#define N 4096
#endif

static int32_t A[N];
static int32_t B[N];

static void init() {
    for (int i = 0; i < N; i++) {
        A[i] = (i * 7 + 3) % 23;
        B[i] = (i * 5 + 1) % 19;
    }
}

int main() {
    init();

    long long acc0 = 0, acc1 = 0, acc2 = 0, acc3 = 0;
    long long acc4 = 0, acc5 = 0, acc6 = 0, acc7 = 0;

    for (int i = 0; i < N; i += 8) {
        acc0 += (long long)A[i+0] * B[i+0];
        acc1 += (long long)A[i+1] * B[i+1];
        acc2 += (long long)A[i+2] * B[i+2];
        acc3 += (long long)A[i+3] * B[i+3];
        acc4 += (long long)A[i+4] * B[i+4];
        acc5 += (long long)A[i+5] * B[i+5];
        acc6 += (long long)A[i+6] * B[i+6];
        acc7 += (long long)A[i+7] * B[i+7];
    }

    long long sum = acc0 + acc1 + acc2 + acc3 + acc4 + acc5 + acc6 + acc7;
    printf("multi_accumulator=%lld\n", sum);
    return 0;
}
