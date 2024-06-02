#ifndef DIR_H
#define DIR_H
#include "../disk/disk.h"
#include "item.h"

// initialize the current directory
void dir_init(void);

// get the number of children in the directory
static int get_n_children(Item *childrens, int right);

// read the content of the directory from the virtual disk `return a DirList`
// if the index is 0 then DirList is `created not read from the disk`
DirList read_dir(int index);

// write the content of the directory to the virtual disk
void write_dir(void);

// find the directory by name and make sure that the name can be taken
int dir_search(const char *name);

// find the file by name and make sure that the name can be taken
int file_search(const char *name);

// add the item to the directory object
void add_to_dir(Item item);

// delete the item from the directory object
void delete_item(int index);

// change the numb of
int change_dir(const char *name);

// make the directory with the name
void make_dir(char *name);

// free the current directory with its parents from the memory
void back_dir(void);

// copy the directory to the new directory
CurrentDir *copy_dir(CurrentDir *new_dir, CurrentDir *old_dir);

// free the current directory from the memory
void free_current_dir(void);

// delete the directory with the name
void delete_dir(const char *name);

#endif
