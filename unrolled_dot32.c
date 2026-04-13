#include <stdint.h>
#include <stdio.h>

#ifndef N
#define N 4096
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

    long long s0=0, s1=0, s2=0, s3=0, s4=0, s5=0, s6=0, s7=0;
    long long s8=0, s9=0, s10=0, s11=0, s12=0, s13=0, s14=0, s15=0;
    long long s16=0, s17=0, s18=0, s19=0, s20=0, s21=0, s22=0, s23=0;
    long long s24=0, s25=0, s26=0, s27=0, s28=0, s29=0, s30=0, s31=0;

    for (int i = 0; i < N; i += 32) {
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
        s16 += (long long)A[i+16] * B[i+16];
        s17 += (long long)A[i+17] * B[i+17];
        s18 += (long long)A[i+18] * B[i+18];
        s19 += (long long)A[i+19] * B[i+19];
        s20 += (long long)A[i+20] * B[i+20];
        s21 += (long long)A[i+21] * B[i+21];
        s22 += (long long)A[i+22] * B[i+22];
        s23 += (long long)A[i+23] * B[i+23];
        s24 += (long long)A[i+24] * B[i+24];
        s25 += (long long)A[i+25] * B[i+25];
        s26 += (long long)A[i+26] * B[i+26];
        s27 += (long long)A[i+27] * B[i+27];
        s28 += (long long)A[i+28] * B[i+28];
        s29 += (long long)A[i+29] * B[i+29];
        s30 += (long long)A[i+30] * B[i+30];
        s31 += (long long)A[i+31] * B[i+31];
    }

    long long sum =
        s0+s1+s2+s3+s4+s5+s6+s7+
        s8+s9+s10+s11+s12+s13+s14+s15+
        s16+s17+s18+s19+s20+s21+s22+s23+
        s24+s25+s26+s27+s28+s29+s30+s31;

    printf("unrolled_dot32=%lld\n", sum);
    return 0;
}
