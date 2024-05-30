#include "commands/run.c"
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

int main() {
  disk_init();
  dir_init();
  write_dir();
  char command[MAX_COMMAND_LENGTH] = {0};
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

void debug_print(const char *format, ...) {
  va_list args;
  va_start(args, format);
#ifdef DEBUG
  vprintf(format, args);
#endif /* ifdef DEBUG */
  va_end(args);
}
