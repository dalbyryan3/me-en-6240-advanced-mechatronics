#include <stdio.h>
int main(void) {
	unsigned char i = 60, j = 80, k=200, sumu;
	sumu = i+j;
	printf("unsigned char: %d + %d = %3d or ASCII %c\n",i,j,sumu,sumu);
	sumu = i+k;
	printf("unsigned char: %d + %d = %3d or ASCII %c\n",i,k,sumu,sumu);
	sumu = j+k;
	printf("unsigned char: %d + %d = %3d or ASCII %c\n",j,k,sumu,sumu);
	return 0;
}
