#include "../items/item.h"
int md();
int rd();
int cd(char *paths);
int dir(char *paths);
int movDir(char *name, char *path);
int renameFile(char *filename, char *newName);
int deleteFile(char *name);
int catFile(char *name);
int copyFile(char *name, char *copyPath);
void help(void);
