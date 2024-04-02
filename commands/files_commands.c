#include "../cli.h"
#include <string.h>
int rename_file(char *filename, char *newname) {
  int file_idx;
  if ((file_idx = file_search(filename)) == -1) {
    printf("file not found\n");
    return 1;
  }
  strcpy(current_dir->dir_list.childrens[file_idx].name, newname);
  write_dir();
  return 0;
}
int delete_file(char *name){
  int file_idx;
  if ((file_idx = file_search(name)) == -1) {
    printf("file not found\n");
    return 1;
  }
  delete_item(file_idx);
  return 0;
}
