#ifndef __PROGTEST__
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>

typedef struct TItem
{
	struct TItem *m_Next;
	char m_Digit;
} TITEM;

TITEM *createItem(char digit, TITEM *next)
{
	TITEM *n = (TITEM *)malloc(sizeof(*n));
	n->m_Digit = digit;
	n->m_Next = next;
	return n;
}

void deleteList(TITEM *l)
{
	while (l)
	{
		TITEM *tmp = l->m_Next;
		free(l);
		l = tmp;
	}
}
#endif /* __PROGTEST__ */

int getLen(TITEM *x)
{
	int num_len = 0;
	while (x)
	{
		if (!isdigit(x->m_Digit))
			return 0;
		num_len += 1;
		x = x->m_Next;
	}
	return num_len;
}

void getNumberRec(TITEM *x, char *num_str, int num_len)
{
	if (x->m_Next)
		getNumberRec(x->m_Next, num_str, num_len - 1);
	num_str[num_len] = x->m_Digit;
}

char *getNumber(TITEM *x)
{
	int num_len = getLen(x);
	if (!num_len)
		return NULL;
	char *num_str = (char *)malloc((num_len + 1) * sizeof(char));
	num_str[num_len] = '\0';
	getNumberRec(x, num_str, num_len - 1);
	return num_str;
}

TITEM *maxOf(TITEM **x, int nr)
{
	char **arr = (char **)malloc(nr * sizeof(char *));
	int max, zero_max = 0;

	for (int i = 0; i < nr; i++)
	{
		arr[i] = getNumber(*(x + i));
		if (arr[i] == NULL)
		{
			for (int k = 0; k < nr; k++)
				free(arr[k]);
			free(arr);
			return NULL;
		}
	}

	for (int j = 0; j < nr; j++)
	{
		int zero_j = 0;
		for (int z = 0; arr[j][z] == '0'; z++)
			zero_j++;
		if (j == 0 || (strlen(arr[max]+zero_max) < strlen(arr[j]+zero_j)) || (strlen(arr[max]+zero_max) == strlen(arr[j]+zero_j) && strcmp(arr[max]+zero_max, arr[j]+zero_j) < 0))
		{
			max = j;
			zero_max = zero_j;
		}
	}

	for (int k = 0; k < nr; k++)
		free(arr[k]);
	free(arr);

	return x[max];
}

#ifndef __PROGTEST__
int main(int argc, char *argv[])
{
	TITEM *a[5];

	a[0] = createItem('4',
							createItem('3',
										  createItem('2',
														 createItem('1', NULL))));
	a[1] = createItem('2',
							createItem('3',
										  createItem('4',
														 createItem('5', NULL))));

	assert(maxOf(a, 2) == a[1]);
	deleteList(a[0]);
	deleteList(a[1]);

	a[0] = createItem('0',
							createItem('0',
										  createItem('0',
														 createItem('1', NULL))));
	a[1] = createItem('2',
							createItem('0',
										  createItem('0',
														 createItem('1', NULL))));
	a[2] = createItem('1',
							createItem('0',
										  createItem('0',
														 createItem('1', NULL))));
	a[3] = createItem('2',
							createItem('0',
										  createItem('0',
														 createItem('1',
																		createItem('0',
																					  createItem('0', NULL))))));

	assert(maxOf(a, 4) == a[1]);
	deleteList(a[0]);
	deleteList(a[1]);
	deleteList(a[2]);
	deleteList(a[3]);

	a[0] = createItem('1',
							createItem('0',
										  createItem('0',
														 createItem('0',
																		createItem('0',
																					  createItem('0', NULL))))));
	a[1] = createItem('0',
							createItem('0',
										  createItem('1', NULL)));
	a[2] = createItem('1',
							createItem('0',
										  createItem('0',
														 createItem('0',
																		createItem('0',
																					  createItem('9', NULL))))));
	a[3] = createItem('0',
							createItem('0',
										  createItem('0',
														 createItem('0',
																		createItem('0',
																					  createItem('0',
																									 createItem('0',
																													createItem('0',
																																  createItem('0',
																																				 createItem('0',
																																								createItem('0',
																																											  createItem('0',
																																															 createItem('0',
																																																			createItem('0',
																																																						  createItem('0', NULL)))))))))))))));
	assert(maxOf(a, 4) == a[2]);
	deleteList(a[0]);
	deleteList(a[1]);
	deleteList(a[2]);
	deleteList(a[3]);

	a[0] = createItem('0',
							createItem('0',
										  createItem('0',
														 createItem('0',
																		createItem('0',
																					  createItem('0',
																									 createItem('0',
																													createItem('0',
																																  createItem('0',
																																				 createItem('0',
																																								createItem('0',
																																											  createItem('0',
																																															 createItem('0',
																																																			createItem('0',
																																																						  createItem('0',
																																																										 createItem('0',
																																																														createItem('0',
																																																																	  createItem('0',
																																																																					 createItem('0',
																																																																									createItem('0',
																																																																												  createItem('0',
																																																																																 createItem('1', NULL))))))))))))))))))))));
	a[1] = createItem('1',
							createItem('0',
										  createItem('0',
														 createItem('0',
																		createItem('0',
																					  createItem('0',
																									 createItem('0',
																													createItem('0',
																																  createItem('0',
																																				 createItem('0',
																																								createItem('0',
																																											  createItem('0',
																																															 createItem('0',
																																																			createItem('0',
																																																						  createItem('0',
																																																										 createItem('0',
																																																														createItem('0',
																																																																	  createItem('0',
																																																																					 createItem('0',
																																																																									createItem('0',
																																																																												  createItem('0',
																																																																																 createItem('1', NULL))))))))))))))))))))));
	assert(maxOf(a, 2) == a[1]);
	deleteList(a[0]);
	deleteList(a[1]);

	a[0] = createItem('3',
							createItem('2',
										  createItem('1', NULL)));
	a[1] = createItem('6',
							createItem('5',
										  createItem('4', NULL)));
	a[2] = createItem('9',
							createItem('c',
										  createItem('b',
														 createItem('9',
																		createItem('9', NULL)))));
	assert(maxOf(a, 3) == NULL);
	deleteList(a[0]);
	deleteList(a[1]);
	deleteList(a[2]);

	return 0;
}

#endif /* __PROGTEST__ */
