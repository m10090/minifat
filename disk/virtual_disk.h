#ifndef VIRTUAL_DISK_H
void disk_init();
// Function to write a block to the virtual disk
void write_block(const char* buffer, int block_number);

// Function to read a block from the virtual disk
char* read_block(int block_number);
#endif // !VIRTUAL_DISK_H
