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

#ifndef __PROGTEST__

int main(int argc, char *argv[])
{
	TITEM *a, *b, *res;

	a = createItem('x', NULL);
	b = createItem('3', NULL);
	res = addList(a, b);
	assert(res == NULL);
	deleteList(res);
	deleteList(a);
	deleteList(b);

	a = createItem('5',
						createItem('0',
									  createItem('0', NULL)));
	b = createItem('3', NULL);
	res = addList(a, b);
	assert(res == NULL);
	deleteList(res);
	deleteList(a);
	deleteList(b);

	a = createItem('3',
						createItem('4',
									  createItem('5', NULL)));
	b = createItem('0', NULL);
	res = addList(a, b);
	assert(res->m_Digit == '3');
	assert(res->m_Next->m_Digit == '4');
	assert(res->m_Next->m_Next->m_Digit == '5');
	assert(res->m_Next->m_Next->m_Next == NULL);
	deleteList(res);
	deleteList(a);
	deleteList(b);

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

	return 0;
}

#endif /* __PROGTEST__ */
