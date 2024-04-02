#include "../cli.h"

void help() {
  char *token = strtok(NULL, " ");
  if (token == NULL) {
    printf("This is a simple interactive shell. The following commands are "
           "supported:\n");
    printf("  cls: clear the screen\n");
    printf("  exit: exit the shell\n");
    printf("  help: display this help message\n");
  } else if (!strcmp(token, "cls")) {
    printf("cls: clear the screen\n");
  } else if (!strcmp(token, "exit")) {
    printf("exit: exit the shell\n");
  } else if (!strcmp(token, "help")) {
    printf("help: display this help message\n");
  } else if (!strcmp(token,"")) {
  
  }
  else {
    printf("Command not found: %s\n", token);
  }
}
