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
extern Dir* current_dir = NULL;


DirList read_dir(int index);
void free_dir(void);
