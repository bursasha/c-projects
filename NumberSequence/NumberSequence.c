#include <stdio.h>
#include <math.h>

// ---------------------------------------------------------------------------------------------------------------------
// ---------------------------------------------------------------------------------------------------------------------

/**
 * @brief
 * Checks if the input values are valid.
 *
 * This function verifies that the position in the sequence is non-negative and the base is within the range [2, 36].
 *
 * @param number_position - The position in the sequence.
 * @param number_system - The base of the number system.
 * @return 1 if the input values are invalid, 0 otherwise.
 */
long long int isntValid (long long int number_position, int number_system)
{
	return (number_position < 0 || number_system < 2 || number_system > 36);
}

// ---------------------------------------------------------------------------------------------------------------------

/**
 * @brief
 * Gets the size (number of digits) of the number at the given position in the sequence.
 *
 * This function calculates the number of digits of the number that contains the digit at the given position in the sequence.
 *
 * @param number_position - The position in the sequence.
 * @param number_system - The base of the number system.
 * @return The size (number of digits) of the number.
 */
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

// ---------------------------------------------------------------------------------------------------------------------

/**
 * @brief
 * Gets the base number for the given size.
 *
 * This function calculates the base number for the given size by generating the numbers of all previous sizes.
 *
 * @param number_system - The base of the number system.
 * @param size - The size (number of digits) of the number.
 * @return The base number.
 */
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

// ---------------------------------------------------------------------------------------------------------------------

/**
 * @brief
 * Gets the base digit for the given size.
 *
 * This function calculates the base digit for the given size by generating the digits of all previous sizes.
 *
 * @param number_system - The base of the number system.
 * @param size - The size (number of digits) of the number.
 * @return The base digit.
 */
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

// ---------------------------------------------------------------------------------------------------------------------

/**
 * @brief
 * Gets the number at the given position in the sequence.
 *
 * This function calculates the number that contains the digit at the given position in the sequence.
 *
 * @param number_position - The position in the sequence.
 * @param number_system - The base of the number system.
 * @param number_base - The base number.
 * @param digit_base - The base digit.
 * @param size - The size (number of digits) of the number.
 * @return The number at the given position.
 */
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

// ---------------------------------------------------------------------------------------------------------------------

/**
 * @brief
 * Converts the result to the specified base and prints it.
 *
 * This function converts the result from getPosition to the specified base and prints the digits.
 *
 * @param result - The number to be converted.
 * @param size - The size (number of digits) of the number.
 * @param number_system - The base of the number system.
 */
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

// ---------------------------------------------------------------------------------------------------------------------

/**
 * @brief
 * Prints the index position of the digit in the number.
 *
 * This function calculates and prints the position of the digit in the number for the given position in the sequence.
 *
 * @param number_position - The position in the sequence.
 * @param digit_base - The base digit.
 * @param size - The size (number of digits) of the number.
 */
void getIndexPosition (long long int number_position, long long int digit_base, int size)
{
	int index_position = (number_position - digit_base) % size;
	for (int i = 0; i < index_position; i++) printf(" ");
	printf("^\n");
}

// ---------------------------------------------------------------------------------------------------------------------
// ---------------------------------------------------------------------------------------------------------------------

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
