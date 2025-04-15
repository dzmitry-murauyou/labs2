#include "Functions.h"


int sumAfterLastMin(struct myStack* stack) 
{
    if (!stack) 
        return 0;
    int minValue = INT_MAX, sum = 0;
    struct myStack* current = stack;
    struct myStack* lastMinNode = NULL;
    while (current != NULL) 
    {
        if (current->info < minValue) {
            minValue = current->info;
            lastMinNode = current;
        }
        current = current->next;
    }
    if (!lastMinNode) return 0;
    current = lastMinNode->next;
    while (current != NULL) {
        sum += current->info;
        current = current->next;
    }

    return sum;
}

int sumAfterMinReversed(struct myStack* stack, int minValue, int* foundMin) {
    if (!stack) {
        return 0;
    }
    int sum = sumAfterMinReversed(stack->next, minValue, foundMin);
    if (*foundMin) {
        sum += stack->info;
    }
    if (stack->info == minValue) {
        *foundMin = 1;
    }

    return sum;
}

int calculateSumAfterMinInReversedStack(struct myStack* stack) {
    if (!stack) return 0;

    int minValue = INT_MAX;
    struct myStack* current = stack;
    while (current != NULL) {
        if (current->info < minValue) {
            minValue = current->info;
        }
        current = current->next;
    }

    int foundMin = 0;
    return sumAfterMinReversed(stack, minValue, &foundMin);
}

void work() 
{
    struct myStack* top = NULL;
    int numberOfElements, value;
    printf("Enter max number of stack elements: ");
    numberOfElements = input(1000000, 1);
    printf("If you want to stop, enter 's'\n");
    for (int i = 0; i < numberOfElements; i++) 
    {
        printf("Enter element %d - ", i + 1);
        value = input(INT_MAX - 1, INT_MIN + 1);
        if (value == INT_MIN) 
        {
            break;
        }
        top = push(top, value);
    }
    printStack(top);
    int sum = sumAfterLastMin(top);
    printf("Sum of elements after the last minimum: %d\n", sum);
    int sumReversed = calculateSumAfterMinInReversedStack(top);
    printf("Sum of elements after the last minimum in reversed stack: %d\n", sumReversed);
    struct myStack* current = top;
    while (current != NULL) 
    {
        struct myStack* temp = current;
        current = current->next;
        free(temp);
    }
}

int main() 
{
    work();
    return 0;
} 