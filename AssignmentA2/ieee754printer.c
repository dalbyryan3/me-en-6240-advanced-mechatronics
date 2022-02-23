#include <stdio.h>

typedef union{
    float f;

    struct{
        unsigned char f1:1;
        unsigned char f2:1;
        unsigned char f3:1;
        unsigned char f4:1;
        unsigned char f5:1;
        unsigned char f6:1;
        unsigned char f7:1;
        unsigned char f8:1;
        unsigned char f9:1;
        unsigned char f10:1;
        unsigned char f11:1;
        unsigned char f12:1;
        unsigned char f13:1;
        unsigned char f14:1;
        unsigned char f15:1;
        unsigned char f16:1;
        unsigned char f17:1;
        unsigned char f18:1;
        unsigned char f19:1;
        unsigned char f20:1;
        unsigned char f21:1;
        unsigned char f22:1;
        unsigned char f23:1;
        unsigned char e0:1;
        unsigned char e1:1;
        unsigned char e2:1;
        unsigned char e3:1;
        unsigned char e4:1;
        unsigned char e5:1;
        unsigned char e6:1;
        unsigned char e7:1;
        unsigned char s0:1;
    };
} ieee754_info_t; 

void printIEEE754(ieee754_info_t *info){
    printf("s = %u\n", info->s0);
    printf("e = %u", info->e7);
    printf("%u", info->e6);
    printf("%u", info->e5);
    printf("%u", info->e4);
    printf("%u", info->e3);
    printf("%u", info->e2);
    printf("%u", info->e1);
    printf("%u\n", info->e0);
    printf("f = %u", info->f23);
    printf("%u", info->f22);
    printf("%u", info->f21);
    printf("%u", info->f20);
    printf("%u", info->f19);
    printf("%u", info->f18);
    printf("%u", info->f17);
    printf("%u", info->f16);
    printf("%u", info->f15);
    printf("%u", info->f14);
    printf("%u", info->f13);
    printf("%u", info->f12);
    printf("%u", info->f11);
    printf("%u", info->f10);
    printf("%u", info->f9);
    printf("%u", info->f8);
    printf("%u", info->f7);
    printf("%u", info->f6);
    printf("%u", info->f5);
    printf("%u", info->f4);
    printf("%u", info->f3);
    printf("%u", info->f2);
    printf("%u\n", info->f1);
}

int main(void){
    ieee754_info_t val;
    while(1){
        printf("Enter a floating point number: ");
        scanf("%f",&val.f);
        printIEEE754(&val);
    }
    return(0);
}

