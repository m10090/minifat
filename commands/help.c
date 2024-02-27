#include "../cli.h"


void help(char* command){
  #ifdef  DEBUG
    printf(" %s\n", command);
  #endif /* ifdef  DEBUG */
  char * token = strtok(command, " ");
  if (token == NULL){
    printf("This is a simple interactive shell. The following commands are supported:\n");
    printf("  cls: clear the screen\n");
    printf("  exit: exit the shell\n");
    printf("  help: display this help message\n");
  }
  else if (!strcmp(token, "cls")) {
    printf("cls: clear the screen\n");
  }
  else if (!strcmp(token, "exit")) {
    printf("exit: exit the shell\n");
  }
  else if (!strcmp(token, "help")) {
    printf("help: display this help message\n");
  }
  else {
    printf("Command not found: %s\n", token);
  }

}
