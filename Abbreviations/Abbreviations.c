#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

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

void wrStrQuotes(char **str_quo, char *str, int quo_1, int quo_2)
{
	*str_quo = (char *)malloc((quo_2 - quo_1) * sizeof(char));
	strncpy(*str_quo, str + quo_1 + 1, quo_2 - quo_1 - 1);
}

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
