#include "Functions.h"

int main() 
{
    struct myStack* top1 = NULL;
    struct myStack* top2 = NULL;
    struct myStack* topRes = NULL;
    int numberOfElements1, numberOfElements2, value, temp = INT_MIN;
    printf_s("Enter max number of stack elements for Stack 1: ");
    numberOfElements1 = input(1000000, 1, INT_MIN);
    printf_s("If you want to stop, enter 's'\n");
    for (int i = 0; i < numberOfElements1; i++) {
        printf_s("Enter element %d - ", i + 1);
        value = input(INT_MAX - 1, INT_MIN + 1, temp);
        if (value == INT_MIN) {
            break;
        }
        top1 = push(top1, value);
        temp = value;
    }
    temp = INT_MIN;
    printf_s("Enter max number of stack elements for Stack 2: ");
    numberOfElements2 = input(1000000, 1, INT_MIN);
    printf_s("If you want to stop, enter 's'\n");
    for (int i = 0; i < numberOfElements2; i++) {
        printf_s("Enter element %d - ", i + 1);
        value = input(INT_MAX - 1, INT_MIN + 1, temp);
        if (value == INT_MIN) {
            break;
        }
        top2 = push(top2, value);
        temp = value;
    }
    printStack(top1);
    printStack(top2);
    while (top1 != NULL) {
        topRes = insertSorted(topRes, pop(&top1));
    }
    while (top2 != NULL) {
        topRes = insertSorted(topRes, pop(&top2));
    }
    printf_s("Resulting sorted stack:\n");
    printStack(topRes);
    return 0;
}