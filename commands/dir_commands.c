#include "../cli.h" // for linter purpose this is useless but it will make the linter "happy"
#include <stdio.h>
#include <string.h>
int md() {
  char *paths = strtok(NULL, " ");
  if (paths == NULL) {
    printf("md: missing operand\n");
    return 1;
  }
  do {
    char name[11];
    strncpy(name, paths, 11);
    // check if the directory name cotains a '/'
    if (strchr(name, '/') != NULL) {
      printf("md :cannot create directory recursive path");
      return 1;
    }
    if (dir_search(name) != -1) {
      printf("md: cannot create directory '%s': directory exist\n", name);
      printf("%s\n", name);
      return 1;
    }
    // create the directory
    make_dir(name);
    paths = strtok(NULL, " ");
  } while (paths != NULL);
  return 0;
}
int rd() {
  char *paths = strtok(NULL, " ");
  if (paths == NULL) {
    printf("rd: missing operand\n");
    return 1;
  }
  while (paths != NULL) {
    // check if the directory name cotains a '/'
    if (strchr(paths, '/') != NULL || dir_search(paths) == -1) {
      printf("rd: cannot remove directory '%s': No such file or directory\n",
             paths);
      return 1;
    }
    // remove the directory
    char *name = malloc(11);
    strncpy(name, paths, 11);
    delete_item(dir_search(name));
    write_dir();
    free(name);
    paths = strtok(NULL, " ");
  }
  return 0;
}
int cd(char *paths) {
  if (paths == NULL) {
    printf("cd: missing operand\n");
    return 1;
  }
  // check if the directory name cotains a '/'
  if (strchr(paths, '/') != NULL) {
    printf("cd: cannot change directory to '%s': No such file or directory\n",
           paths);
    return 1;
  }
  // change the directory
  char *name = malloc(11);
  strncpy(name, paths, 11);
  change_dir(name);
  free(name);
  return 0;
}
int dir(char *paths) {
  if (paths != NULL)
    return 1;
  Item *childrens = current_dir->dir_list.childrens;
  for (int i = 0; i < current_dir->dir_list.n_children; i++) {
    printf("%s ", childrens[i].name);
  }
  printf("\n");
  return 0;
}
int movDir(char *name, char *path, char *newName) {
  int dir_idx = dir_search(name);
  if (dir_idx == -1) {
    printf("mvdir: cannot move directory '%s': No such file or directory\n",
           name);
    return 1;
  }
  Item dir = current_dir->dir_list.childrens[dir_idx];
  delete_item(dir_idx);
  write_dir();
  char current_dir_path[100];
  strcpy(current_dir_path, current_dir->path);
  path = strtok(path, "/");
  while (path != NULL){
    change_dir(path);
    path = strtok(NULL, "/");
  }
  add_to_dir(dir);
  write_dir();
  free_current_dir();
  dir_init();
  path = strtok(current_dir_path, "/");
  while (path != NULL) {
    change_dir(path);
    path = strtok(NULL, "/");
  }
  return 0;
}
