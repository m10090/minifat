#include "cli.h"

#include <stdio.h>
#include <string.h>
void runCommand(char* command);
int main() {
  disk_init();
  dir_init();
  write_dir();
  char command[MAX_COMMAND_LENGTH];
  while (1) {
    printf("%s>", current_dir->path);
    fgets(command, sizeof(command), stdin);
    fflush(stdin);
    // Remove trailing newline character
    command[strcspn(command, "\n")] = 0;

    runCommand(command);
    memset(command, 0, sizeof(command));
  }

  return 0;
}
