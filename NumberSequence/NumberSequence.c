#include <stdio.h>
#include <math.h>

// number_position - число, которое указывает на цифру конкретного числа в последовательности чисел в данной системе счисления
// number_system - система счисления, в которой работаем с number_position

// isntValid - проверка вводных данных
long long int isntValid (long long int number_position, int number_system)
{
	return (number_position < 0 || number_system < 2 || number_system > 36);
}

// getSize - получение разрядности числа, на цифру которого указывает number_positon 
long long int getSize (long long int number_position, int number_system)
{
	long long int i = (number_system - 1), size = 1;
	while (i < number_position)
	{
		size++;
		i += pow (number_system, size - 1) * (number_system - 1) * size;
	}
	return size;
}

// getNumberBase - генерирует числа всех предыдущих разрядностей
long long int getNumberBase (int number_system, int size)
{
	long long int number_base = number_system;
	if (size > 2)
	{
		for (int i = 2; i < size; i++)
		{
			number_base += pow (number_system, (i - 1)) * (number_system - 1);
		}
	}
	return number_base;
}

// getDigitBase - генерирует цифры чисел всех предыдущих разрядностей
long long int getDigitBase (int number_system, int size)
{
	long long int digit_base = number_system;
	if (size > 2)
	{
		for (int i = 2; i < size; i++)
		{
			digit_base += pow (number_system, i - 1) * (number_system - 1) * i;
		}
	}
	return digit_base;
}

// getPosition - рассчитывает число, на которое указывает number_position
long long int getPosition (long long int number_position, int number_system, long long int number_base, long long int digit_base, int size)
{
	long long int result = 0;
	if (number_position >= number_system) 
	{
		result = number_base + ((number_position - digit_base) / size);
	}
	else result = number_position;
	return result;
}

// systemConvertation - конвертация result из getPosition в систему счисления number_system
void systemConvertation (long long int result, int size, int number_system)
{
	const int max_array_size = 111;
	long long int divisible = result;
	int result_array[max_array_size];
	for (int i = 0; i < size; i++)
	{
		result_array[i] = divisible % number_system;
		divisible /= number_system;
	}
	for (int i = size - 1; i >= 0; i--) 
	{
		if (result_array[i] > 9) printf("%c", 'a' + (result_array[i] - 10));
		else printf("%d", result_array[i]);
	}
	printf("\n");
}

// getIndexPosition - рассчитывает положение индекса конкретной цифры в числе result
void getIndexPosition (long long int number_position, long long int digit_base, int size)
{
	int index_position = (number_position - digit_base) % size;
	for (int i = 0; i < index_position; i++) printf(" ");
	printf("^\n");
}


int main()
{
	long long int number_position = 0;
	int number_system = 0;

	printf ("Pozice a soustava:\n");
	while (scanf (" %lld %d", &number_position, &number_system) != EOF)
	{
		if (isntValid (number_position, number_system))
		{
			printf ("Nespravny vstup.\n");
			return 1;
		}
		int size = getSize (number_position, number_system);
		long long int number_base = getNumberBase (number_system, size);
		long long int digit_base = getDigitBase (number_system, size);
		long long int result = getPosition (number_position, number_system, number_base, digit_base, size);
		systemConvertation (result, size, number_system);
		getIndexPosition (number_position, digit_base, size);
	}

	return 0;
}
