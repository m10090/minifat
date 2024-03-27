#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dir.h"
#include "../disk/disk.h"

void dir_init(void) {
  current_dir = (Dir *) malloc(sizeof(Dir));
  // memcpy(current_dir, (Dir*){{"root",{0},2,2,5},NULL,0,0,NULL}, sizeof(Dir));
  current_dir->dir = (Item){"root",{0},2,2,5};
  current_dir->parent = current_dir;
  DirList childrensList = read_dir(5);
  current_dir->childrens = childrensList.item;
  current_dir->n_children = childrensList.n_children;
  current_dir->array_size = childrensList.array_size;
}
int get_size_of_list(Item* childrens,int left,int right){
  // find the index of the empty file (file that have a attrubute of 0) 
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (childrens[mid].attribute == 0) {
            right = mid - 1; // Move to the left half
        } else {
            left = mid + 1; // Move to the right half
        }
    }
    return left;
}
DirList read_dir(int index) {
  int np = index;
  if (np == 0) np = get_free_block();
  Item* items = NULL;
  int array_size = 0;
  int n_children = 0;
  int nc = index;
  while (np != -1) {
    array_size += BLOCK_SIZE / sizeof(Item);
    items = (Item*)reallocf(items, array_size * sizeof(Item) );
    Item* childrens = (Item *)read_block(np);
    nc = np;
    np = get_fat_value(np);
    memcpy( items + array_size - BLOCK_SIZE/ sizeof(Item),  childrens,  (BLOCK_SIZE/sizeof(Item)) * sizeof(Item));
    if (np == 0){
      set_value(nc, -1);
      np = -1;
    }
    free(childrens);
  } 
  n_children =  get_size_of_list(items, array_size - BLOCK_SIZE / sizeof(Item),array_size-1);
  #ifdef DEBUG
    printf("Reading dir %d\n", index);
    printf("Array size %d\n", array_size );
    printf("Number of children %d\n", n_children );
  #endif /* ifdef DEB */
  return (DirList){.item = items, .array_size = array_size , .n_children =n_children};
}
void write_dir(void) {
  int np = current_dir->parent->dir.frist_cluster;
  int nc = 0;
  for (int i = 0; i < current_dir->array_size; i += BLOCK_SIZE / sizeof(Item)) {
    printf("Writing block %d %d\n", np,i);
    write_block((char*)current_dir->childrens + i, np);
    nc = np;
    np = get_fat_value(np);
    if (np == 0) {
      if(i + BLOCK_SIZE < current_dir->array_size)set_value(nc, -1);
      else set_value(nc,np = get_free_block());
    }
    if (np == -1 && i + BLOCK_SIZE / sizeof(Item) < current_dir->array_size) {
      np = get_free_block();
      set_value(nc, np);
    }
  }
  set_value(nc, -1);
  
}
Item dir_search(char* name) {
  for (int i = 0; i < current_dir->array_size; i++) {
    if (strcmp(current_dir->childrens[i].name, name) == 0) {
      return current_dir->childrens[i];
    }
  }
  return (Item){0};
}
void dir_add(Item item) {
  #ifdef DEBUG
    printf("Adding %s to %s\n", item.name, current_dir->dir.name);
    printf("Current dir has %d children\n", current_dir->n_children);
    printf("Current dir has %d array size\n", current_dir->array_size);
  #endif /* ifdef DEB */
  if (current_dir->n_children == current_dir->array_size) {
    current_dir->array_size += BLOCK_SIZE / sizeof(Item);
    current_dir->childrens = (Item*)reallocf(current_dir->childrens, current_dir->array_size);
  }
  current_dir->childrens[current_dir->n_children++] = item;
}

