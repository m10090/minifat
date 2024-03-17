int *fat = NULL;
void init_fat(void) {
  fat = (int*)malloc(BLOCK_SIZE*sizeof(int));
  int i;
  for (i = 0; i < BLOCK_SIZE; i++) {
    fat[i] = 0;
  }
  fat[0] = -1;
  fat[1] = 2;
  fat[2] = 3;
  fat[3] = 4;
  fat[4] = -1;
  write_fat_table();
}
void write_fat_table(void){
  if (fat){
  write_block((char*)fat, 1);
  write_block((char*)fat+BLOCK_SIZE, 2);
  write_block((char*)fat+BLOCK_SIZE*2, 3);
  write_block((char*)fat+BLOCK_SIZE*3, 4);
  }
}
void read_fat_table(void){
  if (fat) free(fat);
  fat = (int*)malloc(BLOCK_SIZE*sizeof(int));
  for(int i =1; i <=4 ; i++){
    const char * block = read_block(i);
    for(int j = 0; j < BLOCK_SIZE; j++){
      fat[(i-1)*BLOCK_SIZE+j] = block[j];
    }
    free((void*)block);
  }
}
#ifdef DEBUG
void print_fat_table(void){
  int i;
  printf("[");
  for (i = 0; i < BLOCK_SIZE; i++) {
    printf("%d,", fat[i]);
  }
  printf("]");
}
#endif /* ifdef DEBUG */
int get_free_block(void){
  int i;
  for (i = 0; i < BLOCK_SIZE; i++) {
    if (fat[i] == 0) {
      fat[i] = -1;
      return i;
    }
  }
  return -1;
}
int get_value(int index){
  if (index < 0 || index >= BLOCK_SIZE) return -1;
  return fat[index];
}
void set_value(int index, int value){
  if (index < 0 || index >= BLOCK_SIZE) return;
  fat[index] = value;
}
int get_free_space(void){
  int i;
  int count = 0;
  for (i = 0; i < BLOCK_SIZE; i++) {
    if (fat[i] == 0) {
      count++;
    }
  }
  return count;
}
