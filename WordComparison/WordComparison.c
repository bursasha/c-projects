#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

// ---------------------------------------------------------------------------------------------------------------------
// ---------------------------------------------------------------------------------------------------------------------

/**
 * @brief
 * Represents a structure to hold a word.
 *
 * This structure is used to store a word from the input strings.
 */
typedef struct
{
	char *word;
} WORDS;

// ---------------------------------------------------------------------------------------------------------------------

/**
 * @brief
 * Compares two WORDS structures case insensitively.
 *
 * This function is used for sorting the words case insensitively.
 *
 * @param first - Pointer to the first WORDS structure.
 * @param second - Pointer to the second WORDS structure.
 * @return A negative, zero, or positive integer if the first word is less than, equal to, or greater than the second word, respectively.
 */
int compareWords(const void *first, const void *second)
{
	const WORDS *arg_1 = (WORDS *)first;
	const WORDS *arg_2 = (WORDS *)second;
	return (strcasecmp(arg_1->word, arg_2->word));
}

// ---------------------------------------------------------------------------------------------------------------------

/**
 * @brief
 * Checks if a word is already present in the list of words.
 *
 * This function is used to avoid counting duplicate words.
 *
 * @param words_count - The current count of words.
 * @param token - The word to check for duplication.
 * @param words - The list of words.
 * @return 1 if the word is already present, -1 otherwise.
 */
int wordRepeat(const int words_count, const char *token, WORDS *words)
{
	for (int i = 0; i < words_count - 1; i++)
	{
		if (strcasecmp(token, words[i].word) == 0)
			return 1;
	}
	return -1;
}

// ---------------------------------------------------------------------------------------------------------------------

/**
 * @brief
 * Compares two strings to check if they are composed of the same words.
 *
 * This function splits the strings into words, removes duplicates, sorts them, and then compares.
 *
 * @param a - The first string to compare.
 * @param b - The second string to compare.
 * @return 1 if the strings are composed of the same words, 0 otherwise.
 */
int sameWords ( const char * a, const char * b )
{
	char delimiter_signs[] = " \t1234567890.,:;'/\"?!@#$%^&*()[]{}§+~<>_=-'\0'\n";
	char *a_string = strdup(a), *b_string = strdup(b);
	WORDS *a_words = NULL, *b_words = NULL;
	int a_words_count = 0, b_words_count = 0;
	int memory_amount = 100;

	char *a_token = strtok(a_string, delimiter_signs);
	while (a_token != NULL)
	{
		a_words_count++;
		if (a_words == NULL)
			a_words = (WORDS *)malloc(memory_amount * sizeof(*a_words));
		else
		{
			int word_repeat = wordRepeat(a_words_count, a_token, a_words);
			if (word_repeat == -1)
			{
				if (a_words_count == memory_amount)
					a_words = (WORDS *)realloc(a_words, (memory_amount *= 1.5) * sizeof(*a_words));
			}
			else
			{
				a_token = strtok(NULL, delimiter_signs);
				a_words_count--;
				continue;
			}
		}
		a_words[a_words_count - 1].word = a_token;
		a_token = strtok(NULL, delimiter_signs);
	}

	char *b_token = strtok(b_string, delimiter_signs);
	while (b_token != NULL)
	{
		b_words_count++;
		if (b_words == NULL)
			b_words = (WORDS *)malloc(memory_amount * sizeof(*b_words));
		else
		{
			int word_repeat = wordRepeat(b_words_count, b_token, b_words);
			if (word_repeat == -1)
			{
				if (b_words_count == memory_amount)
					b_words = (WORDS *)realloc(b_words, (memory_amount *= 1.5) * sizeof(*b_words));
			}
			else
			{
				b_token = strtok(NULL, delimiter_signs);
				b_words_count--;
				continue;
			}
		}
		b_words[b_words_count - 1].word = b_token;
		b_token = strtok(NULL, delimiter_signs);
	}

	qsort(a_words, a_words_count, sizeof(*a_words), compareWords);
	qsort(b_words, b_words_count, sizeof(*b_words), compareWords);

	if (a_words_count != b_words_count)
	{
		free(a_words), free(b_words);
		free(a_string), free(b_string);
		return 0;
	}
	for (int i = 0; i < a_words_count; i++)
	{
		if (strcasecmp(a_words[i].word, b_words[i].word) != 0)
		{
			free(a_words), free(b_words);
			free(a_string), free(b_string);
			return 0;
		}
	}

	free(a_words), free(b_words);
	free(a_string), free(b_string);
	return 1;
}

// ---------------------------------------------------------------------------------------------------------------------
// ---------------------------------------------------------------------------------------------------------------------

int main ( int argc, char * argv [] )
{
	assert ( sameWords ( "Hello students.", "HELLO studEnts!" ) == 1 );
	assert ( sameWords ( " He said 'hello!'", "'Hello.' he   said." ) == 1 );
	assert ( sameWords ( "He said he would do it.", "IT said: 'He would do it.'" ) == 1 );
	assert ( sameWords ( "one two three", "one two five" ) == 0 );

	// -----------------------------------------------------------------------------------------------------------------

	return 0;
}
