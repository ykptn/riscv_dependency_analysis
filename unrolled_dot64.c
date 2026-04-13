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
    long long s32=0, s33=0, s34=0, s35=0, s36=0, s37=0, s38=0, s39=0;
    long long s40=0, s41=0, s42=0, s43=0, s44=0, s45=0, s46=0, s47=0;
    long long s48=0, s49=0, s50=0, s51=0, s52=0, s53=0, s54=0, s55=0;
    long long s56=0, s57=0, s58=0, s59=0, s60=0, s61=0, s62=0, s63=0;

    for (int i = 0; i < N; i += 64) {
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

        s32 += (long long)A[i+32] * B[i+32];
        s33 += (long long)A[i+33] * B[i+33];
        s34 += (long long)A[i+34] * B[i+34];
        s35 += (long long)A[i+35] * B[i+35];
        s36 += (long long)A[i+36] * B[i+36];
        s37 += (long long)A[i+37] * B[i+37];
        s38 += (long long)A[i+38] * B[i+38];
        s39 += (long long)A[i+39] * B[i+39];
        s40 += (long long)A[i+40] * B[i+40];
        s41 += (long long)A[i+41] * B[i+41];
        s42 += (long long)A[i+42] * B[i+42];
        s43 += (long long)A[i+43] * B[i+43];
        s44 += (long long)A[i+44] * B[i+44];
        s45 += (long long)A[i+45] * B[i+45];
        s46 += (long long)A[i+46] * B[i+46];
        s47 += (long long)A[i+47] * B[i+47];

        s48 += (long long)A[i+48] * B[i+48];
        s49 += (long long)A[i+49] * B[i+49];
        s50 += (long long)A[i+50] * B[i+50];
        s51 += (long long)A[i+51] * B[i+51];
        s52 += (long long)A[i+52] * B[i+52];
        s53 += (long long)A[i+53] * B[i+53];
        s54 += (long long)A[i+54] * B[i+54];
        s55 += (long long)A[i+55] * B[i+55];
        s56 += (long long)A[i+56] * B[i+56];
        s57 += (long long)A[i+57] * B[i+57];
        s58 += (long long)A[i+58] * B[i+58];
        s59 += (long long)A[i+59] * B[i+59];
        s60 += (long long)A[i+60] * B[i+60];
        s61 += (long long)A[i+61] * B[i+61];
        s62 += (long long)A[i+62] * B[i+62];
        s63 += (long long)A[i+63] * B[i+63];
    }

    long long sum =
        s0+s1+s2+s3+s4+s5+s6+s7+
        s8+s9+s10+s11+s12+s13+s14+s15+
        s16+s17+s18+s19+s20+s21+s22+s23+
        s24+s25+s26+s27+s28+s29+s30+s31+
        s32+s33+s34+s35+s36+s37+s38+s39+
        s40+s41+s42+s43+s44+s45+s46+s47+
        s48+s49+s50+s51+s52+s53+s54+s55+
        s56+s57+s58+s59+s60+s61+s62+s63;

    printf("unrolled_dot64=%lld\n", sum);
    return 0;
}
