#ifndef FAT_TABLE_H
#define FAT_TABLE_H

// initialize the fat table
void init_fat(char file_exists);

// write the fat table to the disk
void write_fat_table(void);

// read the fat table from the disk
void read_fat_table(void);

#ifdef DEBUG
  // print the fat table
  void print_fat_table(void);
#endif /* ifdef DEBUG */

// get the next free block
int get_free_block(void);

// get fat value at index
int get_fat_value(int index);

// set fat value at index
void set_value(int index, int value);

// get the free space in the disk
long get_free_space(void);

#endif // !FAT_TABLE_H
