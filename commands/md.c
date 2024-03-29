#include <stdio.h>
#include <string.h>
#include "../cli.h"
int md(char *paths){
  if (paths == NULL){
    printf("md: missing operand\n");
    return 1;
  }
  do {
    // check if the directory name cotains a '/'
    if (strchr(paths, '/') != NULL){
      printf("md: cannot create directory '%s': No such file or directory\n", paths);
      return 1;
    }
    // create the directory
    char* name = malloc(11);
    strcpy(name, paths);
    make_dir(name);
    free(name);
  }while((paths = strtok(paths, " ")) != NULL);
  return 0;
}
