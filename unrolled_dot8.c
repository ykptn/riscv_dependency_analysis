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

    long long s0=0, s1=0, s2=0, s3=0;
    long long s4=0, s5=0, s6=0, s7=0;

    for (int i = 0; i < N; i += 8) {
        s0 += (long long)A[i+0] * B[i+0];
        s1 += (long long)A[i+1] * B[i+1];
        s2 += (long long)A[i+2] * B[i+2];
        s3 += (long long)A[i+3] * B[i+3];
        s4 += (long long)A[i+4] * B[i+4];
        s5 += (long long)A[i+5] * B[i+5];
        s6 += (long long)A[i+6] * B[i+6];
        s7 += (long long)A[i+7] * B[i+7];
    }

    long long sum = s0+s1+s2+s3+s4+s5+s6+s7;
    printf("unrolled_dot8=%lld\n", sum);
    return 0;
}
