#include "dir.c"
#include <stdio.h>
int main() {
  init_disk();
  // print_fat_table();
  dir_init();
  for (int i = 0; i < 32; i++) {
    dir_add((struct Item){.name="Mohamed",.empty= {0}, .attribute= 2,.size= 0, .frist_cluster=0});
    
  }
  // printf("%s\n",current_dir->childrens[3]);
  // printf("array size %d\n",current_dir->array_size);
  // printf("number childrens %d\n",current_dir->n_children);
  // printf("size of Item struct %lu\n", sizeof(Item));
  write_dir();
  print_fat_table();
  write_block((unsigned char *)current_dir->childrens, 5);
  Item *buffer = (Item*) read_block(9);
  for (int i = 0; i < 32; i++) {
    printf("%s %d \n", buffer[i].name, i);
  }
  printf("\n");

  return 0;
}
