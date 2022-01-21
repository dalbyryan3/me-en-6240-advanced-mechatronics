#include <stdio.h>

int main(void) {
  int a=2, b=3, c; float d=1.0, e=3.5, f;
  f = a/b;
  printf("%f\n",f);
  f = ((float)a)/b;
  printf("%f\n",f);
  f = (float)(a/b);
  printf("%f\n",f);
  c = e/d;
  printf("%d\n",c);
  c = (int)(e/d);
  printf("%d\n",c);
  f = ((int)e)/d;
  printf("%f\n",f);

  return(0);
}
