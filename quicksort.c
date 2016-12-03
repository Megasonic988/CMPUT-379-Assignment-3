#include <stdio.h>
#include <stdlib.h>
#include "simulator.h"

// Iterative Quicksort adapted from
// http://alienryderflex.com/quicksort/ (public domain)

#define ARRAY_SIZE 10000
#define MAX_LEVELS 300

void process() {

  int i;
  for (i = 0; i < ARRAY_SIZE; i++) {
    put (i, lrand48 ());
  }

  int  piv, beg[MAX_LEVELS], end[MAX_LEVELS], L, R, swap ;
  i = 0;

  beg[0] = 0; end[0] = ARRAY_SIZE;
  while (i>=0) {
    L=beg[i]; R=end[i]-1;
    if (L<R) {
      piv=get(L);
      while (L<R) {
        while (get(R)>=piv && L<R) R--; if (L<R) put(L++, get(R));
        while (get(L)<=piv && L<R) L++; if (L<R) put(R--, get(L));
      }
      put(L, piv); beg[i+1]=L+1; end[i+1]=end[i]; end[i++]=L;
      if (end[i]-beg[i]>end[i-1]-beg[i-1]) {
        swap=beg[i]; beg[i]=beg[i-1]; beg[i-1]=swap;
        swap=end[i]; end[i]=end[i-1]; end[i-1]=swap;
      }
    }
    else {
      i--;
    }
  }
  done();
}
