#include "../items/item.h"
// create directory(s)
int md();
// remove directory(s)
int rd();
// change directory 
int cd(char *paths);
// show the directory 
int dir(char *paths);
// move the directory location
int mov_dir(char *name, char *path);
// rename file(s)
int rename_file(char *filename, char *newName);
// delete a file
int delete_file(char *name);
// show the file content
int cat_file(char *name);
// copy file to another directory
int copy_file(char *name, char *copyPath);
// show help
void help(void);
