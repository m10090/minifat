#ifndef FILE_H
#define FILE_H

#include "dir.h"
#include "item.h"
#include <stdio.h>
#include <string.h>

static int min(const int a, const int b);

// expand the path to the full path if it contains ~
// buffer should be filed with \0 and 100 byte size
static void expand_path(const char *path, char *buffer);

// import the file from the real disk to the virtual disk takes the filepath
int import_files(const char *filepath);

// export the file from virtual disk to the real disk
int export_files(const char *name);

// read the file and return the buffer `need to free the buffer`
char *read_file(const int first_cluster);

// add the buffer into the virtual disk
void import_buffer(const char *buffer, const int file_size, const char *name);

#endif
