#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "simulator.h"

//intervals corresponding to window size
//keep track of the individual page accesses for each window

extern void process();

const int MAX_MEMORY_SIZE = 33554432;

int PAGE_SIZE;
int WINDOW_SIZE;
int NUMBER_OF_PAGES;
int NUMBER_OF_WINDOWS;
int ACCESS_COUNT = 0;
//int *working_set_array; //assume we know the number of pages right now.

//count and array for each window
int count;
int *page_array;

//array of counts
int *working_set_array;

typedef struct MemoryNode {
  unsigned int address;
  int value;
  struct MemoryNode *next;
} MemoryNode;

MemoryNode** memory; // hash table, acts as the virtual memory

MemoryNode* new_MemoryNode(unsigned int address, int value)
{
  MemoryNode *new = malloc(sizeof(MemoryNode));
  new->address = address;
  new->value = value;
  new->next = NULL;
  return new;
}

MemoryNode* search_MemoryNode(MemoryNode *head, unsigned int address)
{
  while (head != NULL) {
    if (head->address == address) {
      return head;
    }
    head = head->next;
  }
  return NULL;
}

MemoryNode* insert_MemoryNode(MemoryNode *head, MemoryNode *new)
{
  new->next = head;
  return new;
}

int length_MemoryNode(MemoryNode *head)
{
  int length = 0;
  while (head != NULL) {
    length++;
    head = head->next;
  }
  return length;
}

void create_memory(int page_size)
{
  int num_pages = (MAX_MEMORY_SIZE / page_size);
  memory = (MemoryNode **)malloc(num_pages * sizeof(MemoryNode *));
  printf("Virtual memory successfully created!\n");
}

int hash(unsigned int address) {
  return address % NUMBER_OF_PAGES;
}

int get_memory(unsigned int address)
{
  int page_index = hash(address);
  MemoryNode *node = search_MemoryNode(memory[page_index], address);
  if (node == NULL) {
    printf("Error: get_memory on invalid address\n");
    exit(1);
  } else {
    return node->value;
  }
}

void put_memory(unsigned int address, int value)
{
  int page_index = hash(address);
  MemoryNode *node = search_MemoryNode(memory[page_index], address);
  if (node == NULL) {
    MemoryNode *new = new_MemoryNode(address, value);
    memory[page_index] = insert_MemoryNode(memory[page_index], new);
  } else {
    node->value = value;
  }
}


void init(int psize, int winsize) {
  PAGE_SIZE = psize;
  WINDOW_SIZE = winsize;
  NUMBER_OF_PAGES = MAX_MEMORY_SIZE / PAGE_SIZE;
  NUMBER_OF_WINDOWS = MAX_MEMORY_SIZE / winsize;
  page_array = (int*)malloc(sizeof(int) * NUMBER_OF_PAGES);
  working_set_array = (int*)(malloc(sizeof(int) * NUMBER_OF_WINDOWS));

  create_memory(psize);
}

void working_set(unsigned int address){

  // working_set_array.bucket_array = malloc(sizeof(int) * NUMBER_OF_PAGES);


  int current_working_set = 0;
  int current_page = address / PAGE_SIZE;
  int current_window = ACCESS_COUNT / WINDOW_SIZE;

  if(page_array[current_page] == 0){
    page_array[current_page] = 1;
    current_working_set = 1;
  }

  else{
    current_working_set = 0;
  }

  count += current_working_set;

  //for the last access in the window size update the count and clear the memory
  if(ACCESS_COUNT % WINDOW_SIZE == (WINDOW_SIZE - 1)){
    working_set_array[current_window] = count;
    memset(page_array, 0, NUMBER_OF_PAGES*sizeof(int));
    count = 0;
  }
  ACCESS_COUNT++;
}


void put(unsigned int address, int value) {
  //printf("address: %i\n",address);
  working_set(address);
  put_memory(address, value);
}

int get(unsigned int address) {
  working_set(address);
  return get_memory(address);
}

void done(){

  int min;
  int max;
  float total_count;
  float windows_used = ACCESS_COUNT / WINDOW_SIZE;

  int i;
  //printf("NUMBER_OF_WINDOWS: %i\n",NUMBER_OF_WINDOWS);
  for(i = 0; i < windows_used; i++){
    min = i * WINDOW_SIZE;
    max = min + WINDOW_SIZE - 1;
    printf("Window %i (Memory Accesses %i to %i) Working Set Size: %i\n", i, min, max, working_set_array[i]);
    //printf("hi\n");
    total_count += working_set_array[i];
  }

  float avg = total_count/windows_used;

  printf("Average working set size taken over all memory references: %f\n", avg);
}

int main(int argc, char *argv[]) {

  if (argc != 3) {
    printf("Invalid input arguments!\n");
    exit(1);
  }

  int page_size = atoi(argv[1]);
  int window_size = atoi(argv[2]);

  init(page_size, window_size);
  printf("Running process...\n");
  process();
  printf("Analysis complete!\n");
  return 0;
}
