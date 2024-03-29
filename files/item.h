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
#endif // !ITEM_H
