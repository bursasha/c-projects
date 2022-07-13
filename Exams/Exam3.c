#ifndef __PROGTEST__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>

typedef struct TItem
{
	int m_Val;
	struct TItem *m_Next;
} TITEM;

TITEM *createItem(int val, TITEM *next)
{
	TITEM *n = (TITEM *)malloc(sizeof(*n));
	n->m_Val = val;
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

int validateList(TITEM *x)
{
	int valid = 0;
	while (x)
	{
		if (x->m_Next && x->m_Val > x->m_Next->m_Val)
			return 0;
		x = x->m_Next; ++valid;
	}
	return valid;
}

void connectNode(TITEM **res, TITEM **x)
{
	TITEM *tmp = *res, *to_connect = *x;
	int in_head = 1;
	*x = to_connect->m_Next;
	while (tmp)
	{
		if (in_head && to_connect->m_Val <= tmp->m_Val) // присоединение к голове
		{
			to_connect->m_Next = *res;
			*res = to_connect;
			break;
		}
		if (!(tmp->m_Next) && to_connect->m_Val >= tmp->m_Val) // присоединение к хвосту
		{
			to_connect->m_Next = NULL;
			tmp->m_Next = to_connect;
			break;
		}
		if (tmp->m_Next && (tmp->m_Val < to_connect->m_Val) && (to_connect->m_Val <= tmp->m_Next->m_Val)) // присоединение между двумя нодами
		{
			TITEM *tmp_next = tmp->m_Next;
			to_connect->m_Next = tmp_next;
			tmp->m_Next = to_connect;
			break;
		}
		tmp = tmp->m_Next; in_head = 0;
	}
}

TITEM *connectLists(TITEM **x, int nr)
{
	for (int i = 0; i < nr; i++)
		if (!validateList(x[i]))
			return NULL;

	TITEM *res = x[0];
	for (int j = 1; j < nr; j++)
	{
		while (x[j])
			connectNode(&res, &x[j]);
	}

	TITEM *tmp = res;
	while (tmp)
	{
		printf("(%d) -> ", tmp->m_Val);
		tmp = tmp->m_Next;
	}
	printf("NULL\n");

	return res;
}

#ifndef __PROGTEST__

int main(int argc, char *argv[])
{
	TITEM *a[5], *res;

	a[0] = createItem(1, createItem(5, createItem(19, createItem(24, NULL))));
	a[1] = createItem(3, createItem(7, createItem(17, createItem(25, NULL))));
	res = connectLists(a, 2);
	assert(res->m_Val == 1);
	assert(res->m_Next->m_Val == 3);
	assert(res->m_Next->m_Next->m_Val == 5);
	assert(res->m_Next->m_Next->m_Next->m_Val == 7);
	assert(res->m_Next->m_Next->m_Next->m_Next->m_Val == 17);
	assert(res->m_Next->m_Next->m_Next->m_Next->m_Next->m_Val == 19);
	assert(res->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Val == 24);
	assert(res->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Val == 25);
	assert(res->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next == NULL);
	deleteList(res);

	a[0] = createItem(8, NULL);
	res = connectLists(a, 1);
	assert(res->m_Val == 8);
	assert(res->m_Next == NULL);
	deleteList(res);

	a[0] = createItem(-1, createItem(3, createItem(5, NULL)));
	a[1] = createItem(2, createItem(3, createItem(7, NULL)));
	res = connectLists(a, 2);
	assert(res->m_Val == -1);
	assert(res->m_Next->m_Val == 2);
	assert(res->m_Next->m_Next->m_Val == 3);
	assert(res->m_Next->m_Next->m_Next->m_Val == 3);
	assert(res->m_Next->m_Next->m_Next->m_Next->m_Val == 5);
	assert(res->m_Next->m_Next->m_Next->m_Next->m_Next->m_Val == 7);
	assert(res->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next == NULL);
	deleteList(res);

	a[0] = createItem(2, createItem(4, createItem(4, NULL)));
	a[1] = createItem(5, createItem(6, NULL));
	a[2] = createItem(-1, createItem(5, NULL));
	res = connectLists(a, 3);
	assert(res->m_Val == -1);
	assert(res->m_Next->m_Val == 2);
	assert(res->m_Next->m_Next->m_Val == 4);
	assert(res->m_Next->m_Next->m_Next->m_Val == 4);
	assert(res->m_Next->m_Next->m_Next->m_Next->m_Val == 5);
	assert(res->m_Next->m_Next->m_Next->m_Next->m_Next->m_Val == 5);
	assert(res->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Val == 6);
	assert(res->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next == NULL);
	deleteList(res);

	a[0] = createItem(-20, createItem(-5, createItem(-5, createItem(-5, createItem(100, NULL)))));
	a[1] = createItem(-5, createItem(50, NULL));
	a[2] = createItem(50, createItem(100, createItem(228, NULL)));
	a[3] = createItem(2048, NULL);
	a[4] = createItem(-20, createItem(-20, NULL));
	res = connectLists(a, 5);
	assert(res->m_Val == -20);
	assert(res->m_Next->m_Val == -20);
	assert(res->m_Next->m_Next->m_Val == -20);
	assert(res->m_Next->m_Next->m_Next->m_Val == -5);
	assert(res->m_Next->m_Next->m_Next->m_Next->m_Val == -5);
	assert(res->m_Next->m_Next->m_Next->m_Next->m_Next->m_Val == -5);
	assert(res->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Val == -5);
	assert(res->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Val == 50);
	assert(res->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Val == 50);
	assert(res->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Val == 100);
	assert(res->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Val == 100);
	assert(res->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Val == 228);
	assert(res->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Val == 2048);
	assert(res->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next == NULL);
	deleteList(res);

	a[0] = createItem(-2165422, createItem(2, createItem(2, createItem(2, createItem(3425555, NULL)))));
	a[1] = createItem(-3000000, NULL);
	a[2] = createItem(2, createItem(2, createItem(3425555, NULL)));
	a[3] = createItem(-3000000, NULL);
	a[4] = createItem(2, createItem(2, NULL));
	res = connectLists(a, 5);
	assert(res->m_Val == -3000000);
	assert(res->m_Next->m_Val == -3000000);
	assert(res->m_Next->m_Next->m_Val == -2165422);
	assert(res->m_Next->m_Next->m_Next->m_Val == 2);
	assert(res->m_Next->m_Next->m_Next->m_Next->m_Val == 2);
	assert(res->m_Next->m_Next->m_Next->m_Next->m_Next->m_Val == 2);
	assert(res->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Val == 2);
	assert(res->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Val == 2);
	assert(res->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Val == 2);
	assert(res->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Val == 2);
	assert(res->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Val == 3425555);
	assert(res->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Val == 3425555);
	assert(res->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next == NULL);
	deleteList(res);

	a[0] = createItem(8, createItem(11, NULL));
	a[1] = createItem(4, createItem(4, NULL));
	a[2] = createItem(-5, createItem(0, NULL));
	a[3] = createItem(2, createItem(1, NULL));
	res = connectLists(a, 4);
	assert(res == NULL);
	deleteList(res);

	a[0] = createItem(3, createItem(3, NULL));
	a[1] = createItem(4, createItem(4, NULL));
	a[2] = NULL;
	res = connectLists(a, 3);
	assert(res == NULL);
	deleteList(res);

	return 0;
}

#endif /* __PROGTEST__ */
