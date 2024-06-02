#ifndef DISK_H
#define DISK_H

#include "fat_table.h"
#include "virtual_disk.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BLOCK_SIZE 1024

#ifndef FAT_SIZE
#define FAT_SIZE 4
#endif

#ifndef DISK_SIZE
#define DISK_SIZE 1024
#endif

#ifndef DISK_PATH
#define DISK_PATH "Disk.txt"
#endif

#endif // !DISK_H
