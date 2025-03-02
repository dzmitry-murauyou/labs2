#include <stdio.h>
#include "Functions.h"
const int LOWER_INPUT_AMOUNT = 1;
const int UPPER_INPUT_AMOUNT = 100;
const int LOWER_INPUT = -1000000;
const int UPPER_INPUT = 1000000;
int main(int argc, char* argv[])
{
	int work = 1, number, i;
	FILE* f;
	if (argc != 2){
	return 1;
	}
	fopen_s(&f, argv[1], "w+");
	if (f == NULL) {
		printf_s("Error opening file");
		return 1;
	}
	while (work)
	{
		printf_s("Welcome to the program for working with .txt files\n");
		printf_s("Enter the amount of numbers\n");
		number = input(UPPER_INPUT_AMOUNT, LOWER_INPUT_AMOUNT);
		rewind(f);
		fprintf_s(f, "%d ",number);
		for (i = 0; i < number; i++)
		{
			printf_s("Enter the number %d\n", i+1);
			fprintf_s(f, "%d ", input(UPPER_INPUT, LOWER_INPUT));
		}
		rewind(f);
		for (i = 0; i < number+1; i++)
		{
			int bufer;
			fscanf_s(f, "%d", &bufer);
			printf_s("%d ", bufer);
		}
		findMaxNumber(f, number);
		reverseNumber(f, number);
		printf_s("If you want to continue work with this file - enter 1 ");
		if (getchar() != '1')
		{
			fclose(f);
			fopen_s(&f, argv[1], "w+");
			if (f == NULL) 
			{
				return 1;
			}
			work--;
		}
	}
	fclose(f);
	return 0;
}