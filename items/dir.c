#include "dir.h"
#include "../cli.h"
#include "item.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

CurrentDir *current_dir = NULL;

void dir_init(void) {
  current_dir = (CurrentDir *)malloc(sizeof(CurrentDir));
  current_dir->dir = (Item){"root", {0}, 2, -2, 5};
  current_dir->parent = NULL;
  current_dir->dir_list = read_dir(5);
}

static int get_n_children(Item *childrens, int right) {
  // find the index of the empty file (file that have a attrubute of 0)
  int left = 0;
  while (left <= right) {
    int mid = left + (right - left) / 2;
    if (childrens[mid].attribute == 0) {
      right = mid - 1;
    } else {
      left = mid + 1;
    }
  }
  return left;
}

DirList read_dir(int index) {
  int current_pointer = index;
  if (current_pointer == 0)
    // create a new DirList
    return (DirList){NULL, 0, 0};
  Item *items = NULL;
  int array_size = 0;
  while (current_pointer != -1) {
    // increase the size of the array
    array_size += DIR_SIZE;
    items = (Item *)reallocf(items, array_size * sizeof(Item));

    Item *childrens = (Item *)read_block(current_pointer);
    memcpy(items + array_size - DIR_SIZE, childrens, BLOCK_SIZE);
    free(childrens);

    current_pointer = get_fat_value(current_pointer);
  }
  int n_children = get_n_children(items, array_size - 1);
  debug_print("Reading dir %d\n", index);
  debug_print("Array size %d\n", array_size);
  debug_print("Number of children %d\n", n_children);
  return (DirList){items, array_size, n_children};
}

void write_dir(void) {
  int current_cluster = current_dir->dir.frist_cluster;
  int next_cluster = 0;
  // if the directory is frist time created
  if (current_cluster == 0) {
    current_cluster = get_free_block();
    // upadate the frist cluster of the directory
    current_dir->dir.frist_cluster = current_cluster;
    // change the current directory to the parent directory to add the updates
    CurrentDir *current_dir_copy = current_dir;
    current_dir = current_dir->parent;
    current_dir->dir_list.childrens[dir_search(current_dir_copy->dir.name)] =
        current_dir_copy->dir;
    write_dir();
    // back to normal
    current_dir = current_dir_copy;
  }
  debug_print("dir_list size %d\n", current_dir->dir_list.array_size);
  for (int i = 0; i < current_dir->dir_list.array_size; i += DIR_SIZE) {

    debug_print("Writing block %d %d\n", current_cluster, i);
    write_block((char *)(current_dir->dir_list.childrens + i), current_cluster);
    next_cluster = get_fat_value(current_cluster);
    if (next_cluster == -1 &&
        i + DIR_SIZE < current_dir->dir_list.array_size) {
      next_cluster = get_free_block();
      set_value(current_cluster, next_cluster);
    }
    if (next_cluster == 0) {
      next_cluster = get_free_block();
      set_value(current_cluster, next_cluster);
    }
    current_cluster = next_cluster;
  }
  set_value(current_cluster, -1);
}

int dir_search(const char *name) {
  const Item *childrens = current_dir->dir_list.childrens;
  const int n_children = current_dir->dir_list.n_children;
  if (strncmp(name, ".", 11) == 0 || strncmp(name, "..", 11) == 0) {
    return -1;
  }
  for (int i = 0; i < n_children; i++) {
    if ((strncmp(childrens[i].name, name, 11) == 0) &&
        (childrens[i].attribute == 2)) {
      return i;
    }
  }
  return -1;
}

int file_search(const char *name) {
  Item *childrens = current_dir->dir_list.childrens;
  int n_children = current_dir->dir_list.n_children;
  for (int i = 0; i < n_children; i++) {
    if ((strncmp(childrens[i].name, name, 11) == 0) &&
        (childrens[i].attribute == 1)) {
      return i;
    }
  }
  return -1;
}

void add_to_dir(Item item) {
  if (current_dir->dir_list.n_children == current_dir->dir_list.array_size) {
    // update the size of the array in Item
    int new_array_size = current_dir->dir_list.array_size + DIR_SIZE;
    current_dir->dir_list.childrens = reallocf(current_dir->dir_list.childrens,
                                               new_array_size * sizeof(Item));
    current_dir->dir_list.array_size = new_array_size;
  }
  current_dir->dir_list.childrens[current_dir->dir_list.n_children++] = item;
}

// delete both dir and file note: need to save after it
void delete_item(int index) {
  if (index < 0)
    return;
  Item to_delete = current_dir->dir_list.childrens[index];
  current_dir->dir_list.n_children--;
  for (int i = index; i < current_dir->dir_list.n_children; i++) {
    current_dir->dir_list.childrens[i] = current_dir->dir_list.childrens[i + 1];
  }
  current_dir->dir_list.childrens[current_dir->dir_list.n_children] =
      (Item){{0}, {0}, 0, 0, 0};
  if (to_delete.frist_cluster == 0)
    return;
  int nc = 0, np = to_delete.frist_cluster;
  while (np != -1) {
    nc = np;
    np = get_fat_value(np);
    set_value(nc, 0);
  }
}
// change the current directory to the given name
int change_dir(const char *name) {
  // if the name is ".." go back to the parent directory
  if (strncmp(name, "..", 10) == 0) {
    if (current_dir->parent == NULL) {
      printf("Can't go back\n");
      return 1;
    }
    back_dir();
    return 0;
  }
  int index = dir_search(name);
  if (index == -1) {
    printf("Directory not found\n");
    return 1;
  }
  // get next directory content

  CurrentDir *parent = current_dir;
  Item dir = current_dir->dir_list.childrens[index];
  DirList dir_list = read_dir(dir.frist_cluster);

  current_dir = (CurrentDir *)malloc(sizeof(CurrentDir));
  current_dir->dir = dir;
  current_dir->parent = parent;
  current_dir->dir_list = dir_list;

  // update the path of the current directory
  strncpy(current_dir->path, parent->path, 100);
  strcat(current_dir->path, "/");
  strcat(current_dir->path, name);
  current_dir->path[99] = '\0';
  return 0;
}
// add a directory to the current directory
void make_dir(char *name) {
  if (dir_search(name) != -1) {
    printf("Directory already exists\n");
    return;
  }
  // it gets a block number of 0 until it is made
  Item item = (Item){{0}, {0}, 2, 0, 0};

  // add the name
  strncpy(item.name, name, 10);
  item.name[10] = '\0';
  add_to_dir(item);
  write_dir();
}
// free the current directory (from memory) and go back to the parent directory
void back_dir(void) {

  CurrentDir *parent = current_dir->parent;
  // free the current directory
  free(current_dir->dir_list.childrens);
  free(current_dir);

  // go to the parent directory
  current_dir = parent;
}
// deep copy the given current directory to the new directory
// and set the current directory to the new directory
CurrentDir *copy_dir(CurrentDir *new_dir, CurrentDir *old_dir) {
  CurrentDir *parents = NULL;
  if (old_dir->parent != NULL) {
    parents = copy_dir(new_dir->parent, old_dir->parent);
  }
  // copy the current directory
  new_dir->dir = old_dir->dir;
  new_dir->parent = parents;
  DirList dir_list = old_dir->dir_list;
  // copy the childrens of the current directory
  dir_list.childrens = (Item *)malloc(dir_list.array_size * sizeof(Item));
  dir_list.array_size = old_dir->dir_list.array_size;
  dir_list.n_children = old_dir->dir_list.n_children;
  memcpy(dir_list.childrens, old_dir->dir_list.childrens,
         dir_list.array_size * sizeof(Item));
  new_dir->dir_list = dir_list;
  return new_dir;
}

void free_current_dir(void) {
  while (current_dir != NULL) {
    back_dir();
  }
}

void delete_dir(const char *name) {
  change_dir(name);
  // id the directory is uninitalized
  if (0 == current_dir->dir.frist_cluster) {
    change_dir("..");
    delete_item(dir_search(name));
    return;
  }

  const Item *children = current_dir->dir_list.childrens;
  int n_children = current_dir->dir_list.n_children;
  for (int i = n_children - 1; i >= 0; i--) {
    if (2 == children[i].attribute) {
      delete_dir(children[i].name);
    } else {
      delete_item(i);
    }
  }
  // save the change
  write_dir();
  change_dir("..");
  delete_item(dir_search(name));
  return;
}
