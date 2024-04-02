#ifndef FILE_H
#define FILE_H
#include "dir.h"
#include "item.h"
#include <stdio.h>
#include <string.h>
char *read_file(int frist_cluster);
int export_files(char *name);
int import_files(char *name);
int min(int a, int b);
#include "files.c"
#endif
