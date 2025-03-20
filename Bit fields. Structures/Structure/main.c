/*Структура содержит информацию о сотрудниках фирмы: шифр отдела
(число), фамилию (указатель), вложенную структуру – дату приёма на работу
(строка фиксированной длины) и сумму оклада. Найти сотрудников с
заданной фамилией. Удалить сотрудников с окладом ниже заданного.*/
/*16.03.2025*/
const HIGH_LIMIT = 100;
const LOW_LIMIT = 1;
#include "Functions.h"
int main()
{
    int numberOfEmployes;
    printf_s("Hello. This program can store data about the company's employees.\n");
    printf_s("Enter the number of employes: ");
    numberOfEmployes = input(HIGH_LIMIT, LOW_LIMIT);
    struct employee *p = (struct employee*)malloc(numberOfEmployes * sizeof(struct employee));
    working(numberOfEmployes, p);
    free(p);
    return 0;
}