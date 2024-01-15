#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include "util.h"

void nbody(int n, struct particle *ps, int steps) {
  for(int s = 0; s < steps; s++) {
    assert(0); // TODO
  }
}

int main(int argc, char** argv) {
  int steps = 1;
  if (argc < 3) {
    printf("Usage: \n");
    printf("%s <input> <output> [steps]\n", argv[0]);
    return 1;
  } else if (argc > 3) {
    steps = atoi(argv[3]);
  }

  int32_t n;
  struct particle *ps = read_particles(argv[1], &n);

  double bef = seconds();
  nbody(n, ps, steps);
  double aft = seconds();
  printf("%f\n", aft-bef);
  write_particles(argv[2], n, ps);
  free(ps);
}
