#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ARRAY_SIZE 10000

void bubbleDown(int numbers[], int index, int len) {
  int leftChildIndex = 2 * index + 1;
  int rightChildIndex = 2 * index + 2;

  if (leftChildIndex >= len) {
    return; // node at index is a leaf
  }

  int minIndex = index;

  if (numbers[leftChildIndex] > numbers[index]) {
    minIndex = leftChildIndex;
  }
  if ((rightChildIndex < len) &&
      (numbers[rightChildIndex] > numbers[minIndex])) {
    minIndex = rightChildIndex;
  }

  if (minIndex != index) {
    int tmp = numbers[minIndex];
    numbers[minIndex] = numbers[index];
    numbers[index] = tmp;
    bubbleDown(numbers, minIndex, len);
  }
}

void makeHeap(int numbers[], int len) {
  for (int i = len - 1; i >= 0; i--) {
    bubbleDown(numbers, i, len);
  }
}

void heapSort(int numbers[], int len) {
  makeHeap(numbers, len);

  for (int i = 0; i < len; i++) {
    int tmp = numbers[0];
    numbers[0] = numbers[len - 1 - i];
    numbers[len - 1 - i] = tmp;
    bubbleDown(numbers, 0, len - 1 - i);
  }
}

void process() {
  int i;
  for (i = 0; i < ARRAY_SIZE; i++) {
    put (i, lrand48 ());
  }

  heapSort(arr, ARRAY_SIZE);

}
