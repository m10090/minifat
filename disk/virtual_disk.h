
void init_disk();

// Function to write a block to the virtual disk
void write_block(char* buffer, int block_number);

// Function to read a block from the virtual disk
char* read_block(int block_number);
