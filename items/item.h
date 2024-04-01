#ifndef ITEM_H
#define ITEM_H
typedef  struct  Item {
  char name[11];
  // it should be empty
  char empty[12];
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
  char *path;
} currentDir;
extern currentDir *current_dir;
#include "dir.h"
#include "files.h"
#endif // !ITEM_H
