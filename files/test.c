#include "dir.c"
#include <stdio.h>
int main (){
  init_disk();
  print_fat_table();
  dir_init();
  for (int i = 0; i < 32; i++) {
    dir_add((Item) {"Mohamed", {0}, 2, 0, 0});
  }
  printf("%s\n",current_dir->childrens[0].name);
  printf("%d\n",current_dir->array_size);
  printf("%d\n",current_dir->n_children);
  for (int i = 32; i < current_dir->array_size / 10; i++) {
    printf("%s\n",current_dir->childrens[i].name);
  }
  printf("size of Item struct %lu\n", sizeof(Item));
  write_dir();
  print_fat_table();
  return 0;

}
