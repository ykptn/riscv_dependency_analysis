#include <stdint.h>
#include <stdio.h>

#ifndef N
#define N 4096
#endif

static int32_t ar[N], ai[N];
static int32_t br[N], bi[N];

static void init() {
    for (int i = 0; i < N; i++) {
        ar[i] = (i * 3 + 1) % 17;
        ai[i] = (i * 5 + 2) % 19;
        br[i] = (i * 7 + 3) % 23;
        bi[i] = (i * 11 + 4) % 29;
    }
}

int main() {
    init();

    long long s0 = 0, s1 = 0, s2 = 0, s3 = 0;

    for (int i = 0; i < N; i += 4) {
        // Complex multiply:
        // (a+jb)(c+jd) = (ac-bd) + j(ad+bc)

        long long r0 = (long long)ar[i+0] * br[i+0] - (long long)ai[i+0] * bi[i+0];
        long long j0 = (long long)ar[i+0] * bi[i+0] + (long long)ai[i+0] * br[i+0];

        long long r1 = (long long)ar[i+1] * br[i+1] - (long long)ai[i+1] * bi[i+1];
        long long j1 = (long long)ar[i+1] * bi[i+1] + (long long)ai[i+1] * br[i+1];

        long long r2 = (long long)ar[i+2] * br[i+2] - (long long)ai[i+2] * bi[i+2];
        long long j2 = (long long)ar[i+2] * bi[i+2] + (long long)ai[i+2] * br[i+2];

        long long r3 = (long long)ar[i+3] * br[i+3] - (long long)ai[i+3] * bi[i+3];
        long long j3 = (long long)ar[i+3] * bi[i+3] + (long long)ai[i+3] * br[i+3];

        s0 += r0 + j0;
        s1 += r1 + j1;
        s2 += r2 + j2;
        s3 += r3 + j3;
    }

    long long total = s0 + s1 + s2 + s3;
    printf("complex_bank=%lld\n", total);
    return 0;
}
