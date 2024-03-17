#include <stdio.h>
#define DISK_PATH "Disk.txt"
FILE* disk = NULL;
void init_disk(void) {
    // Initialize the virtual disk
    disk = fopen("Disk.txt", "wb+");
    if (disk == NULL) {
        printf("Error: Could not create or read virtual disk\n");
        exit(1);
    }
    fseek(disk, 0, SEEK_SET);
    long size = ftell(disk);
    if (size == 0) {
        // Initialize the disk to 1MB of 0s
        int i;
        // the super block
        for (i =0;i < 1024; i++){
            fwrite("0", 1, 1, disk);
        }
        // the fat table
        for (; i < 1024*4; i++) {
            fwrite("*", 1, 1, disk);
        }
        // the data block
        for (;i< 1024*1024; i++) {
            fwrite("#", 1, 1, disk);
        }
        fclose(disk);
         init_fat();
        disk = fopen("Disk.txt", "wb+");
    }
    fclose(disk);
}
void write_block(char* buffer, int block_number) {
    disk = fopen(DISK_PATH, "rb+");
    if (disk == NULL) {
        printf("Error: Could not create or read virtual disk\n");
        exit(1);
    }
    fseek(disk, block_number * BLOCK_SIZE, SEEK_SET);
    fwrite(buffer, BLOCK_SIZE, 1, disk);
    fclose(disk);
}
char* read_block(int block_number) {
    disk = fopen(DISK_PATH, "rb");
    if (disk == NULL) {
        printf("Error: Could not create or read virtual disk\n");
        exit(1);
    }
    char* buffer = (char*)malloc(BLOCK_SIZE);
    fseek(disk, block_number * BLOCK_SIZE, SEEK_SET);
    fread(buffer, BLOCK_SIZE, 1, disk);
    fclose(disk);
    return buffer;
}
// int main() {
//     init();
// }
