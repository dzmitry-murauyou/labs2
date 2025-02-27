#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
const int LOWER_INPUT = 0;
const int LOWER_INPUT_OF_JUDJE = 3;
const int UPPER_INPUT = 100;
int inputCheck(char* value, int LIMIT, int LIMIT_LOW) 
{
    int i = 0, number = 0;
    for (; value[i] != '\0'; i++) 
    {
        if (value[i] < '0' || value[i] > '9') 
        {
            printf("Error: Invalid characters have been entered.\n");
            return INT_MAX;
        }
        int digit = value[i] - '0';
        number = number * 10 + digit;
    }
    if (number < LIMIT_LOW || number > LIMIT) 
    {
        printf("Error: Input is out of bounds.\n");
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
            printf("Memory allocation failed.\n");
            return INT_MAX;
        }
        scanf_s("%s", value, 12);
        if (getchar() != '\n') 
        {
            printf("Error: there are too many elements in the row, or there are spaces\n");
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
            printf("Please, again\n");
            free(value);
            value = NULL;
        }
    }
    int result = inputCheck(value, LIMIT, LOWER_INPUT);
    free(value);
    return result;
}
int laba8(const char* filename) {
    FILE* scores;
    int number, i, maxscore = -1, minscore = -1;
    double final_score = 0.0, fullsum = 0.0;
    printf("Enter the number of scores\n");
    fopen_s(&scores, filename, "w+b");
    if (scores == NULL) 
    {
        return 1;
    }
    number = input(UPPER_INPUT, LOWER_INPUT_OF_JUDJE);
    fwrite(&number, sizeof(int), 1, scores);
    for (i = 0; i < number; i++) 
    {
        printf("Enter the value of score %d\n", i + 1);
        int score = input(UPPER_INPUT, LOWER_INPUT);
        fwrite(&score, sizeof(int), 1, scores);
    }
    rewind(scores);
    fseek(scores, sizeof(int), SEEK_CUR);
    for (i = 0; i < number; i++)
    {
        int score;
        fread(&score, sizeof(int), 1, scores);
        fullsum += score;
        if (score > maxscore) 
        {
            maxscore = score;
        }
        if (score < minscore) 
        {
            minscore = score;
        }
    }
    rewind(scores);
    fseek(scores, sizeof(int), SEEK_CUR);
    for (i = 0; i < number; i++) 
    {
        int score;
        fread(&score, sizeof(int), 1, scores);
        if (score == maxscore) 
        {
            score = minscore; 
            fseek(scores, sizeof(int) * (-1), SEEK_CUR);
            fwrite(&score, sizeof(int), 1, scores);
        }
        else if (score == minscore) 
        {
            score = maxscore; 
            fseek(scores, sizeof(int) * (-1), SEEK_CUR);
            fwrite(&score, sizeof(int), 1, scores);
        }
    }
    final_score = (fullsum - maxscore - minscore) / (number - 2);
    printf("Final score is %.3lf \n", final_score);
    rewind(scores);
    fread(&number, sizeof(int), 1, scores);
    printf("Number of scores is %d\n", number);
    for (i = 0; i < number; i++) 
    {
        int score;
        fread(&score, sizeof(int), 1, scores);
        printf("Value of score %d is %d\n", i + 1, score);
    }
    fclose(scores);
    return 0;
}
int main(int argc, char* argv[]) 
{
    if (argc < 2) 
    {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }
    const char* filename = argv[1];
    printf("Hello, this is Laba8(Laba2_1)\n");
    while (1) 
    {
        laba8(filename);
        printf("You want to repeat? (if yes - enter 1)\n");
        if (getchar() != '1') 
        {
            printf("Goodbye\n");
            return 0;
        }
        while (getchar() != '\n');
    }
    return 0;
}
