#include <stdint.h>
#include <stdio.h>

#ifndef N
#define N 16384
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
    long long s8=0, s9=0, s10=0, s11=0;
    long long s12=0, s13=0, s14=0, s15=0;

    for (int i = 0; i < N; i += 16) {
        s0  += (long long)A[i+0]  * B[i+0];
        s1  += (long long)A[i+1]  * B[i+1];
        s2  += (long long)A[i+2]  * B[i+2];
        s3  += (long long)A[i+3]  * B[i+3];
        s4  += (long long)A[i+4]  * B[i+4];
        s5  += (long long)A[i+5]  * B[i+5];
        s6  += (long long)A[i+6]  * B[i+6];
        s7  += (long long)A[i+7]  * B[i+7];
        s8  += (long long)A[i+8]  * B[i+8];
        s9  += (long long)A[i+9]  * B[i+9];
        s10 += (long long)A[i+10] * B[i+10];
        s11 += (long long)A[i+11] * B[i+11];
        s12 += (long long)A[i+12] * B[i+12];
        s13 += (long long)A[i+13] * B[i+13];
        s14 += (long long)A[i+14] * B[i+14];
        s15 += (long long)A[i+15] * B[i+15];
    }

    long long sum =
        s0+s1+s2+s3+s4+s5+s6+s7+
        s8+s9+s10+s11+s12+s13+s14+s15;

    printf("unrolled_dot16=%lld\n", sum);
    return 0;
}
