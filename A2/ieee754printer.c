#include <stdio.h>

typedef union{
    float f;

    struct{
        unsigned char uchar0:8; // bits 0-7
        unsigned char uchar1:8; // bits 8-15
        unsigned char uchar2:8; // bits 16-23
        unsigned char uchar3:8; // bits 24-31
    };
} ieee754_info_t; 

void printIEEE754(ieee754_info_t *info){

}

int main(void){
    ieee754_info_t val;
    while(1){
        printf("Enter a floating point number: ");
        scanf("%f",&val.f);
        printf("char0 = %X\n", val.uchar0);
        printf("char1 = %X\n", val.uchar1);
        printf("char2 = %X\n", val.uchar2);
        printf("char3 = %X\n", val.uchar3);
    }
    return(0);
}

