#ifndef __PROGTEST__
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>
#endif /* __PROGTEST__ */

typedef struct
{
	char *word;
} WORDS;

int compareWords(const void *first, const void *second)
{
	const WORDS *arg_1 = (WORDS *)first;
	const WORDS *arg_2 = (WORDS *)second;
	return (strcasecmp(arg_1->word, arg_2->word));
}

int wordRepeat(const int words_count, const char *token, WORDS *words)
{
	for (int i = 0; i < words_count - 1; i++)
	{
		if (strcasecmp(token, words[i].word) == 0)
			return 1;
	}
	return -1;
}

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

#ifndef __PROGTEST__
int main ( int argc, char * argv [] )
{
  assert ( sameWords ( "Hello students.", "HELLO studEnts!" ) == 1 );
  assert ( sameWords ( " He said 'hello!'", "'Hello.' he   said." ) == 1 );
  assert ( sameWords ( "He said he would do it.", "IT said: 'He would do it.'" ) == 1 );
  assert ( sameWords ( "one two three", "one two five" ) == 0 );
  return 0;
}
#endif /* __PROGTEST__ */
