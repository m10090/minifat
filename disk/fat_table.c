#include "disk.h"

int fat[BLOCK_SIZE] = {0};

// the number of items in a fat block
const int fat_block = BLOCK_SIZE / sizeof(int);

void init_fat(char file_exists) {
  int i;
  if (file_exists) {
    read_fat_table();
    return;
  }
  fat[0] = -1;
  fat[1] = 2;
  fat[2] = 3;
  fat[3] = 4;
  fat[4] = -1;
  write_fat_table();
}
void write_fat_table(void) {
  write_block((char *)fat, 1);
  write_block((char *)fat + BLOCK_SIZE, 2);
  write_block((char *)fat + BLOCK_SIZE * 2, 3);
  write_block((char *)fat + BLOCK_SIZE * 3, 4);
}

void read_fat_table(void) {
  bzero(fat, sizeof(int) * BLOCK_SIZE);
  for (int i = 1; i < 5; i++) {
    const char *block = read_block(i);
    // Temporary integer array to hold the data from the block
    int temp[fat_block];
    memcpy(temp, block, BLOCK_SIZE);
    free((void *)block);

    // Copy data from temporary array into fat
    for (int j = 0; j < fat_block; j++) {
      fat[(i - 1) * fat_block + j] = temp[j];
    }
  }
}

#ifdef DEBUG
void print_fat_table(void) {
  int i;
  printf("[");
  for (i = 0; i < BLOCK_SIZE; i++) {
    printf("%d,", fat[i]);
  }
  printf("]\n");
}
#endif /* ifdef DEBUG */
int get_free_block(void) {
  int i;
  for (i = 0; i < BLOCK_SIZE; i++) {
    if (fat[i] == 0) {
      return i;
    }
  }
  return -1;
}

int get_fat_value(int index) {
  if (index < 0 || index >= BLOCK_SIZE)
    return -1;
  return fat[index];
}

void set_value(int index, int value) {
  if (index < 0 || index >= BLOCK_SIZE)
    return;
  fat[index] = value;
  write_fat_table();
}

long get_free_space(void) {
  int i;
  long count = 0;
  for (i = 0; i < BLOCK_SIZE; i++) {
    if (fat[i] == 0) {
      count++;
    }
  }
  return count;
}
