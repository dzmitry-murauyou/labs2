#include "Functions.h"

int main() 
{
    char expression[MAX_EXPRESSION_LENGTH];
    char* rpn;
    double result;
    int errorPosition;
    FILE *inputFile, *outputFile;
    if (fopen_s(&inputFile, "input.txt", "r") != 0) 
    {
        return 1;
    }
    if (fopen_s(&outputFile, "output.txt", "w") != 0) 
    {
        return 1;
    }

    while (fgets(expression, MAX_EXPRESSION_LENGTH, inputFile) != NULL) 
    {
        expression[strcspn(expression, "\n")] = 0;
        printf_s("Processing expression: %s\n", expression);
        rpn = toRPN(expression, &errorPosition);
        if (rpn == NULL) 
        {
            fprintf(outputFile, "Error in expression: '%s' at position %d\n", expression, errorPosition + 1);
            continue;
        }
        else 
        {
            result = calculateRPN(rpn);
            fprintf(outputFile, "%s = %lf\n", expression, result);
            free(rpn);
        }
    }
    fclose(inputFile);
    fclose(outputFile);
    return 0;
}