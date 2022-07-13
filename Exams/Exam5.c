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

typedef struct NumItem 
{
	char *n_Num;
	struct NumItem *n_Next;
} NUMITEM;

NUMITEM *createNumItem(int size_Num)
{
	NUMITEM *item = (NUMITEM *)malloc(sizeof(NUMITEM));
	item->n_Num = (char *)malloc(size_Num * sizeof(char) + 1);
	item->n_Num[size_Num] = '\0';
	item->n_Next = NULL;

	return item;
}

void appendNumItem(NUMITEM **n, int size_Num)
{
	NUMITEM *new_item = createNumItem(size_Num);
	new_item->n_Next = *n;
	*n = new_item;
}

void deleteNumItemList(NUMITEM *n)
{
	while (n)
	{
		NUMITEM *tmp = n->n_Next;
		free(n->n_Num); free(n);
		n = tmp;
	}
}

void getNum(TITEM *x, NUMITEM **n)
{
	char *arr;
	int len = 0, mem = 1000;

	if (!x)
		arr = NULL;
	else
	{
		arr = (char *)malloc(mem * sizeof(char));
		while (x)
		{
			if (!isdigit(x->m_Digit))
			{
				free(arr);
				deleteNumItemList(*n);
				*n = NULL;
				return;
			}
			if (len == mem - 1)
				arr = (char *)realloc(arr, (mem *= 1.5) * sizeof(char));

			arr[len++] = x->m_Digit;
			x = x->m_Next;
		}
	}

	if (arr)
	{
		if (!*n)
			*n = createNumItem(len);
		else
			appendNumItem(n, len);

		NUMITEM *tmp = *n;
		for (int i = 0, j = (len - 1); i < len; i++, j--)
			tmp->n_Num[i] = arr[j];
		free(arr);
	}
}

int compareNumItemList(NUMITEM *n)
{
	NUMITEM *tmp = n;
	int itemindex = 0, maxindex = 0;
	while (tmp->n_Next)
	{
		tmp = tmp->n_Next;
		int zerocnt = 0, zerocntn = 0;
		if (tmp->n_Num[0] == '0')
		{
			while (tmp->n_Num[zerocnt] == '0')
				zerocnt++;
		}
		if (n->n_Num[0] == '0')
		{
			while (n->n_Num[zerocntn] == '0')
				zerocntn++;
		}
		if ((int)strlen(tmp->n_Num) - zerocnt > (int)strlen(n->n_Num) - zerocntn)
		{
			maxindex = itemindex + 1;
			n = tmp;
		}
		if ((int)strlen(tmp->n_Num) - zerocnt == (int)strlen(n->n_Num) - zerocntn)
		{
			if (strcmp(tmp->n_Num + zerocnt, n->n_Num + zerocntn) > 0)
			{
				maxindex = itemindex + 1;
				n = tmp;
			}
		}
		itemindex++;
	}
	return maxindex;
}

TITEM *maxOf(TITEM **x, int nr)
{
	NUMITEM *numlist = NULL;
	if (*x)
	{
		for (int i = (nr - 1); i >= 0; i--)
		{
			getNum(*(x + i), &numlist);
			if (!numlist)
				break;
		}
		if (numlist)
		{
			int max = compareNumItemList(numlist);
			deleteNumItemList(numlist);
			return *(x + max);
		}
	}
	return NULL;
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
