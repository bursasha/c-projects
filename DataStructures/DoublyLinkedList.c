#include <stdio.h>
#include <stdlib.h>

typedef struct TList
{
	int data;
	struct TList *next;
	struct TList *prev;
} TLIST;

TLIST *createNode(int set_data)
{
	TLIST *node = (TLIST *)malloc(sizeof(TLIST));
	node->data = set_data;
	node->next = NULL;
	node->prev = NULL;

	return node;
}

void appendHead(TLIST **head, int set_data)
{
	TLIST *new_node = createNode(set_data);
	new_node->next = *head;
	new_node->next->prev = new_node;
	*head = new_node;
}

void appendTail(TLIST **tail, int set_data)
{
	TLIST *new_node = createNode(set_data);
	new_node->prev = *tail;
	new_node->prev->next = new_node;
	*tail = new_node;
}

void appendNode(TLIST **head, TLIST **tail, int set_data)
{
	TLIST *tmp_head = *head, *tmp_tail = *tail;
	int mid = (tmp_tail->data - tmp_head->data) / 2;
	if (set_data < tmp_head->data)
		appendHead(head, set_data);
	if (set_data > tmp_tail->data)
		appendTail(tail, set_data);
	else
		if (tmp_head->data < set_data && set_data <= mid)
		{
			while (tmp_head->data < set_data)
			{
				if (tmp_head->next->data > set_data)
				{
					TLIST *new_node = createNode(set_data);
					new_node->next = tmp_head->next;
					tmp_head->next->prev = new_node;
					new_node->prev = tmp_head;
					tmp_head->next = new_node;
					break;
				}
				tmp_head = tmp_head->next;
			}
		}
		if (tmp_tail->data > set_data && set_data >= mid)
		{
			while (tmp_tail->data > set_data)
			{
				if (tmp_tail->prev->data < set_data)
				{
					TLIST *new_node = createNode(set_data);
					new_node->prev = tmp_tail->prev;
					tmp_tail->prev->next = new_node;
					new_node->next = tmp_tail;
					tmp_tail->prev = new_node;
					break;
				}
				tmp_tail = tmp_tail->prev;
			}
		}
}

void deleteNode(TLIST **head, TLIST **tail, int delete_data)
{
	TLIST *tmp_head = *head, *tmp_tail = *tail;
	int mid = (tmp_tail->data - tmp_head->data) / 2;
	if (tmp_head->next == NULL && tmp_head->prev == NULL)
	{
		free(tmp_head); *head = *tail = NULL;
	}
	if (tmp_head->data <= delete_data && delete_data <= mid)
	{
		if (tmp_head->data == delete_data)
		{
			*head = tmp_head->next;
			tmp_head->next->prev = NULL;
			free(tmp_head);
		}
		else
			while (tmp_head->data != delete_data)
			{
				if (tmp_head->next->data == delete_data)
				{
					tmp_head->next->next->prev = tmp_head;
					tmp_head = tmp_head->next;
					tmp_head->prev->next = tmp_head->next;
					free(tmp_head);
					break;
				}
				tmp_head = tmp_head->next;
			}
	}
	if (tmp_tail->data >= delete_data && delete_data >= mid)
	{
		if (tmp_tail->data == delete_data)
		{
			*tail = tmp_tail->prev;
			tmp_tail->prev->next = NULL;
			free(tmp_tail);
		}
		else
			while (tmp_tail->data != delete_data)
			{
				if (tmp_tail->prev->data == delete_data)
				{
					tmp_tail->prev->prev->next = tmp_tail;
					tmp_tail = tmp_tail->prev;
					tmp_tail->next->prev = tmp_tail->prev;
					free(tmp_tail);
					break;
				}
				tmp_tail = tmp_tail->prev;
			}
	}
}

void deleteList(TLIST **head, TLIST **tail)
{
	TLIST *tmp = *head;
	while (tmp != NULL)
	{
		if (tmp->next == NULL)
		{
			free(tmp);
			break;
		}
		tmp = tmp->next;
		free(tmp->prev);
	}
	*head = *tail = NULL;
}

int main(void)
{
	TLIST *head, *tail;
	head = tail = createNode(0);

	appendNode(&head, &tail, 10);
	appendNode(&head, &tail, -1);
	appendNode(&head, &tail, 1);
	appendNode(&head, &tail, 2);
	appendNode(&head, &tail, 9);
	appendNode(&head, &tail, 8);
	appendNode(&head, &tail, 1000);
	appendNode(&head, &tail, 500);

	deleteNode(&head, &tail, -1);
	deleteNode(&head, &tail, 1000);
	deleteNode(&head, &tail, 8);
	deleteNode(&head, &tail, 1);
	deleteNode(&head, &tail, 9);

	deleteList(&head, &tail);

	while (head != NULL)
	{
		printf("Data = %d\n", head->data);
		head = head->next;
	}
	printf("---------------\n");
	while (tail != NULL)
	{
		printf("Data = %d\n", tail->data);
		tail = tail->prev;
	}
	return 0;
}
