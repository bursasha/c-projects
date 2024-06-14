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
 * Gets the length of the linked list if all characters are digits.
 *
 * Counts the number of nodes in the list, returning 0 if any non-digit character is found.
 *
 * @param x - Pointer to the head of the list.
 * @return The length of the list if all characters are digits, 0 otherwise.
 */
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

// ---------------------------------------------------------------------------------------------------------------------

/**
 * @brief
 * Recursively constructs a string from the linked list digits.
 *
 * Fills the string in reverse order by recursively traversing the list.
 *
 * @param x - Pointer to the current node in the list.
 * @param num_str - The string being constructed.
 * @param num_len - The current length of the string.
 */
void getNumberRec(TITEM *x, char *num_str, int num_len)
{
	if (x->m_Next)
		getNumberRec(x->m_Next, num_str, num_len - 1);
	num_str[num_len] = x->m_Digit;
}

// ---------------------------------------------------------------------------------------------------------------------

/**
 * @brief
 * Converts the linked list digits to a string.
 *
 * Allocates memory for the string and fills it with digits from the list.
 *
 * @param x - Pointer to the head of the list.
 * @return The string representation of the linked list digits, or NULL if invalid.
 */
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

// ---------------------------------------------------------------------------------------------------------------------

/**
 * @brief
 * Finds the linked list with the maximum numeric value.
 *
 * Compares the numeric values represented by each linked list and returns the one with the largest value.
 *
 * @param x - Array of pointers to the head of each linked list.
 * @param nr - The number of linked lists.
 * @return Pointer to the head of the linked list with the maximum value, or NULL if any list is invalid.
 */
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

// ---------------------------------------------------------------------------------------------------------------------
// ---------------------------------------------------------------------------------------------------------------------

int main(int argc, char *argv[])
{
	TITEM *a[5];

	// -----------------------------------------------------------------------------------------------------------------

	a[0] = createItem('4', createItem('3', createItem('2', createItem('1', NULL))));
	a[1] = createItem('2', createItem('3', createItem('4', createItem('5', NULL))));

	// -----------------------------------------------------------------------------------------------------------------

	assert(maxOf(a, 2) == a[1]);
	deleteList(a[0]);
	deleteList(a[1]);

	// -----------------------------------------------------------------------------------------------------------------

	a[0] = createItem('0', createItem('0', createItem('0', createItem('1', NULL))));
	a[1] = createItem('2', createItem('0', createItem('0', createItem('1', NULL))));
	a[2] = createItem('1', createItem('0', createItem('0', createItem('1', NULL))));
	a[3] = createItem('2', createItem('0', createItem('0', createItem('1', createItem('0', createItem('0', NULL))))));

	// -----------------------------------------------------------------------------------------------------------------

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

	// -----------------------------------------------------------------------------------------------------------------

	assert(maxOf(a, 4) == a[2]);
	deleteList(a[0]);
	deleteList(a[1]);
	deleteList(a[2]);
	deleteList(a[3]);

	// -----------------------------------------------------------------------------------------------------------------

	a[0] = createItem('0', createItem('0', createItem('0', createItem('0', createItem('0', createItem('0', createItem('0', createItem('0', createItem('0', createItem('0', createItem('0', createItem('0', createItem('0', createItem('0', createItem('0', createItem('0', createItem('0', createItem('0', createItem('0', createItem('0', createItem('0',  createItem('1', NULL))))))))))))))))))))));
	a[1] = createItem('1', createItem('0', createItem('0', createItem('0', createItem('0', createItem('0', createItem('0', createItem('0', createItem('0', createItem('0', createItem('0', createItem('0', createItem('0', createItem('0', createItem('0', createItem('0', createItem('0', createItem('0', createItem('0', createItem('0', createItem('0', createItem('1', NULL))))))))))))))))))))));

	// -----------------------------------------------------------------------------------------------------------------

	assert(maxOf(a, 2) == a[1]);
	deleteList(a[0]);
	deleteList(a[1]);

	// -----------------------------------------------------------------------------------------------------------------

	a[0] = createItem('3', createItem('2', createItem('1', NULL)));
	a[1] = createItem('6', createItem('5', createItem('4', NULL)));
	a[2] = createItem('9', createItem('c', createItem('b', createItem('9', createItem('9', NULL)))));

	// -----------------------------------------------------------------------------------------------------------------

	assert(maxOf(a, 3) == NULL);
	deleteList(a[0]);
	deleteList(a[1]);
	deleteList(a[2]);

	// -----------------------------------------------------------------------------------------------------------------

	return 0;
}
