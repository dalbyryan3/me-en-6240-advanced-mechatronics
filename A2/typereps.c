#include <stdio.h>

typedef union {         // a new data type consisting of four bytes
    unsigned int u;     // the 32 bits interpreted as an unsigned int
    int i;              // the same 32 bits interpreted as a two’s complement int
    float f;            // the same 32 bits interpreted as an IEEE 754 single prec float
    struct {
        char char0:8;   // bits 0 - 7 interpreted as char, called char0    
        char char1:8;   // bits 8 - 15 interpreted as char, called char1
        char char2:8;   // bits 16 - 23 interpreted as char, called char2
        char char3:8;   // bits 24 - 31 interpreted as char, called char3
		/* : It's a bitfield. It's only valid in a struct definition, and it means that 
		 * the system will only use 8 bits for your char.
		 */
    };
    } four_types_t; // the new type is called four_types_t


/* A union is a special data type available in C that allows storing different data types
 * in the same memory location. You can define a union with many members, but only one member 
 * can contain a value at any given time. Unions provide an efficient way of using the same 
 * memory location for multiple-purpose.
 */


int main(void) {
    four_types_t val;
    while (1) { 			// exit the infinite loop using ctrl-c or similar see pag 561 for while loop
        printf("Enter four bytes as eight hex characters 0-f, e.g., abcd0123: ");
        scanf("%x",&val.u);	// see pag 563-564 for scanf
		printf("\nThe 32 bits in hex: %x\n",val.u);
        printf("The 32 bits as an unsigned int, in decimal: %u\n",val.u);
        printf("The 32 bits as a signed int, in decimal: %d\n",val.i);
        printf("The 32 bits as a float: %.20f\n",val.f);
        printf("The 32 bits as 4 chars: %c %c %c %c\n\n",
        val.char3, val.char2, val.char1, val.char0);
    }
    return 0;
}
