#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>

// ---------------------------------------------------------------------------------------------------------------------
// ---------------------------------------------------------------------------------------------------------------------

/**
 * @brief
 * Represents a node in a linked list for polynomial terms.
 *
 * This structure holds the multiplier and power of a polynomial term, and a pointer to the next node in the list.
 */
typedef struct TItem
{
	struct TItem *m_Next;
	int m_Mul;
	int m_Pow;
} TITEM;

// ---------------------------------------------------------------------------------------------------------------------

/**
 * @brief
 * Creates a new linked list item with the specified multiplier and power.
 *
 * Allocates memory for a new TITEM and initializes its multiplier, power, and next pointer.
 *
 * @param mul - The multiplier of the polynomial term.
 * @param pow - The power of the polynomial term.
 * @param next - Pointer to the next item in the list.
 * @return Pointer to the newly created item.
 */
TITEM *createItem(int mul, int pow, TITEM *next)
{
	TITEM *n = (TITEM *)malloc(sizeof(*n));
	n->m_Mul = mul;
	n->m_Pow = pow;
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
 * Gets the length of the linked list if it is sorted by power in ascending order and multipliers are non-zero.
 *
 * Counts the number of nodes in the list, returning 0 if any node violates the sorting order or has a zero multiplier.
 *
 * @param x - Pointer to the head of the list.
 * @return The length of the list if valid, 0 otherwise.
 */
int getLen(TITEM *x)
{
	int len = 0;
	while (x)
	{
		if ((x->m_Next && x->m_Pow >= x->m_Next->m_Pow) || (x->m_Next && x->m_Mul == 0))
			return 0;
		++len;
		x = x->m_Next;
	}
	return len;
}

// ---------------------------------------------------------------------------------------------------------------------

/**
 * @brief
 * Copies a linked list.
 *
 * Creates a new list that is a copy of the given list.
 *
 * @param x - Pointer to the head of the list to be copied.
 * @param res - Pointer to the pointer where the new list will be stored.
 */
void copyList(TITEM *x, TITEM **res)
{
	TITEM *tmp_res;
	int len = 0;
	while (x)
	{
		TITEM *tmp = createItem(x->m_Mul, x->m_Pow, NULL);
		if (!len)
		{
			*res = tmp; tmp_res = tmp;
			++len; x = x->m_Next;
			continue;
		}
		++len; tmp_res->m_Next = tmp; 
		x = x->m_Next; tmp_res = tmp_res->m_Next;
	}
}

// ---------------------------------------------------------------------------------------------------------------------

/**
 * @brief
 * Processes a node and inserts it into the result list at the correct position.
 *
 * Inserts a node with the given multiplier and power into the result list, combining terms with the same power.
 *
 * @param mul - The multiplier of the polynomial term.
 * @param pow - The power of the polynomial term.
 * @param res - Pointer to the pointer of the result list.
 */
void processNode(int mul, int pow, TITEM **res)
{
	TITEM *tmp = *res;
	int len = 0;
	while (tmp)
	{
		if (!len && pow < tmp->m_Pow)
		{
			*res = createItem(mul, pow, tmp);
			tmp = *res;
			break;
		}
		if (pow == tmp->m_Pow)
		{
			tmp->m_Mul = mul + tmp->m_Mul;
			break;
		}
		if (tmp->m_Next)
		{
			if (tmp->m_Pow < pow && tmp->m_Next->m_Pow > pow)
			{
				TITEM *tmp_next = tmp->m_Next;
				tmp->m_Next = createItem(mul, pow, tmp_next);
				break;
			}
		}
		if (!(tmp->m_Next) && tmp->m_Pow < pow)
		{
			tmp->m_Next = createItem(mul, pow, NULL);
			break;
		}
		++len; tmp = tmp->m_Next;
	}
}

// ---------------------------------------------------------------------------------------------------------------------

/**
 * @brief
 * Sums the terms of the polynomial linked list and stores the result in the result list.
 *
 * Traverses the given list and processes each node to insert it into the result list.
 *
 * @param x - Pointer to the head of the list to be summed.
 * @param res - Pointer to the pointer of the result list.
 */
void getSum(TITEM *x, TITEM **res)
{
	while (x)
	{
		processNode(x->m_Mul, x->m_Pow, res);
		x = x->m_Next;
	}
}

// ---------------------------------------------------------------------------------------------------------------------

/**
 * @brief
 * Removes terms with a zero multiplier from the result list.
 *
 * Traverses the result list and deletes nodes with a zero multiplier.
 *
 * @param res - Pointer to the pointer of the result list.
 */
void deleteShit(TITEM **res)
{
	TITEM *tmp = *res;
	int len = 0;
	while (tmp->m_Next)
	{
		if (!len && tmp->m_Mul == 0)
		{
			*res = tmp->m_Next;
			free(tmp);
			tmp = *res;
			continue;
		}
		if (tmp->m_Next->m_Next && tmp->m_Next->m_Mul == 0)
		{
			TITEM *tmp_next = tmp->m_Next->m_Next;
			free(tmp->m_Next);
			tmp->m_Next = tmp_next;
			tmp = tmp->m_Next;
			continue;
		}
		if (!(tmp->m_Next->m_Next) && tmp->m_Next->m_Mul == 0)
		{
			free(tmp->m_Next);
			tmp->m_Next = NULL;
			continue;
		}
		++len; tmp = tmp->m_Next;
	}
}

// ---------------------------------------------------------------------------------------------------------------------

/**
 * @brief
 * Adds two polynomial linked lists and returns the result.
 *
 * Sums the terms of the two given lists and returns the resulting polynomial list.
 *
 * @param a - Pointer to the head of the first polynomial list.
 * @param b - Pointer to the head of the second polynomial list.
 * @return Pointer to the head of the resulting polynomial list, or NULL if any list is invalid.
 */
TITEM *addPoly(TITEM *a, TITEM *b)
{
	int a_len = getLen(a), b_len = getLen(b);
	if (!a_len || !b_len)
		return NULL;
	
	TITEM *res;
	(a_len >= b_len) ? copyList(a, &res) : copyList(b, &res);
	(a_len >= b_len) ? getSum(b, &res) : getSum(a, &res);

	deleteShit(&res);

	if (!(res->m_Next) || res->m_Mul == 0)
		res->m_Pow = 0;
	
	// TITEM *tmp = res;
	// while (tmp)
	// {
	// 	printf("%d %d\n", tmp->m_Mul, tmp->m_Pow);
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

	a = createItem(1, 0, createItem(9, 1, createItem(5, 2, createItem(-3, 3, NULL))));
	b = createItem(2, 0, createItem(-4, 1, createItem(-6, 2, createItem(15, 3, NULL))));
	res = addPoly(a, b);
	assert(res->m_Mul == 3);
	assert(res->m_Pow == 0);
	assert(res->m_Next->m_Mul == 5);
	assert(res->m_Next->m_Pow == 1);
	assert(res->m_Next->m_Next->m_Mul == -1);
	assert(res->m_Next->m_Next->m_Pow == 2);
	assert(res->m_Next->m_Next->m_Next->m_Mul == 12);
	assert(res->m_Next->m_Next->m_Next->m_Pow == 3);
	assert(res->m_Next->m_Next->m_Next->m_Next == NULL);
	deleteList(res);
	deleteList(a);
	deleteList(b);

	// -----------------------------------------------------------------------------------------------------------------

	a = createItem(3, 0, createItem(2, 1, createItem(9, 3, NULL)));
	b = createItem(7, 0, createItem(4, 2, createItem(-1, 3, NULL)));
	res = addPoly(a, b);
	assert(res->m_Mul == 10);
	assert(res->m_Pow == 0);
	assert(res->m_Next->m_Mul == 2);
	assert(res->m_Next->m_Pow == 1);
	assert(res->m_Next->m_Next->m_Mul == 4);
	assert(res->m_Next->m_Next->m_Pow == 2);
	assert(res->m_Next->m_Next->m_Next->m_Mul == 8);
	assert(res->m_Next->m_Next->m_Next->m_Pow == 3);
	assert(res->m_Next->m_Next->m_Next->m_Next == NULL);
	deleteList(res);
	deleteList(a);
	deleteList(b);

	// -----------------------------------------------------------------------------------------------------------------

	a = createItem(3, -1, createItem(2, 5, createItem(9, 6, NULL)));
	b = createItem(7, 0, createItem(4, 2, createItem(-1, 3, NULL)));
	res = addPoly(a, b);
	assert(res->m_Mul == 3);
	assert(res->m_Pow == -1);
	assert(res->m_Next->m_Mul == 7);
	assert(res->m_Next->m_Pow == 0);
	assert(res->m_Next->m_Next->m_Mul == 4);
	assert(res->m_Next->m_Next->m_Pow == 2);
	assert(res->m_Next->m_Next->m_Next->m_Mul == -1);
	assert(res->m_Next->m_Next->m_Next->m_Pow == 3);
	assert(res->m_Next->m_Next->m_Next->m_Next->m_Mul == 2);
	assert(res->m_Next->m_Next->m_Next->m_Next->m_Pow == 5);
	assert(res->m_Next->m_Next->m_Next->m_Next->m_Next->m_Mul == 9);
	assert(res->m_Next->m_Next->m_Next->m_Next->m_Next->m_Pow == 6);
	assert(res->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next == NULL);
	deleteList(res);
	deleteList(a);
	deleteList(b);

	// -----------------------------------------------------------------------------------------------------------------

	a = createItem(1, 0, createItem(9, 1, createItem(5, 40, createItem(-3, 70, NULL))));
	b = createItem(-1, 0, createItem(-9, 1, createItem(-5, 40, createItem(3, 70, NULL))));
	res = addPoly(a, b);
	assert(res->m_Mul == 0);
	assert(res->m_Pow == 0);
	deleteList(res);
	deleteList(a);
	deleteList(b);

	// -----------------------------------------------------------------------------------------------------------------

	a = createItem(-5, 0, createItem(10, 4, NULL));
	b = createItem(5, 0, createItem(6, 1, NULL));
	res = addPoly(a, b);
	assert(res->m_Mul == 6);
	assert(res->m_Pow == 1);
	assert(res->m_Next->m_Mul == 10);
	assert(res->m_Next->m_Pow == 4);
	assert(res->m_Next->m_Next == NULL);
	deleteList(res);
	deleteList(a);
	deleteList(b);

	// -----------------------------------------------------------------------------------------------------------------

	a = createItem(0, 0, NULL);
	b = createItem(0, 0, NULL);
	res = addPoly(a, b);
	assert(res->m_Mul == 0);
	assert(res->m_Pow == 0);
	assert(res->m_Next == NULL);
	deleteList(res);
	deleteList(a);
	deleteList(b);

	// -----------------------------------------------------------------------------------------------------------------

	a = createItem(1, 0, createItem(2, 1, NULL));
	b = createItem(-1, 0, createItem(-2, 1, NULL));
	res = addPoly(a, b);
	assert(res->m_Mul == 0);
	assert(res->m_Pow == 0);
	assert(res->m_Next == NULL);
	deleteList(res);
	deleteList(a);
	deleteList(b);

	// -----------------------------------------------------------------------------------------------------------------

	a = createItem(7, 7, createItem(-20, 12, NULL));
	b = createItem(-40, 1, createItem(-100, 20, NULL));
	res = addPoly(a, b);
	assert(res->m_Mul == -40);
	assert(res->m_Pow == 1);
	assert(res->m_Next->m_Mul == 7);
	assert(res->m_Next->m_Pow == 7);
	assert(res->m_Next->m_Next->m_Mul == -20);
	assert(res->m_Next->m_Next->m_Pow == 12);
	assert(res->m_Next->m_Next->m_Next->m_Mul == -100);
	assert(res->m_Next->m_Next->m_Next->m_Pow == 20);
	assert(res->m_Next->m_Next->m_Next->m_Next == NULL);
	deleteList(res);
	deleteList(a);
	deleteList(b);

	// -----------------------------------------------------------------------------------------------------------------

	a = createItem(0, 0, createItem(100, 5, NULL));
	b = createItem(-40, 0, createItem(6, 20, NULL));
	res = addPoly(a, b);
	assert(res == NULL);
	deleteList(res);
	deleteList(a);
	deleteList(b);

	// -----------------------------------------------------------------------------------------------------------------

	a = createItem(5, 5, createItem(4, 4, NULL));
	b = createItem(6, 0, createItem(9, 20, NULL));
	res = addPoly(a, b);
	assert(res == NULL);
	deleteList(res);
	deleteList(a);
	deleteList(b);

	// -----------------------------------------------------------------------------------------------------------------

	a = createItem(3, 1, createItem(6, 2, createItem(4, 3, createItem(5, 4, NULL))));
	b = NULL;
	res = addPoly(a, b);
	assert(res == NULL);
	deleteList(res);
	deleteList(a);
	deleteList(b);

	// -----------------------------------------------------------------------------------------------------------------

	return 0;
}
