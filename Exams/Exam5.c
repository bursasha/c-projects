#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>

// ---------------------------------------------------------------------------------------------------------------------
// ---------------------------------------------------------------------------------------------------------------------

/**
 * @brief
 * Represents a node in a linked list of digits.
 *
 * This structure holds a single character digit and a pointer to the next node in the list.
 */
typedef struct TItem
{
	struct TItem *m_Next;
	char m_Digit;
} TITEM;

// ---------------------------------------------------------------------------------------------------------------------

/**
 * @brief
 * Creates a new linked list item with the specified digit.
 *
 * Allocates memory for a new TITEM and initializes its digit and next pointer.
 *
 * @param digit - The character digit to be stored in the new item.
 * @param next - Pointer to the next item in the list.
 * @return Pointer to the newly created item.
 */
TITEM *createItem(char digit, TITEM *next)
{
	TITEM *n = (TITEM *)malloc(sizeof(*n));
	n->m_Digit = digit;
	n->m_Next = next;
	return n;
}

// ---------------------------------------------------------------------------------------------------------------------

/**
 * @brief
 * Deletes the entire linked list.
 *
 * Frees all nodes in the list and sets the head pointer to NULL.
 *
 * @param l - Pointer to the head of the list.
 */
void deleteList(TITEM *l)
{
	while (l)
	{
		TITEM *tmp = l->m_Next;
		free(l);
		l = tmp;
	}
}

// ---------------------------------------------------------------------------------------------------------------------

/**
 * @brief
 * Represents a node in a linked list of numbers.
 *
 * This structure holds a string representation of a number and a pointer to the next node in the list.
 */
typedef struct NumItem 
{
	char *n_Num;
	struct NumItem *n_Next;
} NUMITEM;

// ---------------------------------------------------------------------------------------------------------------------

/**
 * @brief
 * Creates a new linked list item for numbers with the specified size.
 *
 * Allocates memory for a new NUMITEM and initializes its number string and next pointer.
 *
 * @param size_Num - The size of the number string.
 * @return Pointer to the newly created item.
 */
NUMITEM *createNumItem(int size_Num)
{
	NUMITEM *item = (NUMITEM *)malloc(sizeof(NUMITEM));
	item->n_Num = (char *)malloc(size_Num * sizeof(char) + 1);
	item->n_Num[size_Num] = '\0';
	item->n_Next = NULL;

	return item;
}

// ---------------------------------------------------------------------------------------------------------------------

/**
 * @brief
 * Appends a new number item to the list.
 *
 * Creates a new number item and inserts it at the beginning of the list.
 *
 * @param n - Pointer to the pointer of the head of the list.
 * @param size_Num - The size of the number string.
 */
void appendNumItem(NUMITEM **n, int size_Num)
{
	NUMITEM *new_item = createNumItem(size_Num);
	new_item->n_Next = *n;
	*n = new_item;
}

// ---------------------------------------------------------------------------------------------------------------------

/**
 * @brief
 * Deletes the entire linked list of number items.
 *
 * Frees all nodes and their associated number strings in the list and sets the head pointer to NULL.
 *
 * @param n - Pointer to the head of the list.
 */
void deleteNumItemList(NUMITEM *n)
{
	while (n)
	{
		NUMITEM *tmp = n->n_Next;
		free(n->n_Num); free(n);
		n = tmp;
	}
}

// ---------------------------------------------------------------------------------------------------------------------

/**
 * @brief
 * Converts a linked list of digits to a number and stores it in a NUMITEM list.
 *
 * Traverses the digit list, constructs the number string, and appends it to the NUMITEM list.
 *
 * @param x - Pointer to the head of the digit list.
 * @param n - Pointer to the pointer of the head of the NUMITEM list.
 */
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

// ---------------------------------------------------------------------------------------------------------------------

/**
 * @brief
 * Compares the numbers in a NUMITEM list to find the largest.
 *
 * Traverses the NUMITEM list and determines which number is the largest.
 *
 * @param n - Pointer to the head of the NUMITEM list.
 * @return The index of the largest number in the list.
 */
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

// ---------------------------------------------------------------------------------------------------------------------

/**
 * @brief
 * Finds the largest number in an array of linked lists of digits.
 *
 * Converts each list to a number, compares the numbers, and returns the list with the largest number.
 *
 * @param x - Array of pointers to the head of each digit list.
 * @param nr - The number of lists.
 * @return Pointer to the head of the list with the largest number, or NULL if any list is invalid.
 */
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

// ---------------------------------------------------------------------------------------------------------------------
// ---------------------------------------------------------------------------------------------------------------------

int main(int argc, char *argv[])
{
	TITEM *a[5];

	// -----------------------------------------------------------------------------------------------------------------

	a[0] = createItem('4', createItem('3', createItem('2', createItem('1', NULL))));
	a[1] = createItem('2', createItem('3', createItem('4', createItem('5', NULL))));
	assert(maxOf(a, 2) == a[1]);
	deleteList(a[0]);
	deleteList(a[1]);

	// -----------------------------------------------------------------------------------------------------------------

	a[0] = createItem('0', createItem('0', createItem('0', createItem('1', NULL))));
	a[1] = createItem('2', createItem('0', createItem('0', createItem('1', NULL))));
	a[2] = createItem('1', createItem('0', createItem('0', createItem('1', NULL))));
	a[3] = createItem('2', createItem('0', createItem('0', createItem('1', createItem('0', createItem('0', NULL))))));
	assert(maxOf(a, 4) == a[1]);
	deleteList(a[0]);
	deleteList(a[1]);
	deleteList(a[2]);
	deleteList(a[3]);

	// -----------------------------------------------------------------------------------------------------------------

	a[0] = createItem('1', createItem('0', createItem('0', createItem('0', createItem('0', createItem('0', NULL))))));
	a[1] = createItem('0', createItem('0', createItem('1', NULL)));
	a[2] = createItem('1', createItem('0', createItem('0', createItem('0', createItem('0', createItem('9', NULL))))));
	a[3] = createItem('0', createItem('0', createItem('0', createItem('0', createItem('0', createItem('0', createItem('0', createItem('0', createItem('0', createItem('0', createItem('0', createItem('0', createItem('0', createItem('0', createItem('0', NULL)))))))))))))));
	assert(maxOf(a, 4) == a[2]);
	deleteList(a[0]);
	deleteList(a[1]);
	deleteList(a[2]);
	deleteList(a[3]);

	// -----------------------------------------------------------------------------------------------------------------

	a[0] = createItem('0', createItem('0', createItem('0', createItem('0', createItem('0', createItem('0', createItem('0', createItem('0', createItem('0', createItem('0', createItem('0', createItem('0', createItem('0', createItem('0', createItem('0', createItem('0', createItem('0', createItem('0', createItem('0', createItem('0', createItem('0', createItem('1', NULL))))))))))))))))))))));
	a[1] = createItem('1', createItem('0', createItem('0', createItem('0', createItem('0', createItem('0', createItem('0', createItem('0', createItem('0', createItem('0', createItem('0', createItem('0', createItem('0', createItem('0', createItem('0', createItem('0', createItem('0', createItem('0', createItem('0', createItem('0', createItem('0', createItem('1', NULL))))))))))))))))))))));
	assert(maxOf(a, 2) == a[1]);
	deleteList(a[0]);
	deleteList(a[1]);

	// -----------------------------------------------------------------------------------------------------------------

	a[0] = createItem('3', createItem('2', createItem('1', NULL)));
	a[1] = createItem('6', createItem('5', createItem('4', NULL)));
	a[2] = createItem('9', createItem('c', createItem('b', createItem('9', createItem('9', NULL)))));
	assert(maxOf(a, 3) == NULL);
	deleteList(a[0]);
	deleteList(a[1]);
	deleteList(a[2]);

	// -----------------------------------------------------------------------------------------------------------------

	return 0;
}
