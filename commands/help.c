#include <stdio.h>
#include <string.h>

void help(void) {
  char *token = strtok(NULL, " ");
  if (token == NULL) {
    printf("This is a simple interactive shell. The following commands are "
           "supported:\n");
    printf("  cls: clear the screen\n");
    printf("  exit: exit the shell\n");
    printf("  help: display this help message\n");
    printf("  copy: copy a file\n");
    printf("  del: delete files\n");
    printf("  rd: remove directory\n");
    printf("  md: make directory\n");
    printf("  cd: change directory\n");
    printf("  dir: list directory\n");
    printf("  type: display the contents of a file\n");
    printf("  rename: rename a file\n");
    printf("  mvd: move directory\n");
  } else if (!strcmp(token, "cls")) {
    printf("cls: clear the screen\n");
  } else if (!strcmp(token, "exit")) {
    printf("exit: exit the shell\n");
  } else if (!strcmp(token, "help")) {
    printf("help: display this help message\n");
  } else if (!strcmp(token, "copy")) {
    printf("copy: copy a file\n");
    printf("Usage: copy <source> <destination/new name>\n");
  } else if (!strcmp(token, "del")) {
    printf("del: delete files\n");
  } else if (!strcmp(token, "rd")) {
    printf("rd: remove directory\n");
  } else if (!strcmp(token, "md")) {
    printf("md: make directory\n");
  } else if (!strcmp(token, "cd")) {
    printf("cd: change directory\n");
  } else if (!strcmp(token, "dir")) {
    printf("dir: list directory\n");
  } else if (!strcmp(token, "type")) {
    printf("type: display the contents of a file\n");
  } else if (!strcmp(token, "rename")) {
    printf("rename: rename a file\n");
  } else if (!strcmp(token, "mvd")) {
    printf("mvd: move directory\n");
    printf("Usage: mv <source> <destination/new name>\n");
  } else {
    printf("Command not found: %s\n", token);
  }
}
