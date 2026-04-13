#include <stdint.h>
#include <stdio.h>

#ifndef N
#define N 64
#endif

static int32_t a[N];
static int32_t b[N];
static int32_t C[N][N];

static void init() {
    for (int i = 0; i < N; i++) {
        a[i] = (i * 3 + 1) % 17;
        b[i] = (i * 5 + 7) % 19;
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            C[i][j] = 0;
        }
    }
}

static long long checksum() {
    long long s = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            s += C[i][j];
        }
    }
    return s;
}

int main() {
    init();

    for (int i = 0; i < N; i++) {
        int32_t ai = a[i];
        for (int j = 0; j < N; j++) {
            C[i][j] += ai * b[j];
        }
    }

    printf("outer_checksum=%lld\n", checksum());
    return 0;
}
