#ifndef FILE_H
#define FILE_H
#include "dir.h"
#include "item.h"
#include <stdio.h>
#include <string.h>
int min(const int a,const  int b);
int import_files(const char *name);
int export_files(const char *name);
char *read_file(const int first_cluster);
void import_buffer(const char *buffer,const int file_size, const char *name);
#endif
