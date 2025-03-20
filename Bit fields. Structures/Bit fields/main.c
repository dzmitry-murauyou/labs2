/*Найти и вывести 2 старших бита беззнакового числа.*/
/**/
#include <stdio.h>
#include "Functions.h"

union code 
{
    struct 
    {
        unsigned int a30 : 1;
        unsigned int a31 : 1;
        unsigned int : 30;
    } bits;
    unsigned int value;
};

int main(void) {
    union code c;
    printf_s("Enter 32 bit number: ");
    scanf_s("%u", &c.value);
    printf_s("2 most significant bits: %u %u\n", c.bits.a31, c.bits.a30);
    return 0;
}