#include "disk.h"

int fat[BLOCK_SIZE] = {0};

// the number of items in a fat block
const int fat_block = BLOCK_SIZE / sizeof(int);

void init_fat(int file_exists) {
  int i;
  if (file_exists) {
    read_fat_table();
    return;
  }
  // the super block
  fat[0] = -1;
  // Initialize the fat table
  for (int i = 1; i < FAT_SIZE; i++) {
    fat[i] = i + 1;
  }
  fat[FAT_SIZE] = -1;
  // root dir
  fat[FAT_SIZE + 1] = -1;
  write_fat_table();
}
void write_fat_table(void) {
  for (int i = 0; i < FAT_SIZE; i++) {
    write_block((char *)fat + BLOCK_SIZE * i, i + 1);
  }
}

void read_fat_table(void) {
  for (int i = 0; i < FAT_SIZE; i++) {
    const char *block = read_block(i + 1);
    memcpy((char *)fat + i * BLOCK_SIZE, block, BLOCK_SIZE);
    free((void *)block);
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
