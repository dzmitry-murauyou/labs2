#include <stdio.h>
#include <stdlib.h>

struct myStack 
{
    int info;
    struct myStack* next;
};

int inputCheck(char* value, int LIMIT, int LIMIT_LOW) 
{
    int i = 0, number = 0, isNegative = 0;
    if (value[0] == '-') 
    {
        isNegative = 1;
        i++;
    }
    for (; value[i] != '\0'; i++) 
    {
        if (value[i] < '0' || value[i] > '9') 
        {
            printf_s("Error: Invalid characters have been entered.\n");
            return INT_MAX;
        }
        int digit = value[i] - '0';
        number = number * 10 + digit;
    }
    if (isNegative) 
    {
        number = -number;
    }
    if (number < LIMIT_LOW || number > LIMIT) 
    {
        printf_s("Error: Input is out of bounds.\n");
        return INT_MAX;
    }
    return number;
}

int input(int LIMIT, int LOWER_INPUT, int previous) 
{
    char* value;
    int isCorrect = 0;
    while (isCorrect == 0) 
    {
        value = (char*)calloc(12, sizeof(char));
        if (!value) 
        {
            return INT_MAX;
        }
        printf_s("Enter a value: ");
        scanf_s("%s",  value, 12);
        if (value[0] == 's' && value[1] == '\0') 
        {
            free(value);
            return INT_MIN;
        }
        if (getchar() != '\n') 
        {
            printf_s("Error: too many elements in the row or there are spaces.\n");
            while (getchar() != '\n');
            free(value);
            value = NULL;
            continue;
        }
        int inputValue = inputCheck(value, LIMIT, LOWER_INPUT);
        if (inputValue != INT_MAX) 
        {
            if (inputValue >= previous) 
            {
                isCorrect = 1;
                free(value);
                return inputValue;
            }
            else 
            {
                printf_s("Please enter a number greater than or equal to %d\n", previous);
            }
        }
        free(value);
    }
    return INT_MAX;
}
struct myStack* createElement(int value)
{
    struct myStack* newNode = (struct myStack*)malloc(sizeof(struct myStack));
    if (!newNode) 
    {
        return NULL;
    }
    newNode->info = value;
    newNode->next = NULL;
    return newNode;
}

struct myStack* push(struct myStack* top, int value) 
{
    struct myStack* newElement = createElement(value);
    if (!newElement) 
    {
        return top;
    }
    newElement->next = top;
    return newElement;
}

void printStack(struct myStack* top) 
{
    if (!top) return;
    struct myStack* current = top;
    printf_s("Stack elements:\n");
    while (current != NULL) 
    {
        printf_s("%d\n", current->info);
        current = current->next;
    }
}

int pop(struct myStack** top) 
{
    if (*top == NULL) return INT_MIN;
    struct myStack* temp = *top;
    int value = temp->info;
    *top = (*top)->next;
    free(temp);
    return value;
}

struct myStack* insertSorted(struct myStack* top, int value)
{
    struct myStack* newNode = createElement(value);
    if (!newNode) return top;
    if (top == NULL || top->info >= value) 
    {
        newNode->next = top;
        return newNode;
    }
    struct myStack* current = top;
    while (current->next != NULL && current->next->info < value)
    {
        current = current->next;
    }
    newNode->next = current->next;
    current->next = newNode;
    return top;
}