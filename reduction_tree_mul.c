#include <stdint.h>
#include <stdio.h>

#ifndef N
#define N 8192
#endif

static int32_t A[N];
static int32_t B[N];

static void init() {
    for (int i = 0; i < N; i++) {
        A[i] = (i * 3 + 1) % 17;
        B[i] = (i * 5 + 7) % 19;
    }
}

int main() {
    init();

    long long total = 0;

    for (int i = 0; i < N; i += 8) {
        long long p0 = (long long)A[i+0] * B[i+0];
        long long p1 = (long long)A[i+1] * B[i+1];
        long long p2 = (long long)A[i+2] * B[i+2];
        long long p3 = (long long)A[i+3] * B[i+3];
        long long p4 = (long long)A[i+4] * B[i+4];
        long long p5 = (long long)A[i+5] * B[i+5];
        long long p6 = (long long)A[i+6] * B[i+6];
        long long p7 = (long long)A[i+7] * B[i+7];

        long long q0 = p0 + p1;
        long long q1 = p2 + p3;
        long long q2 = p4 + p5;
        long long q3 = p6 + p7;

        long long r0 = q0 + q1;
        long long r1 = q2 + q3;

        total += r0 + r1;
    }

    printf("reduction_tree_mul=%lld\n", total);
    return 0;
}
