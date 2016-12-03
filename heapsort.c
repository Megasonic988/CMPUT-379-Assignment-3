#include <stdlib.h>
#include <stdio.h>
#include "simulator.h"

#define N 1000

void process() {

  int x;
  for (x = 0; x < N; x++) {
    put (x, lrand48 ());
  }

  unsigned int n = N, i = n / 2, parent, child;
  int t;

  for (;;) {      /* Loops until arr is sorted */
    if (i > 0) {  /* First stage - Sorting the heap */
      i--;        /* Save its index to i */
      t = get(i); /* Save parent value to t */
    } else {      /* Second stage - Extracting elements in-place */
      n--;        /* Make the new heap smaller */
      if (n == 0)
        return;        /* When the heap is empty, we are done */
      t = get(n);      /* Save last value (it will be overwritten) */
      put(n, get(0)); /* Save largest value at the end of arr */
    }

    parent = i;        /* We will start pushing down t from parent */
    child = i * 2 + 1; /* parent's left child */

    /* Sift operation - pushing the value of t down the heap */
    while (child < n) {
      if (child + 1 < n && get(child + 1) > get(child)) {
        child++; /* Choose the largest child */
      }
      if (get(child) > t) {       /* If any child is bigger than the parent */
        put(parent, get(child)); /* Move the largest child up */
        parent = child;           /* Move parent pointer to this child */
        // child = parent*2-1; /* Find the next child */
        child = parent * 2 + 1; /* the previous line is wrong*/
      } else {
        break; /* t's place is found */
      }
    }
    put(parent, t); /* We save t in the heap */
    printf("%s\n", "done");
  }
  printf("%s\n", "hereee");

  done();
}
