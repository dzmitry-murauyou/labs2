#include <stdio.h>
#include <stdlib.h>

struct extraInfo 
{
    char hiredate[11];
    double salary;
};

struct employee 
{
    int cipher;
    char* surName;
    struct extraInfo howSkilled;
};

int mystrcmp(const char* str1, const char* str2) 
{
    while (*str1 != '\0' && *str2 != '\0') 
    {
        if (*str1 != *str2) 
        {
            return *str1 - *str2;
        }
        str1++;
        str2++;
    }
    return *str1 - *str2;
}

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
            printf_s("Memory allocation failed.\n");
            return INT_MAX;
        }
        scanf_s("%s", value, 12);
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

void inputStructure(int number, struct employee* p) 
{
    int i;
    for (i = 0; i < number; i++) 
    {
        int length = 0, ch;
        printf_s("Enter the cipher of employee %d - ", i + 1);
        p[i].cipher = input(INT_MAX, 0);
        p[i].surName = NULL;
        
        printf_s("Enter the surname of employee %d - ", i + 1);
        while ((ch = getchar()) != '\n') 
        {
            char* temp = realloc(p[i].surName, (length + 1) * sizeof(char));
            if (temp == NULL) 
            {
                free(p[i].surName);
                return;
            }
            p[i].surName = temp;
            p[i].surName[length++] = ch;
        }
        char* temp = realloc(p[i].surName, (length + 1) * sizeof(char));
        if (temp == NULL) 
        {
            free(p[i].surName);
            return;
        }
        p[i].surName = temp;
        p[i].surName[length] = '\0';
        while (1) 
        {
            printf_s("Enter the date of hire for employee %d in format dd.mm.yyyy - ", i + 1);
            scanf_s("%s", p[i].howSkilled.hiredate, 11);
            int validLength = 1;
            for (int j = 0; j < 10; j++) 
            {
                if (p[i].howSkilled.hiredate[j] == '\0') 
                {
                    if (j < 10) 
                    {
                        validLength = 0;
                    }
                    break;
                }
            }
            if (!validLength) 
            {
                printf_s("Invalid date.\n");
                continue;
            }
            int validFormat = 1;
            for (int j = 0; j < 10; j++) 
            {
                if (j == 2 || j == 5) 
                {
                    if (p[i].howSkilled.hiredate[j] != '.') 
                    {
                        validFormat = 0;
                        break;
                    }
                }
                else 
                {
                    if (p[i].howSkilled.hiredate[j] < '0' || p[i].howSkilled.hiredate[j] > '9') 
                    {
                        validFormat = 0;
                        break;
                    }
                }
            }

            if (validFormat) 
            {
                int day = (p[i].howSkilled.hiredate[0] - '0') * 10 + (p[i].howSkilled.hiredate[1] - '0');
                int month = (p[i].howSkilled.hiredate[3] - '0') * 10 + (p[i].howSkilled.hiredate[4] - '0');
                int year = (p[i].howSkilled.hiredate[6] - '0') * 1000 + (p[i].howSkilled.hiredate[7] - '0') * 100 +
                    (p[i].howSkilled.hiredate[8] - '0') * 10 + (p[i].howSkilled.hiredate[9] - '0');
                if (month < 1 || month > 12 || day < 1 || day > 31) 
                {
                    validFormat = 0;
                    printf_s("Invalid date.\n");
                }
                else 
                {
                    if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30) 
                    {
                        validFormat = 0;
                        printf_s("Invalid date.\n");
                    }
                    else if (month == 2) 
                    {
                        if (day > 29 || (day == 29 && (year % 4 != 0))) 
                        {
                            validFormat = 0;
                            printf_s("Invalid date.\n");
                        }
                    }
                }
            }

            if (validFormat) 
            {
                break;
            }
            else 
            {
                printf_s("Please enter the date again.\n");
            }
        }

        while (1) 
        {
            printf_s("Enter the salary of employee %d - ", i + 1);
            if (scanf_s("%lf", &p[i].howSkilled.salary) != 0 && getchar() == '\n') {
                break;
            }
            else 
            {
                while (getchar() != '\n');
                printf_s("Error. Please enter a valid salary.\n");
            }
        }
    }
}

void outputStructure(int number, struct employee* p)
{
    int i;
    printf_s("\n");
    printf_s("The structure is\n\n");
    for (i = 0; i < number; i++)
    {
        printf_s("Cipher of employee %d  - \t%d\n", i+1, p[i].cipher);
        printf_s("Surname of employee %d - \t%s\n", i + 1, p[i].surName);
        printf_s("The date of hire employee %d  -  %s\n", i + 1, p[i].howSkilled.hiredate);
        printf_s("The salary of employee %d  - \t%.2lf\n\n", i + 1, p[i].howSkilled.salary);
    }
}

void find(int number, struct employee* p) 
{
    int ch, length = 0, found = 0;
    char* lastNameSearch = NULL;
    printf_s("Enter last name to search: ");
    while ((ch = getchar()) != '\n') 
    {
        char* temp = realloc(lastNameSearch, (length + 1) * sizeof(char));
        if (temp == NULL) 
        {
            free(lastNameSearch);
            return;
        }
        lastNameSearch = temp;
        lastNameSearch[length++] = ch;
    }
    char* temp = realloc(lastNameSearch, (length + 1) * sizeof(char));
    if (temp == NULL) 
    {
        free(lastNameSearch);
        return;
    }
    lastNameSearch = temp;
    lastNameSearch[length] = '\0';
    for (int i = 0; i < number; i++)
    {
        if (mystrcmp(lastNameSearch, p[i].surName) == 0) 
        {
            found = 1;
            printf_s("Found last name %d: %s\n",found, p[i].surName);
            printf_s("Employee cipher: %d\n", p[i].cipher);
            printf_s("Date of hire: %s\n", p[i].howSkilled.hiredate);
            printf_s("Employee salary: %.2lf\n\n", p[i].howSkilled.salary);
        }
    }
    if (!found) 
    {
        printf_s("Last name not found.\n");
    }
    free(lastNameSearch);
}

int eraseElement(int number, struct employee* p)
{
    if (number == 1)
    {
        printf_s("There is only one element in the structure: do you want to delete this\n");
        printf_s("If yes - enter 1, if no - enter 0\n");
        if (input(1, 0) == 1)
        {
            free(p[0].surName);
            return 0;
        }
        else
        {
            printf_s("Function execution stopped.\n");
            return 1;
        }
    }
    if (number == 0)
    {
        printf_s("No elements. Function execution stopped.\n");
        return 1;
    }
    int numberOfErase,i,j;
    printf_s("Enter the number of structure, what you want to erase: ");
    numberOfErase = input(number, 0);
    numberOfErase--;
    free(p[numberOfErase].surName);
    for (i = numberOfErase;i < number-1;i++)
    {
        p[i].surName = p[i+1].surName;
        p[i].cipher = p[i+1].cipher;
        p[i].howSkilled.salary = p[i + 1].howSkilled.salary;
        for (j = 0;j < 11;j++)
        {
            p[i].howSkilled.hiredate[j] = p[i + 1].howSkilled.hiredate[j];
        }
    }
    struct employee* p0 = realloc(p, (number - 1) * sizeof(struct employee));
    if (p0 == NULL) 
    {
        printf_s("ERROR");
        return 1;
    }
    p = p0;
    number--;
    outputStructure(number, p);
    return 0;
}

void working(int number, struct employee* p)
{
    int numberOfEmployes, check;
    printf_s("Enter elements of structure\n");
    inputStructure(number, p);
    outputStructure(number, p);
    numberOfEmployes = number;
    while (1)
    {
        if (numberOfEmployes == 0)
            break;
        printf_s("If you want to find element of structure -  \tenter 1\n");
        printf_s("If you want to erase element of structure - \tenter 2\n");
        printf_s("If you want to output the structure -      \tenter 3\n");
        printf_s("If you want to stop the program -   \tenter any other key\n");
        check = getchar();
        if (check == '1')
        {
            find(numberOfEmployes, p);
        }
        else if (check == '2')
        {
           if(eraseElement(numberOfEmployes, p)==0)
            numberOfEmployes--;
        }
        else if (check == '3')
        {
            outputStructure(numberOfEmployes, p);
        }
        else
        {
            break;
        }
    }
}
