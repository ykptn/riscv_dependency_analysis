#include <stdint.h>
#include <stdio.h>

#ifndef N
#define N 64
#endif

static int32_t A[N][N];
static int32_t B[N][N];

static void init() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            A[i][j] = (i * 3 + j * 5 + 1) % 17;
            B[i][j] = 0;
        }
    }
}

static long long checksum() {
    long long s = 0;
    for (int i = 1; i < N-1; i++) {
        for (int j = 1; j < N-1; j++) {
            s += B[i][j];
        }
    }
    return s;
}

int main() {
    init();

    for (int i = 1; i < N-1; i++) {
        for (int j = 1; j < N-1; j++) {
            int32_t sum = 0;
            sum += A[i-1][j-1] * 1;
            sum += A[i-1][j  ] * 2;
            sum += A[i-1][j+1] * 1;
            sum += A[i  ][j-1] * 2;
            sum += A[i  ][j  ] * 4;
            sum += A[i  ][j+1] * 2;
            sum += A[i+1][j-1] * 1;
            sum += A[i+1][j  ] * 2;
            sum += A[i+1][j+1] * 1;
            B[i][j] = sum;
        }
    }

    printf("conv2d_sum=%lld\n", checksum());
    return 0;
}
