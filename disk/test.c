#include "disk.h"
int main () {
  init_disk();
  printf("Disk initialized\n");
  print_fat_table();

  return 0;
}
