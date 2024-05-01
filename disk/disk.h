#ifndef DISK_H
#define DISK_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fat_table.h" 
#include "virtual_disk.h"


#define BLOCK_SIZE 1024 



// variables for this module
extern FILE *disk;
// fat table with the useage of each block
extern int fat[BLOCK_SIZE];


#endif // !DISK_H
