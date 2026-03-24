#include <stdint.h>
#include <stdio.h>

#ifndef N
#define N 1024
#endif

#ifndef K
#define K 16
#endif

static int32_t x[N];
static int32_t h[K];
static int32_t y[N];

static void init() {
  for (int i = 0; i < N; i++) {
    x[i] = (i * 3 + 1) % 17;
    y[i] = 0;
  }
  for (int k = 0; k < K; k++) {
    h[k] = (k * 5 + 7) % 19;
  }
}

int main() {
  init();

  for (int i = K; i < N; i++) {
    int32_t acc = 0;
    for (int k = 0; k < K; k++) {
      acc += x[i - k] * h[k];
    }
    y[i] = acc;
  }

  long long sum = 0;
  for (int i = 0; i < N; i++) {
    sum += y[i];
  }

  printf("fir_sum=%lld\n", sum);
  return 0;
}
