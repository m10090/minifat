#include "../cli.h"
#include <string.h>
int renameFile(char *filename, char *newName) {
  int file_idx;
  if ((file_idx = file_search(filename)) == -1) {
    printf("file not found\n");
    return 1;
  }
  strncpy(current_dir->dir_list.childrens[file_idx].name, newName, 10);
  write_dir();
  return 0;
}
int deleteFile(char *name) {
  int file_idx = file_search(name);
  if (file_idx == -1) {
    printf("file not found\n");
    return 1;
  }
  delete_item(file_idx);
  write_dir();
  return 0;
}
int catFile(char *name) {
  int filesize;
  int file_idx;
  if ((file_idx = file_search(name)) == -1) {
    printf("file not found\n");
    return 1;
  }
  char *buffer =
      read_file(current_dir->dir_list.childrens[file_idx].frist_cluster);
  buffer[1023] = 0;
  printf("%s\n", buffer);
  free(buffer);
  return 0;
}
int copyFile(const char *name, char *copyPath) {
  int file_idx = file_search(name);
  if (file_idx == -1) {
    printf("file not found\n");
    return -1;
  }
  const Item *childrens = current_dir->dir_list.childrens;
  char *file_content = read_file(childrens[file_idx].frist_cluster);
  int file_size = childrens[file_idx].size;
  char current_dir_path[100];
  const char *newName = strrchr(copyPath, '/') + 1;
  current_dir_path[strlen(current_dir_path) - strlen(newName) - 1] = '\0';
  strncpy(current_dir_path, current_dir->path, 10);
  copyPath = strtok(copyPath, "/");
  while (copyPath != NULL) {
    if (change_dir(copyPath)) {
      free_current_dir();
      dir_init();
      copyPath = strtok(current_dir_path, "/");
      while (copyPath != NULL) {
        change_dir(copyPath);
        copyPath = strtok(NULL, "/");
      }
      return -1;
    }
    copyPath = strtok(NULL, "/");
  }
  import_buffer(file_content, file_size, newName);
  free(file_content);
  free_current_dir();
  dir_init();
  copyPath = strtok(current_dir_path, "/");
  while (copyPath != NULL) {
    change_dir(copyPath);
    copyPath = strtok(NULL, "/");
  }
  return 0;
}
