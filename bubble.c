#include "simulator.h"
#include <stdio.h>
#include <stdlib.h>

#define n 100

void process() {
  int i;
  for (i = 0; i < n; i++) {
    long int val = lrand48();
    put(i, val);
  }

  int c, d, swap;
  for (c = 0; c < (n - 1); c++) {
    for (d = 0; d < n - c - 1; d++) {
      if (get(d) > get(d + 1)) /* For decreasing order use < */
      {
        swap = get(d);
        put(d, get(d + 1));
        put(d + 1, swap);
      }
    }
  }

  done();
}
