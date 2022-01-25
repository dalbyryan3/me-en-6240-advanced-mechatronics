#include <stdio.h>      

int main(){
  printf("ASCII Table\n\n");
  printf("Number\tCharacter\n");

  for (unsigned char i = 33; i <= 127; i++){
    printf("%d\t%c\n",i,i);
  }

  return (0);
}
