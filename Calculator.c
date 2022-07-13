#include <stdio.h>
#include <math.h>

int isOperator(char op, char eq)
{
	return ((op == '+' || op == '-' || op == '*' || op == '/') && eq == '=');
}

int main() 
{
	double x, y;
	char op, eq;

	printf("Zadejte vzorec:\n");

	if (scanf(" %lf %c %lf %c", &x, &op, &y, &eq) != 4 || !isOperator(op, eq) || (op == '/' && y == 0))
	{
		printf("Nespravny vstup.\n");
		return 1;
	}

	double result;

	if(op == '+')
	{
		result = x + y;
	}
	else if(op == '-')
	{
		result = x - y;
	}
	else if(op == '*')
	{
		result = x * y;
	}
	else
	{
		result = x / y;
		if(result < 0)
		{
			printf("%g\n", ceil (result));
			return 0;
		}
		printf("%g\n", floor (result));
		return 0;
	}

	printf("%g\n", result);

	return 0;
}