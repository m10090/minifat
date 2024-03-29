#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Dir* current_dir = NULL;
// initialize the current directory
void dir_init(void) {
  current_dir = (Dir *) malloc(sizeof(Dir));
  // memcpy(current_dir, (Dir*){{"root",{0},2,2,5},NULL,0,0,NULL}, sizeof(Dir));
  current_dir->dir = (Item){"root",{0},2,2,5};
  current_dir->parent = current_dir;
  current_dir->dir_list = read_dir(5);
}
// get the number of children in the directory
int get_n_children(Item* childrens,int right){
  // find the index of the empty file (file that have a attrubute of 0) 
    int left = 0;
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
// read the content of the directory from the disk
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
  n_children =  get_n_children(items,array_size-1);
  #ifdef DEBUG
    printf("Reading dir %d\n", index);
    printf("Array size %d\n", array_size );
    printf("Number of children %d\n", n_children );
  #endif /* ifdef DEB */
  return (DirList){items,  array_size , n_children};
}
void write_dir(void) {
  int np = current_dir->parent->dir.frist_cluster;
  int nc = 0;
  for (int i = 0; i < current_dir->dir_list.array_size; i += BLOCK_SIZE / sizeof(Item)) {
    printf("Writing block %d %d\n", np,i);
    write_block((char*)(current_dir->dir_list.childrens + i), np);
    nc = np;
    np = get_fat_value(np);
    if (np == 0) {
      if(i + BLOCK_SIZE / sizeof(Item) > current_dir->dir_list.array_size)set_value(nc, -1);
      else set_value(nc,np = get_free_block());
    }
    if (np == -1 && i + BLOCK_SIZE / sizeof(Item) < current_dir->dir_list.array_size) {
      np = get_free_block();
      set_value(nc, np);
    }
  }
  set_value(nc, -1);
  
}
int dir_search(char* name) {
  for (int i = 0; i < current_dir->dir_list.array_size; i++) {
    if (strcmp(current_dir->dir_list.childrens[i].name, name) == 0) {
      return i;
     
    }
  }
  return -1;
}
void add_to_dir(Item item) {
  #ifdef DEBUG
    printf("Adding %s to %s\n", item.name, current_dir->dir.name);
    printf("Current dir has %d children\n", current_dir->n_children);
    printf("Current dir has %d array size\n", current_dir->array_size);
  #endif /* ifdef DEBUG */
  
  if (current_dir->dir_list.n_children == current_dir->dir_list.array_size) {
    // Calculate the new array size
    size_t new_array_size = current_dir->dir_list.array_size + BLOCK_SIZE / sizeof(Item);
    
    // Resize the array
    current_dir->dir_list.childrens = reallocf(current_dir->dir_list.childrens, new_array_size * sizeof(Item));
    if (current_dir->dir_list.childrens == NULL) {
      // Handle realloc failure
      fprintf(stderr, "Error: Memory reallocation failed\n");
      exit(EXIT_FAILURE);
    }
    
    // Update the array size
    current_dir->dir_list.array_size = new_array_size;
  }
  
  // Add the new item to the array
  current_dir->dir_list.childrens[current_dir->dir_list.n_children++] = item;
}
void delete_dir(int index) {
  if (index <0) return ;
  Item deleted = current_dir->dir_list.childrens[index];
  for (int i = index; i < current_dir->dir_list.n_children - 1; i++) {
    current_dir->dir_list.childrens[i] = current_dir->dir_list.childrens[i + 1];
  }
  current_dir->dir_list.n_children--;
  if (deleted.frist_cluster == 0) return ;
  int nc = 0 ,
  np = deleted.frist_cluster;
  while (np != -1) {
    nc = np;
    np = get_fat_value(np);
    set_value(nc, 0);
  }
}
// change the current directory to the given name
void change_dir(char* name) {
  // if the name is ".." go back to the parent directory
  if (strcmp(name, "..") == 0) {
    if (current_dir->parent == NULL) {
      printf("Can't go back\n");
      return;
    }
    free_dir();
    current_dir->dir_list = read_dir(current_dir->dir.frist_cluster);
    current_dir->dir = current_dir->dir;
    return;
  }
  int index = dir_search(name);
  if (index == -1) {
    printf("Directory not found\n");
    return;
  }
  if (current_dir->dir_list.childrens[index].attribute == 2) {
    current_dir->parent = current_dir;
    current_dir->dir = current_dir->dir_list.childrens[index];
    current_dir->dir_list = read_dir(current_dir->dir.frist_cluster);
  } else {
    printf("Not a directory\n");
  }
}
// add a directory to the current directory
void make_dir(char* name) {
  if (dir_search(name) != -1) {
    printf("Directory already exists\n");
    return;
  }
  // it gets a block number of 0 until it is made
  Item item = (Item){{0},{0}, 2, 0, 0};
  strncpy(item.name, name,11);
  add_to_dir(item);
  write_dir();
  current_dir->dir_list = read_dir(current_dir->dir.frist_cluster);
}
// free the current directory (from memory) and go back to the parent directory
void free_dir(void){
  Dir* parent = current_dir->parent;
  free(current_dir->dir_list.childrens);
  free(current_dir);
  current_dir = parent;
}
// deep copy the given current directory to the new directory 
// and set the current directory to the new directory
Dir* copy_dir(Dir* new_dir, Dir* old_dir) {
  Dir* parents = NULL;
  if (old_dir->parent != NULL) {
    parents = copy_dir(new_dir->parent, old_dir->parent);
  }
  // copy the current directory
  new_dir->dir = old_dir->dir;
  new_dir->parent = parents;
  DirList dir_list = old_dir->dir_list;
  // copy the childrens of the current directory
  dir_list.childrens = (Item*)malloc(dir_list.array_size * sizeof(Item));
  dir_list.array_size = old_dir->dir_list.array_size;
  dir_list.n_children = old_dir->dir_list.n_children;
  memcpy(dir_list.childrens, old_dir->dir_list.childrens, dir_list.array_size * sizeof(Item));
  new_dir->dir_list = dir_list; 
  return new_dir;
}
// free the current directory with its parents
void free_current_dir(void) {
  while (current_dir != NULL) {
    free_dir();
  }
}
