#include <stdlib.h>
#include <limits.h>
const int CHECK_DECIMAL = 10;

int inputCheck(char* value, int LIMIT, int LIMIT_LOW) {
    int i = 0, number = 0, sign=1;
    if (value[0] == '-') {
        sign = -1;
        i = 1;
    }
    else if (value[0] == '+') {
        i = 1;
    }
    for (; value[i] != '\0'; i++) {
        if (value[i] < '0' || value[i] > '9') {
            printf("Error: Invalid characters have been entered.\n");
            return INT_MAX;
        }
        int digit = value[i] - '0';
        number = number * 10 + digit;
        
    }
    if (number < LIMIT_LOW || number > LIMIT) {
        printf("Error: Input is out of bounds.\n");
        return INT_MAX;
    }
    number *= sign;
    return number;
}

int input(int LIMIT, int LOWER_INPUT) {
    char* value;
    int isCorrect = 0;
    while (isCorrect == 0) {
        value = (char*)calloc(12, sizeof(char));
        if (!value) {
            printf("Memory allocation failed.\n");
            return INT_MAX;
        }
        scanf_s("%s", value, 12);
        if (getchar() != '\n') {
            printf("Error: there are too many elements in the row, or there are spaces\n");
            while (getchar() != '\n');
            free(value);
            value = NULL;
        }
        else if (inputCheck(value, LIMIT, LOWER_INPUT) != INT_MAX) {
            isCorrect = 1;
        }
        else {
            printf("Please, again\n");
            free(value);
            value = NULL;
        }
    }
    int result = inputCheck(value, LIMIT, LOWER_INPUT);
    free(value);
    return result;
}

void findMaxNumber(FILE* f, int number) {
    int buferMax = INT_MIN; 
    int bufer;
    int count = 0;
    rewind(f);
    fscanf_s(f, "%d", &bufer);
    for (int i = 0; i < number; i++) 
    {
        if (fscanf_s(f, "%d", &bufer) != 1) 
        {
            return;
        }
        if (bufer > buferMax) 
        {
            buferMax = bufer;
            count = 1;
        }
        else if (bufer == buferMax) 
        {
            count++;
        }
    }
    if (count > 0) 
    {
        printf("Max number is %d, found %d times.\n", buferMax, count);
    }
}

void reverseNumber(FILE* f,int number) 
{
    int numberToReverse, flip = 0;
    int reversed = 0;
    printf("Enter the index of the number you want to reverse: \n");
    numberToReverse = input(number, 1);
    rewind(f);
    for (int i = 0; i < numberToReverse+1; i++)
    {
        fscanf_s(f, "%d", &flip);
    }
    while (flip != 0) {
        reversed = reversed * CHECK_DECIMAL + flip % CHECK_DECIMAL;
        flip /= CHECK_DECIMAL;
    }
    printf_s("Reversed number: %d\n", reversed);
}