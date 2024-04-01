#include "../cli.h" // for linter purpose this is useless but it will make the linter "happy"
#include <stdio.h>
#include <string.h>
int md() {
  char* paths = strtok(NULL, " ");
  if (paths == NULL) {
    printf("md: missing operand\n");
    return 1;
  }
  printf("hi $%s$\n", paths);
  do {
    char *name = malloc(11);
    strncpy(name, paths, 11);
    // check if the directory name cotains a '/'
    if (strchr(name, '/') != NULL || dir_search(name) != -1) {
      printf("md: cannot create directory '%s': file or directory exist\n",
             name);
      printf("%s\n", name);
      return 1;
    }
    // create the directory
    make_dir(name);
    free(name);
    paths=  strtok(NULL, " ");
  } while (paths != NULL);
  return 0;
}
int rd() {
  char* paths = strtok(NULL, " ");
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
    delete_dir(dir_search(name));
    write_dir();
    free(name);
    paths =  strtok(NULL, " ");
  } 
  return 0;
}
int cd(char* paths) {
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

