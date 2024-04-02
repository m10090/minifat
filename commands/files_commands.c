#include "../cli.h"
#include <string.h>
int rename_file(char *filename, char *newname) {
  int file_idx;
  if ((file_idx = file_search(filename)) == -1) {
    printf("file not found");
  }
  strcpy(current_dir->dir_list.childrens[file_idx].name, newname);
  write_dir();
  return 0;
}
