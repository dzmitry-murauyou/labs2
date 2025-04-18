#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_EXPRESSION_LENGTH 1000
#define MAX_STACK_SIZE 100
#define MAX_NUM_LENGTH 20

typedef struct
{
    double data[MAX_STACK_SIZE];
    int top;
} Stack;

void initStack(Stack* stack)
{
    stack->top = -1;
}

int isEmpty(Stack* stack)
{
    return stack->top == -1;
}

int isFull(Stack* stack) {
    return stack->top == MAX_STACK_SIZE - 1;
}

void push(Stack* stack, double value)
{
    if (isFull(stack))
    {
        printf_s("Stack overflow!\n");
        return;
    }
    stack->data[++stack->top] = value;
}

double pop(Stack* stack)
{
    if (isEmpty(stack))
    {
        printf_s("Stack underflow!\n");
        return 0;
    }
    return stack->data[stack->top--];
}

int precedence(char op)
{
    if (op == '+' || op == '-')
    {
        return 1;
    }
    else if (op == '*' || op == '/')
    {
        return 2;
    }
    else
    {
        return 0;
    }
}

char* myStrncpy(char* bufer, const char* string, int numCopy)
{
    if (bufer == NULL || string == NULL) 
        return NULL;
    int i = 0;
    while (i < numCopy && string[i] != '\0')
    {
        bufer[i] = string[i];
        i++;
    }
    while (i < numCopy)
    {
        bufer[i] = '\0';
        i++;
    }
    return bufer;
}

char* myStrtok(char* str, const char* delim, char** context) {
    if (str != NULL) {
        *context = str;
    }
    if (*context == NULL) {
        return NULL;
    }
    char* token = *context;
    *context = strstr(*context, delim);
    if (*context != NULL) {
        **context = '\0';
        *context += strlen(delim);
    }
    else {
        *context = NULL;
    }
    return token;
}

char* toRPN(char* infix, int* errorPosition) {
    Stack operatorStack;
    initStack(&operatorStack);
    char* rpn = (char*)malloc(MAX_EXPRESSION_LENGTH * sizeof(char));
    if (rpn == NULL) 
    {
        return NULL;
    }
    int rpnIndex = 0;
    int i = 0;
    char currentNum[MAX_NUM_LENGTH] = { 0 };
    int numIndex = 0;

    while (infix[i] != '\0') 
    {
        if (isdigit(infix[i]) || (infix[i] == '.' && isdigit(infix[i - 1])) || (infix[i] == ',' && isdigit(infix[i - 1])))
        {
            currentNum[numIndex++] = infix[i];
        }
        else 
        {
            if (numIndex > 0) 
            {
                currentNum[numIndex] = '\0';
                myStrncpy(rpn + rpnIndex, currentNum, MAX_EXPRESSION_LENGTH - rpnIndex);
                rpnIndex += strlen(currentNum);
                rpn[rpnIndex++] = ' ';
                numIndex = 0;
            }
            if (infix[i] == '(') {
                push(&operatorStack, '(');
            }
            else if (infix[i] == ')') 
            {
                while (!isEmpty(&operatorStack) && operatorStack.data[operatorStack.top] != '(') 
                {
                    rpn[rpnIndex++] = pop(&operatorStack);
                    rpn[rpnIndex++] = ' ';
                }
                if (isEmpty(&operatorStack)) 
                {
                    *errorPosition = i;
                    free(rpn);
                    return NULL;
                }
                pop(&operatorStack);
            }
            else if (strchr("+-*/", infix[i]) != NULL) 
            {
                while (!isEmpty(&operatorStack) && precedence(infix[i]) <= precedence(operatorStack.data[operatorStack.top])) 
                {
                    rpn[rpnIndex++] = pop(&operatorStack);
                    rpn[rpnIndex++] = ' ';
                }
                push(&operatorStack, infix[i]);
            }
            else if (!isspace(infix[i]))
            {
                *errorPosition = i;
                free(rpn);
                return NULL;
            }
        }
        i++;
    }

    if (numIndex > 0) 
    {
        currentNum[numIndex] = '\0';
        myStrncpy(rpn + rpnIndex, currentNum, MAX_EXPRESSION_LENGTH - rpnIndex);
        rpnIndex += strlen(currentNum);
        rpn[rpnIndex++] = ' ';
    }

    while (!isEmpty(&operatorStack)) 
    {
        if (operatorStack.data[operatorStack.top] == '(') {
            *errorPosition = i;
            free(rpn);
            return NULL;
        }
        rpn[rpnIndex++] = pop(&operatorStack);
        rpn[rpnIndex++] = '0';
    }
    rpn[rpnIndex - 1] = '\0';

    return rpn;
}

double calculateRPN(char* rpn)
{
    char* context = NULL;
    char* token;
    Stack operandStack;
    initStack(&operandStack);

    token = myStrtok(rpn, " ", &context);
    while (token != NULL) {
        if (isdigit(token[0]) || (token[0] == '-' && isdigit(token[1])))
        {
            push(&operandStack, atof(token));
        }
        else
        {
            if (isEmpty(&operandStack))
            {
                return 0;
            }
            double op2 = pop(&operandStack);
            if (isEmpty(&operandStack))
            {
                return 0;
            }
            double op1 = pop(&operandStack);
            if (strcmp(token, "+") == 0) push(&operandStack, op1 + op2);
            else if (strcmp(token, "-") == 0) push(&operandStack, op1 - op2);
            else if (strcmp(token, "*") == 0) push(&operandStack, op1 * op2);
            else if (strcmp(token, "/") == 0)
            {
                if (op2 == 0)
                {
                    printf_s("Division by zero!\n");
                    return 0;
                    push(&operandStack, op1 / op2);
                }
                else
                {
                    printf_s("Invalid operator: %s\n", token);
                    return 0;
                }
            }
            token = myStrtok(NULL, " ", &context);
        }
        return pop(&operandStack);
    }

}
