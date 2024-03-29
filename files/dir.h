#ifndef DIR_H
#define DIR_H
#include "item.h"
typedef struct {
  Item *childrens;
  int array_size;
  int n_children;
} DirList;
typedef struct Dir{
  Item dir;
  struct Dir *parent;
  DirList dir_list;
} Dir ;
extern Dir* current_dir;


DirList read_dir(int index);
void free_dir(void);
#include "dir.c"
#endif
