#ifndef DISK_H
#define DISK_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BLOCK_SIZE 1024 



// variables for this module
extern FILE *disk;
// fat table with the useage of each block
extern int *fat;




#include "virtual_disk.h"
#include "fat_table.h"
#include "virtual_disk.c"
#include "fat_table.c"
#endif // !DISK_H
