#ifndef __PROGTEST__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>

typedef struct TItem
{
	struct TItem *m_Next;
	int m_Mul;
	int m_Pow;
} TITEM;

TITEM *createItem(int mul, int pow, TITEM *next)
{
	TITEM *n = (TITEM *)malloc(sizeof(*n));
	n->m_Mul = mul;
	n->m_Pow = pow;
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

void getSum(TITEM *x, TITEM **res)
{
	while (x)
	{
		processNode(x->m_Mul, x->m_Pow, res);
		x = x->m_Next;
	}
}

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

#ifndef __PROGTEST__

int main(int argc, char *argv[])
{
	TITEM *a, *b, *res;

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

	a = createItem(1, 0, createItem(9, 1, createItem(5, 40, createItem(-3, 70, NULL))));
	b = createItem(-1, 0, createItem(-9, 1, createItem(-5, 40, createItem(3, 70, NULL))));
	res = addPoly(a, b);
	assert(res->m_Mul == 0);
	assert(res->m_Pow == 0);
	deleteList(res);
	deleteList(a);
	deleteList(b);

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

	a = createItem(0, 0, NULL);
	b = createItem(0, 0, NULL);
	res = addPoly(a, b);
	assert(res->m_Mul == 0);
	assert(res->m_Pow == 0);
	assert(res->m_Next == NULL);
	deleteList(res);
	deleteList(a);
	deleteList(b);

	a = createItem(1, 0, createItem(2, 1, NULL));
	b = createItem(-1, 0, createItem(-2, 1, NULL));
	res = addPoly(a, b);
	assert(res->m_Mul == 0);
	assert(res->m_Pow == 0);
	assert(res->m_Next == NULL);
	deleteList(res);
	deleteList(a);
	deleteList(b);

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

	a = createItem(0, 0, createItem(100, 5, NULL));
	b = createItem(-40, 0, createItem(6, 20, NULL));
	res = addPoly(a, b);
	assert(res == NULL);
	deleteList(res);
	deleteList(a);
	deleteList(b);

	a = createItem(5, 5, createItem(4, 4, NULL));
	b = createItem(6, 0, createItem(9, 20, NULL));
	res = addPoly(a, b);
	assert(res == NULL);
	deleteList(res);
	deleteList(a);
	deleteList(b);

	a = createItem(3, 1, createItem(6, 2, createItem(4, 3, createItem(5, 4, NULL))));
	b = NULL;
	res = addPoly(a, b);
	assert(res == NULL);
	deleteList(res);
	deleteList(a);
	deleteList(b);

	return 0;
}

#endif /* __PROGTEST__ */
