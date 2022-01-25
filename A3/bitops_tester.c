#include <stdio.h>      

int main(){
  unsigned char a=0x0D, b=0x03, c;
  c = ~a;
  printf("a) %X\n", c);

  c = a & b;
  printf("b) %X\n", c);

  c = a | b;
  printf("c) %X\n", c);

  c = a ^ b;
  printf("d) %X\n", c);

  c = a >> 3;
  printf("e) %X\n", c);

  c = a << 3;
  printf("f) %X\n", c);

  c &= b;
  printf("g) %X\n", c);

  return (0);
}
