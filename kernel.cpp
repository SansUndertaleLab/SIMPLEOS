long out(char* pos,char* str){
  long index=0;
  char chr=str[0];
  int width = 80;
  long homepointer = 0xb8000;
  while (chr){
    if (chr == '\n'){
      pos += (width-(((long)pos - homepointer) / 2) % width)*2;
    } else {
      *pos=chr;
      pos+=2;
    }
    index++;
    chr=str[index];
  }
  return index*2;
}

void print(long* position, char* msg){
  *position += out((char*)*position, msg);
  return;
}

char getChar(){
  char returnV;
  asm volatile(
    "mov $0, %%ah\n"
    "int $22\n"
    "mov %%al, %0\n"
    "ret"
    : "=r" (returnV)
    :
    : "%eax"
  );
  return returnV;
}

extern "C" void main(){
  long position = 0xb8000;
  char str = getChar();
  return;
}
