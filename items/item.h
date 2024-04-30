#ifndef ITEM_H
#define ITEM_H
typedef  struct  Item {
  char name[11];
  // it should be empty
  char empty[11];
  // if a file 1, if a dir 2 if empty 0
  char attribute;
  int size;
  int frist_cluster;
}  Item;
typedef struct {
  Item *childrens;
  int array_size;
  int n_children;
} DirList;
typedef struct currentDir {
  Item dir;
  struct currentDir *parent;
  DirList dir_list;
  char path[100];
} currentDir;
extern currentDir *current_dir;
#include "../disk/disk.h"
#include "../disk/fat_table.h"
#include "../disk/virtual_disk.h"
#endif // !ITEM_H
