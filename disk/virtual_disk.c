#define DISK_PATH "Disk.txt"
#include "disk.h"
#include <stdio.h>
#include <unistd.h>
FILE *disk = NULL;
void disk_init(void) {
  // Initialize the virtual disk
  disk = fopen(DISK_PATH, "r+b");
  printf("working ");
  sleep(2);
  if (disk == NULL) {
    printf("creating new disk file");
    disk = fopen(DISK_PATH, "w+b");
  }
  fseek(disk, 0L, SEEK_END);
  long int size = ftell(disk);
  if (size == 0) {
#ifdef DEBUG
    printf("Creating new disk\n");
#endif /* ifdef DEBUG */
    // Initialize the disk to 1MB of 0s
    int i;
    // the super block
    for (i = 0; i < 1024; i++) {
      fwrite("0", 1, 1, disk);
    }
    // the fat table
    for (; i < 1024 * 4; i++) {
      fwrite("*", 1, 1, disk);
    }
    // the data block
    for (; i < 1024 * 1024; i++) {
      fwrite("\0", 1, 1, disk);
    }
    fclose(disk);
    init_fat(0);
  } else {
    fclose(disk);
#ifdef DEBUG
    printf("size of the disk %ld\n", size);
    printf("reading fat table\n");
#endif
    init_fat(1);
    read_fat_table();
  }
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
// int main() {
//     init();
// }
