#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <Windows.h>
#include <time.h>
#define K 1.2473309
#define MIN -20
#define MAX 20

void main()
{
	setlocale(LC_ALL, "rus");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	srand(time(NULL));

	int row, col;

	puts("Введите количество строк и столбцов матрицы:");
	while (scanf_s("%d %d", &row, &col) != 2 || row < 2 || col < 2)
	{
		while (getchar() != '\n');
		puts("Вы ввели что-то не так, учтите, что кол-во столбцов и строк не могут быть меньше 2\nПовторите ввод:");
	}

	int* arr = (int*)malloc(row * col * sizeof(int));
	if (arr == NULL)
	{
		puts("Недостаточно памяти...");
		return;
	}
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			*(arr + i * col + j) = rand() % (MAX - MIN + 1) + MIN;
		}
	}

	puts("Исходная матрица:");
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			printf_s("%3d  ", *(arr + i * col + j));
		}
		puts("");
	}

	int size_temp = (row - 1) * 2 + (col - 1) * 2;
	int* arr_temp = (int*)malloc(size_temp * sizeof(int));
	if (arr_temp == NULL)
	{
		puts("Недостаточно памяти...");
		return;
	}

	int l = 0;
	for (int i = 0; i < row; i++)
	{
		if (i == 0 || i == row - 1)
		{
			for (int j = 0; j < col; j++, l++)
			{
				*(arr_temp + l) = *(arr + i * col + j);
			}
		}
		else
		{
			for (int j = 0; j < col; j += col - 1, l++)
			{
				*(arr_temp + l) = *(arr + i * col + j);
			}
		}
	}

	//puts("Буферный массив:");
	//for (int i = 0; i < size_temp; i++)
	//{
	//	printf_s("arr_temp[%2d] = %d\n", i + 1, *(arr_temp + i));
	//}

	int temp, step, flag = 1;
	step = size_temp - 1;
	while (step > 1)
	{
		for (int i = 0; i < size_temp; i++)
		{
			if (*(arr_temp + i) < *(arr_temp + i + step))
			{
				temp = *(arr_temp + i);
				*(arr_temp + i) = *(arr_temp + i + step);
				*(arr_temp + i + step) = temp;
			}
			step /= K;
		}
	}
	while (flag)
	{
		flag = 0;
		for (int i = 0; i < size_temp - 1; i++)
		{
			if (*(arr_temp + i) > *(arr_temp + i + 1))
			{
				temp = *(arr_temp + i);
				*(arr_temp + i) = *(arr_temp + i + 1);
				*(arr_temp + i + 1) = temp;
				flag = 1;
			}
		}
	}

	//puts("Отсортированный буферный массив:");
	//for (int i = 0; i < size_temp; i++)
	//{
	//	printf_s("arr_temp[%2d] = %d\n", i + 1, *(arr_temp + i));
	//}

	//puts("Исходная матрица:");
	//for (int i = 0; i < row; i++)
	//{
	//	for (int j = 0; j < col; j++)
	//	{
	//		printf_s("%3d  ", *(arr + i * col + j));
	//	}
	//	puts("");
	//}

	l = 0;
	for (int j = 0; j < col; j++, l++)
	{
		*(arr + j) = *(arr_temp + l);
	}
	for (int i = 1; i < row; i++, l++)
	{
		*(arr + i * col + col - 1) = *(arr_temp + l);
	}
	for (int j = col - 2; j >= 0; j--, l++)
	{
		*(arr + (row - 1) * col + j) = *(arr_temp + l);
	}
	for (int i = row - 2; i >= 1; i--, l++)
	{
		*(arr + i * col) = *(arr_temp + l);
	}

	free(arr_temp);

	puts("Новая матрица:");
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			printf_s("%3d  ", *(arr + i * col + j));
		}
		puts("");
	}

	free(arr);
	system("pause");
}