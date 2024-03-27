#include "item.h" 
typedef struct Dir{
  Item dir;
  struct Dir *parent;
  int n_children;
  int array_size;
  Item *childrens;
} Dir ;
typedef struct {
  Item *item;
  int array_size;
  int n_children;
} DirList;
extern Dir* current_dir = NULL;


DirList read_dir(int index);
