#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "run.c"
#include "cli.h"


int main() {
    char command[MAX_COMMAND_LENGTH];

    while (1) {
        printf("Enter a command (type 'exit' to quit): ");
        fgets(command, sizeof(command), stdin);

        // Remove trailing newline character
        command[strcspn(command, "\n")] = 0;

        runCommand(command);
        memset(command, 0, sizeof(command));
    }

    return 0;
}
