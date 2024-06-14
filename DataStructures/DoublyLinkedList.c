#include <stdio.h>
#include <stdlib.h>

// ---------------------------------------------------------------------------------------------------------------------
// ---------------------------------------------------------------------------------------------------------------------

/**
 * @brief
 * Represents a node in a doubly linked list.
 *
 * This structure holds an integer data value and pointers to the next and previous nodes in the list.
 */
typedef struct TNode
{
	int data;
	struct TNode *next;
	struct TNode *prev;
} TNODE;

// ---------------------------------------------------------------------------------------------------------------------

/**
 * @brief
 * Creates a new node with the specified data.
 *
 * Allocates memory for a new TNODE and initializes its data, next, and prev pointers.
 *
 * @param set_data - The data value to be stored in the new node.
 * @return Pointer to the newly created node.
 */
TNODE *createNode(int set_data)
{
	TNODE *node = (TNODE *)malloc(sizeof(TNODE));
	node->data = set_data;
	node->next = NULL;
	node->prev = NULL;

	return node;
}

// ---------------------------------------------------------------------------------------------------------------------

/**
 * @brief
 * Appends a new node with the specified data to the head of the list.
 *
 * Creates a new node and inserts it at the beginning of the list.
 *
 * @param head - Pointer to the head of the list.
 * @param set_data - The data value to be inserted.
 */
void appendHead(TNODE **head, int set_data)
{
	TNODE *new_node = createNode(set_data);
	new_node->next = *head;
	new_node->next->prev = new_node;
	*head = new_node;
}

// ---------------------------------------------------------------------------------------------------------------------

/**
 * @brief
 * Appends a new node with the specified data to the tail of the list.
 *
 * Creates a new node and inserts it at the end of the list.
 *
 * @param tail - Pointer to the tail of the list.
 * @param set_data - The data value to be inserted.
 */
void appendTail(TNODE **tail, int set_data)
{
	TNODE *new_node = createNode(set_data);
	new_node->prev = *tail;
	new_node->prev->next = new_node;
	*tail = new_node;
}

// ---------------------------------------------------------------------------------------------------------------------

/**
 * @brief
 * Appends a new node with the specified data into the list.
 *
 * Depending on the data value, the new node is inserted at the correct position to maintain order.
 *
 * @param head - Pointer to the head of the list.
 * @param tail - Pointer to the tail of the list.
 * @param set_data - The data value to be inserted.
 */
void appendNode(TNODE **head, TNODE **tail, int set_data)
{
	TNODE *tmp_head = *head, *tmp_tail = *tail;
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
					TNODE *new_node = createNode(set_data);
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
					TNODE *new_node = createNode(set_data);
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

// ---------------------------------------------------------------------------------------------------------------------

/**
 * @brief
 * Deletes a node with the specified data from the list.
 *
 * Searches for the node with the given data value and removes it from the list.
 *
 * @param head - Pointer to the head of the list.
 * @param tail - Pointer to the tail of the list.
 * @param delete_data - The data value of the node to be deleted.
 */
void deleteNode(TNODE **head, TNODE **tail, int delete_data)
{
	TNODE *tmp_head = *head, *tmp_tail = *tail;
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

// ---------------------------------------------------------------------------------------------------------------------

/**
 * @brief
 * Deletes the entire list.
 *
 * Frees all nodes in the list and sets the head and tail pointers to NULL.
 *
 * @param head - Pointer to the head of the list.
 * @param tail - Pointer to the tail of the list.
 */
void deleteList(TNODE **head, TNODE **tail)
{
	TNODE *tmp = *head;
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

// ---------------------------------------------------------------------------------------------------------------------
// ---------------------------------------------------------------------------------------------------------------------

int main(void)
{
	TNODE *head, *tail;
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
