void init_fat(int file_exists);
void write_fat_table(void);
void read_fat_table(void);
int get_available_block(void);
int get_value(int block);
void set_value(int block, int value);
int get_number_of_free_blocks(void);
int get_free_space(void);



#ifdef DEBUG
void print_fat_table(void);
#endif // DEBUG




