#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
const int LOWER_INPUT = 0;
const int LOWER_INPUT_OF_JUDJE = 3;
const int UPPER_INPUT = 100;
void File_Name(char* NameOfFile)
{
	printf_s("Enter the name of file(only Roman alphabet and digits)\n");
	scanf_s("%s", NameOfFile, 11);
	
	if (getchar() != '\n')
	{
		printf("Error: there are too many elements in the row\n");
		while (getchar() != '\n');
		File_Name(NameOfFile);
	}
	return;
}
int inputCheck(char* value, int LIMIT, int LIMIT_LOW)
{
	int i = 0, number = 0;
	for (; value[i] != '\0'; i++)
	{
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
	return number;
}
int input(int LIMIT, int LOWER_INPUT)
{
	char* value;
	int isCorrect = 0;
	while (isCorrect == 0)
	{
		value = (char*)calloc(12, sizeof(char));
		scanf_s("%11s", value, 12);
		if (getchar() != '\n')
		{
			printf("Error: there are too many elements in the row, or there are spaces\n");
			while (getchar() != '\n');
			value = NULL;
		}
		else if (inputCheck(value, LIMIT, LOWER_INPUT) != INT_MAX)
		{
			isCorrect = 1;
		}
		else
		{
			printf_s("Please, again\n");
			value = NULL;
		}
	}
	return inputCheck(value, LIMIT, LOWER_INPUT);
}
int laba8()
{
	FILE* scores;
	int* a = NULL;
	int number, i, maxscore, minscore, fullsum = 0;
	double final_score;
	char* file_name;
	file_name = (char*)calloc(12, sizeof(char*));
	File_Name(file_name);
	printf_s("Enter the number of scores\n");
	if (file_name == NULL)
	{
		printf("Error\n");
		while (getchar() != '\n');
		return 1;
	}
	fopen_s(&scores, file_name, "w+b");
	if (scores == NULL)
	{
		return 1;
	}
	number = input(UPPER_INPUT, LOWER_INPUT_OF_JUDJE);
	fwrite(&number, sizeof(int), 1, scores);
	a = (int*)calloc(number + 1, sizeof(int));
	if (a == NULL)
	{
		return 1;
	}
	for (i = 0;i < number;i++)
	{
		printf_s("Enter the value of score %d\n", i + 1);
		a[i] = input(UPPER_INPUT, LOWER_INPUT);
	}
	fwrite(a, sizeof(a[0]), number, scores);
	rewind(scores);
	fread(a, sizeof(a[0]), number + 1, scores);
	printf_s("Number of scores is %d\n", a[0]);
	for (i = 1;i < number + 1;i++)
	{
		printf_s("Value of score %d is %d\n", i, a[i]);
	}
	rewind(scores);
	minscore = a[1];
	maxscore = a[1];
	for (i = 1;i < number + 1;i++)
	{
		fullsum += a[i];
		if (maxscore < a[i])
		{
			maxscore = a[i];
		}
		else if (minscore > a[i])
			minscore = a[i];
	}
	for (i = 1; i < number + 1;i++)
	{
		if (a[i] == maxscore)
		{
			a[i] = minscore;
		}
		else if (a[i] == minscore)
		{
			a[i] = maxscore;
		}
	}
	rewind(scores);
	fwrite(a, sizeof(a[0]), number + 1, scores);
	final_score = (double)(fullsum - maxscore - minscore) / (number - 2);
	printf_s("Final score is %.3lf \n", final_score);
	rewind(scores);
	for (i = 0; i < number + 1;i++)
	{
		a[i] = -1;
	}
	fread(a, sizeof(a[0]), number+1, scores);
	printf_s("Number of scores is %d\n", a[0]);
	for (i = 1;i < number + 1;i++)
		printf_s("Value of score %d is %d\n", i, a[i]);
	fclose(scores);
	free(a);
	free(file_name);
	return 0;
}
int main()
{
	int repeat = 1;
	printf_s("Hello, this is Laba8(Laba2_1)\n");
	while (repeat == 1)
	{
		laba8();
		printf_s("You want to repeat(if yes - press space)\n");
		if (_getch() != ' ')
		{
			printf_s("GoodBye");
			return 0;
		}
	}
}