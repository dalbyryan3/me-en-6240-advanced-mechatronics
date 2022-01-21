In embedded systems usually concerned about memory resources and computational resources and time.

What a pointer variable is and how is it different from a non-pointer variable
- A pointer is generally an address (whose value itself is defined/constrained by the architecture of the memory)
- A non pointer is just some memory that isn't an address specifically

Differences between interpreted and compiled code 
- Lines can often be blurred between interpreted and compiled code nowdays (think JIT compiling)
- Generally interpreted code is read line-by-line while compiled code is compiled directly to machine code

Indication of way number is written
- 0x before number indicates hex
- 0d before number indicates decimal
- 0b before number indicates binary

Ex:
- 0x1D = 0b 0001 1110 = 0d30

Hex is useful because it is a more readable form of binary 

Registers are locations in the memory of a microcontroller that are "important", and whose value when changed can do important things

Ex:
- Assuming each byte of memory can be addressed by a 16-bit address and every 16-bit address has a corresponding byte in memory. 
How many total bits of memory do you have? 
  - Ans: (2^16) * 8

Ex:
- Let ch be of type char
  - a) the assignment ch = 'k' can be equivalently written using a number, what is it? 
    - Ans: 107
  - b) the number for '5'
    - Ans: 5
  - c) '='
    - Ans: 61
  - d) '?'
    - Ans: 63

Ex:
What is the range of values for (for PIC32)- note the definition of these types is defined by various standards depending on situation and architecture
- unsigned char 
  - 0 to 2^8 -1
- short int
  - -2^15 to 2^15 -1
- double
    - Depends on architecture and standard used

Difference between unsigned and signed integers are how the bits within them are interpreted (usually one bit reserved for some notion of positive/negative)

Chars are generally faster and take less memory than ints but get less range
Floats take up less memory but doubles can give more range and precision
For integer math it is better to use chars (assuming no overflow) than floats since chars can exactly represent an integer

Signed short int are stored in two bytes of memory often using two's complement (makes it so same logical gate can be used for addition and subtraction).
Give 4 digit hex representation of the following two bytes (process goes as convert to binary and use most significant bit to represent the sign, if negative then algorithm goes as flipping the non significant bits of the binary representation and adding 1):
- -10 = 11110110

Ex:
The smallest positive integer that cannot be exactly represented by a four byte IEEE 754 is 2^24 + 1 or 16777217 
Why?
- value = (-1)^s * b * 2^c
- s e_7...e_0 f_23...f_1
- b = 1 + sum_{i=1}^23{f_i 2^{i-24}} call the sum part A
- c = e -127

2^{24} + 1 = 1 * (1 + A) * 2^{24} = 2^{24} + A * 2^{24} = 2^{24} + 2 * 2^{-24}*2^{24}


Invoking gcc... actually intitates four steps, what are they (-save-temps flag with gcc can show each of these files)
1. Preprocessing
    - Cleaning up the source code, .c to .c, preprocessor directives # are executed/filled
2. Compiling
    - From C code to assembly code (.c to .s)
        - A set of commands that can be executed by the processor
3. Assembling
    - From assembly code to object code (.s to .o)
        - Machine level, binary code, relocatable, specific to the processor (at this point the data and instructions are in terms of **relative** addresses, essential indicating "jumping" to another addresses (typically addresses of other libraries or other .o files that aren't combined with current code yet))
4. Linking
    - From object code (one or more files) to **ONE** executable (Linker decides where things actually go in memory)

(Note sometimes the assembly code can be a "smaller" file than the file output from preprocessing since the preprocessing step often puts a lot of information on where to find stuff that is used during compiling)

Ex.
Assuming have 2^8 bytes of RAM so each address is given by a single byte, consider:
```unsigned int i, j, *kp, *np```

Assume linker places 
- i in addresses 0xB0...0xB3
- j in 0xB4...0xB7
- kp in 0xB8
- np in 0xB9

Give contents of addresses 0xB0...0xB9 for each step below (assume little endian, and all addresses initially unknown or random)

- ```the intital conditions all memory contents unknown```
- ```kp = &i;``` sets 0xB8 to 0xB0
- ```j = *kp;``` 
- ```i = 0xAE;``` sets 0xB0 to 0xAE then 0xB1-0xB3 to 0x00
- ```np = kp;``` sets 0xB9 to 0xB0
- ```*np = 0x12;``` sets 0xB0 to 0x12
- ```j = *kp;``` sets 0xB4 to 0x12 then 0xB5-0xB7 to 0x00

Ex.
Consider three unsigned chars i,j, and k with values 60,80,200 respectively. 
Let sum be an unsigned char
- a) ```sum i+j;``` 140
- b) ```sum i+k;``` 4
- c) ```sum j+k;``` 24

Ex. 
```
int a=2, b=3, c; float d=1.0, e=3.5, f;
f = a/b
f = ((float)a)/b;
f = (float)(a/b);
c = e/d;
c = (int)(e/d);
f = ((int)e)/d;
```


a) 0.0
b) 0.66666...
c) 0.0
d) 3 
e) 3
f) 3.0

Ex.
Give the four bytes in hex that represent:
a) 20 as an unsigned int
    - 0b0...0 0001 0100 = 0x00000014
b) -20 as two's complement signed int
    - 0001 0100 -> 1110 1011-> 1110 1100 = 0xEC => 0x FF FF FF EC
    (Think in terms of references to known things)
c) 1.5 as an IEEE 754 float
    - (-1)^s * b * 2^c where b = 1 + sum_{i=1}^23{f_i 2^{i-24}} and c = e-127
    - Set s = 0
    - Thus set e to be 127 in binary (0111 1111) to get c = 0
    - Set f have 23rd bit to 1 since expanding sum of f_i essentially are doing (f_{23} * 1/2^1 + f_{23}*1/2^2 + ...  down to f_1) 
d) 0 as an IEEE 754 float 
    - 