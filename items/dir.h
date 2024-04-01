#ifndef DIR_H
#define DIR_H
#include "item.h"

DirList read_dir(int index);
void free_dir(void);
int dir_search(char *name);
int file_search(char *name);
#include "../disk/disk.h"
#include "dir.c"
#endif
