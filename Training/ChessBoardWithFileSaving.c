#include <stdio.h>

//Kontrola vstupu
int isntValid(int inputData, int num)
{
	return (inputData != 1 || num < 1);
}

//Oramovani sachovnice
void borderLine(int numberFields, FILE *pFile)
{
	fprintf(pFile, "+");
	int i = 1;
	while(i <= numberFields)
	{
		fprintf(pFile, "-");
		i++;
	}
	fprintf(pFile, "+\n");
}

//Algoritmus pro zobrazeni radku
void printChar(int row, int column, int sizeField, FILE *pFile)
{
	if ((row / sizeField) % 2 == 0)
	{
		fprintf(pFile, "%c", ((column / sizeField) % 2 == 0) ? ' ' : 'X');
	}
	else
	{
		fprintf(pFile, "%c", ((column / sizeField) % 2 == 0) ? 'X' : ' ');
	}
}


int main()
{
	FILE * pFile = stdout;
	int countFields = 0, sizeField = 0, inputData = 0;
	const int maxSize = 64;

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

	//Kontrola max velikosti sachovnice, pokud je vetsi nez 64 poli => presmerovani do souboru
	if (countFields * sizeField > maxSize)
	{
		pFile = fopen("file.txt", "w");
	}

	borderLine(countFields * sizeField, pFile);

	for (int row = 0; row < (countFields * sizeField); row++)
	{
		fprintf(pFile, "|");

		for (int column = 0; column < (countFields * sizeField); column++)
		{
			printChar(row, column, sizeField, pFile);
		}

		fprintf(pFile, "|\n");
	}

	borderLine(countFields * sizeField, pFile);

	fclose(pFile);

	return 0;
}
