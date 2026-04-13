#include <stdint.h>
#include <stdio.h>

#ifndef N
#define N 2048
#endif

static int32_t a[N];

static void init() {
  for (int i = 0; i < N; i++) {
    a[i] = (i * 7 + 3) % 23;
  }
}

int main() {
  init();

  volatile int32_t x = 7;
  int32_t y = 0;

  for (int i = N-1; i >= 0; i--) {
    y = y * x + a[i];
  }

  printf("horner=%d\n", y);
  return 0;
}
