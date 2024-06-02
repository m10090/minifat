#include "../cli.h"
#include "disk.h"
#include <stdio.h>
#include <unistd.h>



FILE *disk = NULL;
void disk_init(void) {
  // Initialize the virtual disk
  disk = fopen(DISK_PATH, "r+b");
  printf("working \n");

  if (disk == NULL) {
    printf("creating new disk file\n");
    disk = fopen(DISK_PATH, "w+b");
    if (disk == NULL) {
      printf("Error: Could not create or read virtual disk\n");
      exit(1);
    }
  }
  fseek(disk, 0L, SEEK_END);
  long size = ftell(disk);
  // if the disk is created
  if (size == (long)BLOCK_SIZE * DISK_SIZE) {
    fclose(disk);
    debug_print("size of the disk %ld\n", size);

    printf("reading fat table\n");
    read_fat_table();
    return;
  }
  fseek(disk, 0L, SEEK_CUR);
  // initialize the disk
  debug_print("Creating new disk\n");
  int i;
  // the super block
  for (i = 0; i < BLOCK_SIZE; i++) {
    fwrite("0", 1, 1, disk);
  }
  for (; i < BLOCK_SIZE * DISK_SIZE; i++) {
    fwrite("\0", 1, 1, disk);
  }
  fclose(disk);
  init_fat(0);
}

void write_block(const char *buffer, int block_number) {
  disk = fopen(DISK_PATH, "r+b");
  if (disk == NULL) {
    printf("Error: Could not create or read virtual disk\n");
    exit(1);
  }
  fseek(disk, block_number * BLOCK_SIZE, SEEK_SET);
  fwrite((void *)buffer, 1, BLOCK_SIZE, disk);
  fclose(disk);
}

char *read_block(int block_number) {
  disk = fopen(DISK_PATH, "r+b");
  if (disk == NULL) {
    printf("Error: Could not create or read virtual disk\n");
    exit(1);
  }
  char *buffer = (char *)malloc(BLOCK_SIZE);
  fseek(disk, block_number * BLOCK_SIZE, SEEK_SET);
  fread(buffer, 1, BLOCK_SIZE, disk);
  fclose(disk);
  return buffer;
}
