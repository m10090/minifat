#ifndef FILE_H
#define FILE_H
#include "dir.h"
#include "item.h"
#include <stdio.h>
#include <string.h>
int min(int a, int b);
int import_files(char *name);
int export_files(char *name);
char *read_file(int first_cluster);
int import_buffer(char *buffer, int file_size, char *name);
#endif
