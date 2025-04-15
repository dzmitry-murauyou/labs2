#include <stdlib.h>
#include <stdio.h>

struct myStack { 
    int info;
    struct myStack* next;
};

int inputCheck(char* value, int LIMIT, int LIMIT_LOW)
{
    int i = 0, number = 0;
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
    if (number < LIMIT_LOW || number > LIMIT)
    {
        printf_s("Error: Input is out of bounds.\n");
        return INT_MAX;
    }
    return number;
}

int input(int LIMIT, int LOWER_INPUT)
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
        scanf_s("%s", value, 12);
        if (value[0] == 's' && value[1] == '\0' && LIMIT == INT_MAX-1 && LOWER_INPUT == INT_MIN+1)
        {
            return INT_MIN;
        }
        if (getchar() != '\n')
        {
            printf_s("Error: there are too many elements in the row, or there are spaces\n");
            while (getchar() != '\n');
            free(value);
            value = NULL;
        }
        else if (inputCheck(value, LIMIT, LOWER_INPUT) != INT_MAX)
        {
            isCorrect = 1;
        }
        else
        {
            printf_s("Please, again\n");
            free(value);
            value = NULL;
        }
    }
    int result = inputCheck(value, LIMIT, LOWER_INPUT);
    free(value);
    return result;
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
    printf("Stack elements:\n");
    while (current != NULL)
    {
        printf("%d\n", current->info);
        current = current->next;
    }
}