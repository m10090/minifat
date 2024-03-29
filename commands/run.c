#include <stdio.h>
#include <stdlib.h>
#include "commands.h"
#include <string.h>



// return the last index in the command string 
void runCommand(char *command) {
  // get the index of the first space
  char *token = strtok(command, " ");
  if (token == NULL) {
    printf("This is a simple interactive shell. The following commands are supported:\n");
    printf("  cls: clear the screen\n");
    printf("  exit: exit the shell\n");
    printf("  help: display this help message\n");
    return;
  }
  #ifdef DEBUG
    printf("command: %s\n", command);
  #endif
    if (!strcmp(token, "cls")) {
      system("clear");
      return;
    }
    else if (!strncmp(token, "exit",4)) {
      printf("Exiting the interactive shell. Goodbye!\n");
      exit(0);
    }
    else if (!strncmp(token, "help",4)) {
      token = strtok(NULL, " ");
      help(token);
    }
    else {
      printf("Executing command: %s\n", command);
    }
}
// main entriy point for processing commands
