#include "../cli.h"

int parseCommand(char *command,int start, int size){
  for (int i = start; i < size; i++) {
    if (command[i] == 0) return i;
    if (command[i] == ' ') {
      return i;
    }
  }
  return -1;
}
// return the start index of the next command in the string 
int nextCommand(char *command, int startIdx, int size){
  for (int i = startIdx+1; i < size; i++) 
    {
    if (command[i] == 0) return -1;
    if (command[i] != ' ') return i; 
  }
    
  return -1;
}
