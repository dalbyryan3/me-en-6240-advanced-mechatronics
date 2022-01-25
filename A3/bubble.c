#include <stdio.h>
#include <string.h>
#define MAXLENGTH 100       // max length of string input

void getString(char *str);  // helper prototypes
void printResult(char *str);
int greaterThan(char ch1, char ch2);
void swap(char *str, int index1, int index2);

int main(void) {
  int len;                  // length of the entered string
  char str[MAXLENGTH];      // input should be no longer than MAXLENGTH
  // here, any other variables you need

  getString(str);
  len = strlen(str);        // get length of the string, from string.h

  // put nested loops here to put the string in sorted order
  
  for (int n=len; n>1; n--){
    for (int i=0; i<(n-1); i++){
      if (greaterThan(str[i],str[i+1])){
        swap(str,i,i+1);
      }
    }
  }

  printResult(str);

  // Testing of helper functions:
  /* int len;                  // length of the entered string */
  /* char str[MAXLENGTH];      // input should be no longer than MAXLENGTH */
  /* // here, any other variables you need */

  /* getString(str); */
  /* len = strlen(str);        // get length of the string, from string.h */

  /* // Test printResult and getString, should output what was typed (will assume input has no spaces) */
  /* printResult(str); */
    /* // Test greaterThan */
  /* printf("B greater than A?(Should be True or (1)): %d\n",greaterThan('B','A')); */ 
  /* printf("A greater than B?(Should be False(0)): %d\n",greaterThan('A','B')); */ 
  /* // Test swap */
  /* char swapTestStr[MAXLENGTH] = "abcdef"; */
  /* printf("Original swap test string: %s    ", swapTestStr); */
  /* swap(swapTestStr, 1,3); */
  /* printf("Final swap test string (should be adcbef): %s", swapTestStr); */

  return(0);
}

// helper functions go here
void getString(char *str){
  scanf("%s", str);
}
void printResult(char *str){
  printf("%s\n", str);
}
int greaterThan(char ch1, char ch2){
  return (ch1 > ch2);
}
void swap(char *str, int index1, int index2){
  char tmp = str[index2];
  str[index2] = str[index1];
  str[index1] = tmp;
}
