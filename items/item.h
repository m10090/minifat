#ifndef ITEM_H
#define ITEM_H

#define ITEM_FILE 1
#define ITEM_DIR 2

typedef struct {
  char name[11];
  // it should be empty
  char empty[11];
  // if a file 1, if a dir 2 if empty 0
  char attribute;
  int size;
  int frist_cluster;
} Item;

// dynamic array of items
typedef struct {
  Item *childrens;
  int array_size; 
  int n_children; 
} DirList;

typedef struct CurrentDir {
  Item dir;
  struct CurrentDir *parent;
  DirList dir_list;
  char path[100];
} CurrentDir;
extern CurrentDir *current_dir;
#define DIR_SIZE BLOCK_SIZE / sizeof(Item)
#include "../disk/disk.h"
#include "../disk/fat_table.h"
#include "../disk/virtual_disk.h"

#endif // !ITEM_H
