#ifndef VIRTUAL_DISK_H
#define VIRTUAL_DISK_H

// initialize the virtual disk
void disk_init();

// Function to write a block to the virtual disk
void write_block(const char* buffer, int block_number);

// Function to read a block from the virtual disk the return a buffer `must be freed`
char* read_block(int block_number);
#endif // !VIRTUAL_DISK_H
