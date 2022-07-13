#include <stdio.h>

//Kontrola vstupu
int isntValid(int inputData, int num)
{
	return (inputData != 1 || num < 1);
}

//Oramovani sachovnice
void borderLine(int numberFields)
{
	printf("+");
	int i = 1;
	while (i <= numberFields)
	{
		printf("-");
		i++;
	}
	printf("+\n");
}

//Algoritmus pro zobrazeni radku
void printChar(int row, int column, int sizeField)
{
	if ((row / sizeField) % 2 == 0)
	{
		printf("%c", ((column / sizeField) % 2 == 0) ? ' ' : 'X');
	}
	else
	{
		printf("%c", ((column / sizeField) % 2 == 0) ? 'X' : ' ');
	}
}

int main()
{
	int countFields = 0, sizeField = 0, inputData = 0;

	printf("Zadejte pocet poli:\n");
	inputData = scanf(" %d", &countFields);
	if (isntValid(inputData, countFields))
	{
		printf("Nespravny vstup.\n");
		return 1;
	}

	printf("Zadejte velikost pole:\n");
	inputData = scanf(" %d", &sizeField);
	if (isntValid(inputData, sizeField))
	{
		printf("Nespravny vstup.\n");
		return 1;
	}

	borderLine(countFields * sizeField);

	for (int row = 0; row < (countFields * sizeField); row++)
	{
		printf("|");

		for (int column = 0; column < (countFields * sizeField); column++)
		{
			printChar(row, column, sizeField);
		}

		printf("|\n");
	}

	borderLine(countFields * sizeField);

	return 0;
}
