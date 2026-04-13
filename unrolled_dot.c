#include <stdio.h>

#define N 4096

int a[N], b[N];

int main() {
    int s0=0, s1=0, s2=0, s3=0;

    for (int i = 0; i < N; i+=4) {
        s0 += a[i]   * b[i];
        s1 += a[i+1] * b[i+1];
        s2 += a[i+2] * b[i+2];
        s3 += a[i+3] * b[i+3];
    }

    int result = s0 + s1 + s2 + s3;
    printf("%d\n", result);
    return 0;
}
