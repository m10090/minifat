#include "../cli.h"
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
    strncpy(name, paths, 10);
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
    char name[11];
    strncpy(name, paths, 10);
    delete_dir(name);
    write_dir();
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
  char name[11];
  strncpy(name, paths, 10);
  change_dir(name);
  return 0;
}
int dir(char *paths) {
  if (paths != NULL)
    return 1;
  Item *childrens = current_dir->dir_list.childrens;
  for (int i = 0; i < current_dir->dir_list.n_children; i++) {

    if (childrens[i].attribute == 2)
      printf("%s", "\x1b[11m");
    printf("%s ", childrens[i].name);
    if (childrens[i].attribute == 2)
      printf("%s", "\033[0m");
  }
  printf("\n");

  return 0;
}
int mov_dir(char *name, char *copyPath) {
  int dir_idx = dir_search(name);
  if (dir_idx == -1) {
    printf("mvdir: cannot move directory '%s': No such file or directory\n",
           name);
    return 1;
  }
  if (strchr(copyPath, '/') == NULL) {
    printf("mvdir: invalid path\n");
    return 1;
  }
  // get the directory
  Item dir = current_dir->dir_list.childrens[dir_idx];

  // delete the direcotry from the current_dir
  delete_item(dir_idx);
  // getting the directory newName from the copyPath
  const char *newName = strrchr(copyPath, '/') + 1;
  // update the path to not include the newName
  int copyPath_len = strlen(copyPath);
  int newName_len = strlen(newName);
  copyPath[copyPath_len - newName_len - 1] = '\0';

  debug_print("%s", copyPath);

  // saving the current path and oldname
  char current_dir_path[100] = {0};
  strncpy(current_dir_path, current_dir->path, 99);
  char oldname[11] = {0};
  strncpy(oldname, dir.name, 10);

  copyPath = strtok(copyPath, "/");

  while (copyPath != NULL) {
    if (change_dir(copyPath) /* the file doesn't exist */) {
      // reset the directory (back to the root)
      free_current_dir();
      dir_init();
      // go to the current path
      copyPath = strtok(current_dir_path, "/");
      while (copyPath != NULL) {
        change_dir(copyPath);
        copyPath = strtok(NULL, "/");
      }
      strncpy(dir.name, oldname, 10);
      add_to_dir(dir);
      write_dir();
      return 1;
    }
    copyPath = strtok(NULL, "/");
  }
  if (dir_search(newName) == -1) {
    strncpy(dir.name, newName, 10);
    add_to_dir(dir);
    write_dir();
  } else {
    printf("mvdir: cannot move directory '%s': File exists\n", newName);
  }
  free_current_dir();
  dir_init();
  copyPath = strtok(current_dir_path, "/");
  while (copyPath != NULL) {
    change_dir(copyPath);
    copyPath = strtok(NULL, "/");
  }
  write_dir();
  return 0;
}
