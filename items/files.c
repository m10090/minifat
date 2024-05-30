#include "files.h" // this is for linter
#include "../cli.h"
#include "dir.h"
#include "item.h"

// as c doesn't have a min function :/
static int min(const int a, const int b) { return (a > b) ? b : a; }

static void expand_path(const char *path, char buffer[100]) {
  // if ~ is found replace it with $HOME
  if (path[0] == '~') {
    const char *homeDir = getenv("HOME");
    if (homeDir != NULL) {
      // 1 for the null terminator
      strncpy(buffer, homeDir, 99);
      if (path[1] != '\0')
        strncat(buffer, path + 1, 99);
    }
    return;
  }
  // else copy the path `1 byte for the null terminator`
  strncat(buffer, path, 99);
  return;
}

int import_files(const char *input) {
  FILE *file;
  if (file_search(input) != -1) {
    printf("File already exists rename it or deleted it \n");
    return 1;
  }
  char filepath[100] = {0};
  expand_path(input, filepath);
  // Overwrite the file if it exists or create it if it does not exist
  file = fopen(filepath, "w+b");
  if (file == NULL) {
    printf("File not found\n");
    return 1;
  }
  // get the file size
  fseek(file, 0, SEEK_END);
  long file_size = ftell(file);
  debug_print("file size %ld\n", file_size);
  fseek(file, 0, SEEK_SET);
  if (file_size > get_free_space()) {
    printf("Not enough space\n");
    return 1;
  }

  int nc = 0;
  int np = get_free_block();
  int start_block = np;
  for (int i = 0; i < file_size; i += BLOCK_SIZE) {
    char buffer[BLOCK_SIZE] = {0};
    fseek(file, i, SEEK_SET);
    fread(buffer, 1,
          // get the min of the bloc size and the remaining size
          min(BLOCK_SIZE, file_size - i), file);
    write_block(buffer, np);
    if (nc != 0) {
      set_value(nc, np);
    } else {
      // this is temp fix for the first block
      set_value(np, -1);
    }
    // if np is take from the fat table it will not be written in the fat table
    nc = np;
    np = get_free_block();
  }
  Item to_add = {.name = "",
                 .empty = {0},
                 .attribute = 1,
                 .size = file_size,
                 .frist_cluster = start_block};
  // get the filename
  char filename[100] = {0};
  char *name_pointer = strrchr(filepath, '/');
  // if the file does not have a / in it
  if (name_pointer == NULL) {
    // 1 for the /
    strncat(filename, "/", 1);
    // 98 for the rest of the name
    strncat(filename, input, 98);
    // 1 for the null terminator
  } else {
    strncpy(filename, name_pointer, 99);
  }

  if (file_search(filename) != -1) {
    printf("File already exists rename it or deleted it \n");
    return 1;
  }
  strncpy(to_add.name, filename + 1, 10);
  set_value(nc, -1);
  add_to_dir(to_add);
  write_dir();
  return 0;
}

int export_files(const char *name) {
  FILE *file;
  // check if the file exists
  int file_idx = file_search(name);
  if (file_idx == -1) {
    printf("File not found\n");
    return 1;
  }
  // w+ vs r+ "this done alot of problems for me" :(
  file = fopen(name, "w+b");

  const Item *childrens = current_dir->dir_list.childrens;
  const int frist_cluster = childrens[file_idx].frist_cluster;
  const int file_size = childrens[file_idx].size;

  char *buffer = read_file(frist_cluster);
  {

    debug_print("frist cluster of file %d\n", frist_cluster);
    debug_print("file size %d\n", file_size);
    debug_print("buffer %s\n", buffer);

    // write the buffer to the file
    fwrite(buffer, 1, file_size, file);
  }
  free(buffer);

  fclose(file);
  return 0;
}

char *read_file(int frist_cluster) {
  int np = frist_cluster;
  char *result = NULL;
  int result_size = 0;
  while (np != -1) {
    result = reallocf(result, result_size + BLOCK_SIZE);
    char *buffer = read_block(np);
    memcpy(result + result_size, buffer, BLOCK_SIZE);
    free(buffer);
    result_size += BLOCK_SIZE;
    np = get_fat_value(np);
  }
  return result;
}

void import_buffer(const char *buffer, const int file_size, const char *name) {
  int nc = 0;
  int np = get_free_block();
  int start_block = np;
  for (int i = 0; i < file_size; i += BLOCK_SIZE) {
    write_block(buffer + i, np);
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

  strncpy(to_add.name, name, 10);
  set_value(nc, -1);
  add_to_dir(to_add);
  write_dir();
}
