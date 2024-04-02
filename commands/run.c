#include "commands.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// return the last index in the command string
void runCommand(char *command) {
  // get the index of the first space
  char *token = strtok(command, " ");
  if (token == NULL) {
    help();
  }
#ifdef DEBUG
  printf("command: %s\n", command);
#endif
  if (!strcmp(token, "cls")) {
    system("clear");
    return;
  } else if (!strcmp(token, "exit")) {
    printf("Exiting the interactive shell. Goodbye!\n");
    exit(0);
  } else if (!strcmp(token, "help")) {
    help();
  } else if (!strcmp(token, "md")) {
    if (md())
      printf("error Directory created\n");
  } else if (!strcmp(token, "rd")) {
    if (rd())
      printf("error Directory removed\n");
  } else if (!strcmp(token, "cd")) {
    token = strtok(NULL, " ");
    cd(token);
  } else if (!strcmp(token, "dir")) {
    token = strtok(NULL, " ");
    if (dir(token))
      printf("error Directory not found\n");
  } else if (!strcmp(token, "export")) {
    while (token != NULL) {
      token = strtok(NULL, " ");
      export_files(token);
    }
  } else if (!strcmp(token, "import")) {
    while (token != NULL) {
      token = strtok(NULL, " ");
      import_files(token);
    }
  } else if (!strcmp(token, "rename")) {
    char *filename = strtok(NULL, " ");
    char *newname = strtok(NULL, " ");
    if (newname == NULL) { // if filename is null then newname will also be null
      printf("needs arguments\n");
      return;
    }
    rename_file(filename, newname);
  } else if (!strcmp(token, "del")) {
    token = strtok(NULL, " ");
    delete_file(token);
  } else if (!strcmp(token, "type")) {
    // cat the file
    //
  } else if (!strcmp(token, "copy")) {
    // copy file
  }
#ifdef DEBUG
  else if (!strcmp(token, "pfat")) {
    print_fat_table();
  }
#endif /* ifdef DEBUG */
  else {
    printf("Command not found: %s\n", token);
  }
}
// main entriy point for processing commands
