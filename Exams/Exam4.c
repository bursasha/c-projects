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
 * Gets the length of the linked list if all characters are digits and valid.
 *
 * Counts the number of nodes in the list, returning 0 if any non-digit character is found or if the last digit is '0'.
 *
 * @param x - Pointer to the head of the list.
 * @return The length of the list if all characters are valid digits, 0 otherwise.
 */
int getLen(TITEM *x)
{
	int len = 0;
	while (x)
	{
		if (!isdigit(x->m_Digit) || (len != 0 && !(x->m_Next) && x->m_Digit == '0'))
			return 0;
		++len;
		x = x->m_Next;
	}
	return len;
}

// ---------------------------------------------------------------------------------------------------------------------

/**
 * @brief
 * Computes the sum of two linked lists representing numbers.
 *
 * Adds the digits of the two lists and stores the result in a new linked list.
 *
 * @param a - Pointer to the head of the first list.
 * @param b - Pointer to the head of the second list.
 * @param res - Pointer to the pointer of the result list.
 */
void getSum(TITEM *a, TITEM *b, TITEM **res)
{
	TITEM *tmp_res = NULL;
	int flag = 1, over = 0;
	while (flag)
	{
		int set_digit;
		if (!tmp_res) // первый элемент суммы
		{
			set_digit = (a->m_Digit - '0') + (b->m_Digit - '0');
			if (set_digit >= 10)
			{
				set_digit -= 10; over = 1;
			}
			*res = createItem(set_digit + '0', NULL);
			tmp_res = *res;
			a = a->m_Next; b = b->m_Next;
			continue;
		}
		if (a && b) // если элементы обоих списков не NULL
		{
			set_digit = (a->m_Digit - '0') + (b->m_Digit - '0') + over;
			if (set_digit >= 10)
			{
				set_digit -= 10; over = 1;
			}
			else 
				over = 0;
			tmp_res->m_Next = createItem(set_digit + '0', NULL);
			a = a->m_Next; b = b->m_Next; tmp_res = tmp_res->m_Next;
			continue;
		}
		if (a && !b) // если а не NULL, но b NULL
		{
			set_digit = (a->m_Digit - '0') + over;
			if (set_digit >= 10)
			{
				set_digit -= 10;
				over = 1;
			}
			else
				over = 0;
			tmp_res->m_Next = createItem(set_digit + '0', NULL);
			a = a->m_Next; tmp_res = tmp_res->m_Next;
			continue;
		}
		if (!a && b) // если b не NULL, но a NULL
		{
			set_digit = (b->m_Digit - '0') + over;
			if (set_digit >= 10)
			{
				set_digit -= 10;
				over = 1;
			}
			else
				over = 0;
			tmp_res->m_Next = createItem(set_digit + '0', NULL);
			b = b->m_Next; tmp_res = tmp_res->m_Next;
			continue;
		}
		if (!a && !b) // если a и b NULL
		{
			if (over == 1)
				tmp_res->m_Next = createItem('1', NULL);
			over = 0; flag = 0;
			continue;
		}
	}
}

// ---------------------------------------------------------------------------------------------------------------------

/**
 * @brief
 * Adds two linked lists representing numbers and returns the result.
 *
 * Validates the lists and computes the sum if they are valid.
 *
 * @param a - Pointer to the head of the first list.
 * @param b - Pointer to the head of the second list.
 * @return Pointer to the head of the resulting list, or NULL if any list is invalid.
 */
TITEM *addList(TITEM *a, TITEM *b)
{
	int a_len = getLen(a), b_len = getLen(b);
	if (!a_len || !b_len)
		return NULL;
	
	TITEM *res;
	getSum(a, b, &res);

	// TITEM *tmp = res;
	// while (tmp)
	// {
	// 	printf("%c\n", tmp->m_Digit);
	// 	tmp = tmp->m_Next;
	// }

	return res;
}

// ---------------------------------------------------------------------------------------------------------------------
// ---------------------------------------------------------------------------------------------------------------------

int main(int argc, char *argv[])
{
	TITEM *a, *b, *res;

	// -----------------------------------------------------------------------------------------------------------------

	a = createItem('x', NULL);
	b = createItem('3', NULL);
	res = addList(a, b);
	assert(res == NULL);
	deleteList(res);
	deleteList(a);
	deleteList(b);

	// -----------------------------------------------------------------------------------------------------------------

	a = createItem('5', createItem('0', createItem('0', NULL)));
	b = createItem('3', NULL);
	res = addList(a, b);
	assert(res == NULL);
	deleteList(res);
	deleteList(a);
	deleteList(b);

	// -----------------------------------------------------------------------------------------------------------------

	a = createItem('3', createItem('4', createItem('5', NULL)));
	b = createItem('0', NULL);
	res = addList(a, b);
	assert(res->m_Digit == '3');
	assert(res->m_Next->m_Digit == '4');
	assert(res->m_Next->m_Next->m_Digit == '5');
	assert(res->m_Next->m_Next->m_Next == NULL);
	deleteList(res);
	deleteList(a);
	deleteList(b);

	// -----------------------------------------------------------------------------------------------------------------

	a = createItem('2', createItem('3', createItem('9', NULL)));
	b = createItem('5', createItem('3', createItem('1', NULL)));
	res = addList(a, b);
	assert(res->m_Digit == '7');
	assert(res->m_Next->m_Digit == '6');
	assert(res->m_Next->m_Next->m_Digit == '0');
	assert(res->m_Next->m_Next->m_Next->m_Digit == '1');
	assert(res->m_Next->m_Next->m_Next->m_Next == NULL);
	deleteList(res);
	deleteList(a);
	deleteList(b);

	// -----------------------------------------------------------------------------------------------------------------

	a = createItem('9', createItem('9', createItem('9', NULL)));
	b = createItem('9', createItem('0', createItem('9', createItem('9', NULL))));
	res = addList(a, b);
	assert(res->m_Digit == '8');
	assert(res->m_Next->m_Digit == '0');
	assert(res->m_Next->m_Next->m_Digit == '9');
	assert(res->m_Next->m_Next->m_Next->m_Digit == '0');
	assert(res->m_Next->m_Next->m_Next->m_Next->m_Digit == '1');
	assert(res->m_Next->m_Next->m_Next->m_Next->m_Next == NULL);
	deleteList(res);
	deleteList(a);
	deleteList(b);

	// -----------------------------------------------------------------------------------------------------------------

	a = createItem('1', createItem('7', createItem('3', createItem('6', createItem('7', createItem('5', createItem('5', NULL)))))));
	b = createItem('5', createItem('0', createItem('2', createItem('6', createItem('6', createItem('3', createItem('6', createItem('9', createItem('4', createItem('8', NULL))))))))));
	res = addList(a, b);
	assert(res->m_Digit == '6');
	assert(res->m_Next->m_Digit == '7');
	assert(res->m_Next->m_Next->m_Digit == '5');
	assert(res->m_Next->m_Next->m_Next->m_Digit == '2');
	assert(res->m_Next->m_Next->m_Next->m_Next->m_Digit == '4');
	assert(res->m_Next->m_Next->m_Next->m_Next->m_Next->m_Digit == '9');
	assert(res->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Digit == '1');
	assert(res->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Digit == '0');
	assert(res->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Digit == '5');
	assert(res->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Digit == '8');
	assert(res->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next == NULL);
	deleteList(res);
	deleteList(a);
	deleteList(b);

	// -----------------------------------------------------------------------------------------------------------------

	return 0;
}
