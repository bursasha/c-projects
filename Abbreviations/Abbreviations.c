#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// ---------------------------------------------------------------------------------------------------------------------
// ---------------------------------------------------------------------------------------------------------------------

/**
 * @brief Validates if the abbreviation contains only uppercase letters.
 *
 * This function checks if each character in the given abbreviation is an uppercase letter
 * from A to Z. If any character does not meet this criterion, the function returns 0 indicating
 * invalid abbreviation. Otherwise, it returns 1 indicating a valid abbreviation.
 *
 * @param abbr - The abbreviation string to validate.
 * @return int - 1 if the abbreviation is valid, 0 otherwise.
 */
int validAbbr(char *abbr)
{
	int len = strlen(abbr);
	for (int i = 0; i < len; i++)
	{
		if (abbr[i] != toupper(abbr[i]) || !isalpha(abbr[i]))
			return 0; // WRONG
	}
	return 1; // OK
}

// ---------------------------------------------------------------------------------------------------------------------

/**
 * @brief Reads and validates the abbreviation from the standard input.
 *
 * This function prompts the user to enter the abbreviation, reads it from the standard input,
 * and validates it using the validAbbr function. If the abbreviation is invalid or the input
 * fails, it prints an error message and returns 0. Otherwise, it returns 1.
 *
 * @param abbr - The abbreviation string to store the input.
 * @return int - 1 if the abbreviation is valid and read successfully, 0 otherwise.
 */
int getAbbr(char *abbr)
{
	printf("Zkratka:\n");
	if (scanf(" %s", abbr) != 1 || !validAbbr(abbr))
	{
		printf("Nespravny vstup.\n");
		free(abbr);
		return 0; // WRONG
	}
	return 1; // OK
}

// ---------------------------------------------------------------------------------------------------------------------

/**
 * @brief Finds the positions of the quotes in the input string.
 *
 * This function scans the input string to find the positions of the first and second quotes.
 * It validates if exactly two quotes are present. If the quotes are missing or there are extra
 * quotes, it prints an error message and returns 0. Otherwise, it returns 1.
 *
 * @param quo_1 - Pointer to store the position of the first quote.
 * @param quo_2 - Pointer to store the position of the second quote.
 * @param str - The input string to scan.
 * @param str_size - The size of the input string.
 * @param abbr - The abbreviation string.
 * @return int - 1 if the quotes are found and valid, 0 otherwise.
 */
int getQuotes(long int *quo_1, long int *quo_2, char *str, long int str_size, char *abbr)
{
	for (int i = 0, quo_cnt = 0; i < str_size - 1; i++)
	{
		if (str[i] == '"')
		{
			quo_cnt++;
			if (quo_cnt == 1)
				*quo_1 = i;
			if (quo_cnt == 2)
				*quo_2 = i;
		}
		if (quo_cnt > 2 || (i == str_size - 2 && quo_cnt < 2))
		{
			printf("Nespravny vstup.\n");
			free(abbr), free(str);
			return 0; // WRONG
		}
	}
	return 1; // OK
}

// ---------------------------------------------------------------------------------------------------------------------

/**
 * @brief Extracts the substring enclosed by quotes.
 *
 * This function extracts the substring from the input string that is enclosed by the quotes.
 * The extracted substring is stored in the provided pointer.
 *
 * @param str_quo - Pointer to store the extracted substring.
 * @param str - The input string.
 * @param quo_1 - The position of the first quote.
 * @param quo_2 - The position of the second quote.
 */
void wrStrQuotes(char **str_quo, char *str, int quo_1, int quo_2)
{
	*str_quo = (char *)malloc((quo_2 - quo_1) * sizeof(char));
	strncpy(*str_quo, str + quo_1 + 1, quo_2 - quo_1 - 1);
}

// ---------------------------------------------------------------------------------------------------------------------

/**
 * @brief Searches for the abbreviation in the quoted string.
 *
 * This function recursively searches for the abbreviation in the quoted string while considering
 * the constraints. It prints all possible matches or counts the matches based on the operation type.
 *
 * @param op_sign - The operation type ('?' or '#').
 * @param str - The input string to search within.
 * @param abbr - The abbreviation to search for.
 * @param N - The maximum number of letters to use from each word.
 * @param str_len - The length of the input string.
 * @param str_pos - The current position in the input string.
 * @param abbr_pos - The current position in the abbreviation.
 * @param arr - Array to store the positions of matched letters.
 * @param word_index - Pointer to track the number of letters used from the current word.
 * @param flag - Pointer to indicate backtracking.
 * @param comb_cnt - Pointer to count the number of valid combinations.
 */
void getStrQuotes(char op_sign, char *str, char *abbr, int N, int str_len, int str_pos, int abbr_pos, int *arr, int *word_index, int *flag, int *comb_cnt)
{
	int abbr_len = strlen(abbr);
	for (; str_pos < str_len; str_pos++) // проход по символам строки
	{
		if (*flag) abbr_pos--, *word_index-=1, *flag = 0;
		if (str_pos < str_len) // проход по словам
		{
			if (str_pos == 0) *word_index = 0;
			if (str[str_pos] != ' ') str[str_pos] = tolower(str[str_pos]);
			else *word_index = 0;
		}
		if (abbr_pos < abbr_len)
		{
			if (str[str_pos] == tolower(abbr[abbr_pos]) && *word_index < N) // нахождение буквы из аббревиатуры и количество переведенных букв в слове меньше Н
			{
				str[str_pos] = toupper(str[str_pos]), arr[abbr_pos++] = str_pos, *word_index+=1;
				if (str_pos < (str_len - 1) && abbr_pos < abbr_len)
					getStrQuotes(op_sign, str, abbr, N, str_len, (str_pos + 1), abbr_pos, arr, word_index, flag, comb_cnt);
			}
		}
		if (str_pos == (str_len - 1)) // мы на конце строки
		{
			if (abbr_pos >= abbr_len)
			{
				if (op_sign == '?') printf("\"%s\"\n", str); 
				*comb_cnt+=1;
				str_pos = arr[--abbr_pos], str[str_pos] = tolower(str[str_pos]);
				if ((str_pos + 1) == str_len)
				{
					str_pos = arr[abbr_pos - 1], str[str_pos] = tolower(str[str_pos]), *flag = 1;
					break;
				}
			}
			else
			{
				if (abbr_pos > 0)
					str_pos = arr[abbr_pos - 1], str[str_pos] = tolower(str[str_pos]), *flag = 1;
				break;
			}
		}
	}
}

// ---------------------------------------------------------------------------------------------------------------------
// ---------------------------------------------------------------------------------------------------------------------

int main (void)
{
	char *abbr = (char *) malloc (300 * sizeof(char));
	int scanf_data = 0;
	char op_sign = '\0';
	int N = 0;
	char *str = NULL, *str_quo = NULL;
	size_t str_len = 0;
	long int str_size = 0; // длина начальной необрезанной строки
	long int quo_1 = 0, quo_2 = 0;
	int *arr = (int *) malloc (300 * sizeof(int));
	int word_index = 0, flag = 0;

	if (!getAbbr(abbr))
		return 1;

	printf("Problemy:\n");
	while ((scanf_data = scanf(" %c %d", &op_sign, &N)) != feof(stdin))
	{
		if ((scanf_data != 0 && feof(stdin)) || scanf_data != 2 || (op_sign != '?' && op_sign != '#') || N < 1)
		{
			printf("Nespravny vstup.\n");
			free(abbr);
			return 1;
		}

		if (op_sign == '?' || op_sign == '#')
		{
			if ((str_size = getline(&str, &str_len, stdin)) == feof(stdin) && str_size != 0)
			{
				printf("Nespravny vstup.\n");
				free(abbr), free(str);
				return 1;
			}
			if (!getQuotes(&quo_1, &quo_2, str, str_size, abbr))
				return 1;
			wrStrQuotes(&str_quo, str, quo_1, quo_2);
			str_quo[quo_2 - quo_1 - 1] = '\0';
			if (op_sign == '?')
			{
				int str_quo_pos = 0, abbr_pos = 0, comb_cnt = 0;
				getStrQuotes(op_sign, str_quo, abbr, N, quo_2 - quo_1 - 1, str_quo_pos, abbr_pos, arr, &word_index, &flag, &comb_cnt);
				printf("> %d\n", comb_cnt);
			}
			else
			{
				for (int n = 1; n <= N; n++)
				{
					int str_quo_pos = 0, abbr_pos = 0, comb_cnt = 0;
					getStrQuotes(op_sign, str_quo, abbr, n, quo_2 - quo_1 - 1, str_quo_pos, abbr_pos, arr, &word_index, &flag, &comb_cnt);
					printf("> limit %d: %d\n", n, comb_cnt);
				}
			}
		}
	}
	printf("Nespravny vstup.\n");
	free(abbr), free(str), free(str_quo), free(arr);
	return 0;
}
