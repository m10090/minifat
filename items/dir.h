#ifndef DIR_H
#define DIR_H
#include "item.h"
#include "../disk/disk.h"
void dir_init(void);
int get_n_children(Item *childrens, int right);
DirList read_dir(int index);
void write_dir(void);
int dir_search(char *name);
int file_search(char *name);
void add_to_dir(Item item);
void delete_item(int index);
int change_dir(char *name);
void make_dir(char *name);
void free_dir(void);
currentDir *copy_dir(currentDir *new_dir, currentDir *old_dir);
void free_current_dir(void);
#endif
