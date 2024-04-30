#include "files.h" // this is for linter
#include <stdio.h>
#include <string.h>
int min(int a, int b) { return (a > b) ? b : a; }
int import_files(char *name) {
  FILE *file;
  if (file_search(name) != -1) {
    printf("File already exists rename it or deleted it \n");
    return 1;
  }
  file = fopen(name, "r+b");
  if (file == NULL) {
    printf("File not found\n");
    return 1;
  }
  fseek(file, 0l, SEEK_END);
  long int file_size = ftell(file);
  printf("file size %ld\n", file_size);
  fseek(file, 0l, SEEK_SET);
  int nc = 0;
  int np = get_free_block();
  int start_block = np;
  for (int i = 0; i < file_size; i += BLOCK_SIZE) {
    char buffer[BLOCK_SIZE];
    memset(buffer, 0, BLOCK_SIZE);
    fseek(file, i, SEEK_SET);
    fread(buffer, 1, min(BLOCK_SIZE, file_size - i), file);
#ifdef DEBUG
    printf("buffer %s\n", buffer);
#endif /* DEBUG */
    write_block(buffer, np);
    if (nc != 0) {
      set_value(nc, np);
    } else {
      set_value(np, -1); // this is temp fix for the first block
    }
    nc = np;
    np = get_free_block(); // if got and not used it will not be written in the
                           // fat table
  }
  Item to_add = (Item){.name = "",
                       .empty = {0},
                       .attribute = 1,
                       .size = file_size,
                       .frist_cluster = start_block};
  strcpy(to_add.name, name);
  set_value(nc, -1);
  add_to_dir(to_add);
  write_dir();
  return 0;
}
int export_files(char *name) {
  FILE *file;
  int file_idx = file_search(name);
  if (file_idx == -1) {
    printf("File not found\n");
    return 1;
  }
  file = fopen(name, "r+b");
  const Item *childrens = current_dir->dir_list.childrens;
  const int frist_cluster = childrens[file_idx].frist_cluster;
  const int file_size = childrens[file_idx].size;
  char *buffer = read_file(frist_cluster);
#ifdef DEBUG
  printf("frist cluster of file %d\n", frist_cluster);
  printf("file size %d\n", file_size);
  printf("buffer %s\n", buffer);
#endif /* DEBUG */
  fwrite(buffer, 1, file_size, file);
  free(buffer);
  return 0;
}

// read the file gets memory from heap
char *read_file(int frist_cluster) {
  int np = frist_cluster;
  char *result = NULL;
  int result_size = 0;
  while (np != -1) {
    result = realloc(result, result_size + BLOCK_SIZE);
    char *buffer = read_block(np);
    memcpy(result + result_size, buffer, BLOCK_SIZE);
    free(buffer);
    result_size += BLOCK_SIZE;
    np = get_fat_value(np);
  }
  return result;
}
int import_buffer(char *buffer, int file_size, char *name) {
  int nc = 0;
  int np = get_free_block();
  int start_block = np;
  for (int i = 0; i < file_size; i += BLOCK_SIZE) {
#ifdef DEBUG
    printf("buffer %s\n", buffer);
#endif /* DEBUG */
    write_block(buffer + i, np);
    if (nc != 0) {
      set_value(nc, np);
    } else {
      set_value(np, -1);
    }
    nc = np;
    np = get_free_block(); // if got and not used it will not be written in the
                           // fat table
  }
  Item to_add = (Item){.name = "",
                       .empty = {0},
                       .attribute = 1,
                       .size = file_size,
                       .frist_cluster = start_block};
  // 
  stpncpy(to_add.name, name,10);
  set_value(nc, -1);
  add_to_dir(to_add);
  write_dir();
  return 0;
}
