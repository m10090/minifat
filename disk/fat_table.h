#ifndef FAT_TABLE_H

void init_fat(int file_exists);
void write_fat_table(void);
void read_fat_table(void);

#ifdef DEBUG
  void print_fat_table(void);
#endif /* ifdef DEBUG */
int get_free_block(void);
int get_fat_value(int index);
void set_value(int index, int value);
int get_free_space(void);
#endif // !FAT_TABLE_H
