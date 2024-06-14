#include <stdio.h>
#include <stdlib.h>

// ---------------------------------------------------------------------------------------------------------------------
// ---------------------------------------------------------------------------------------------------------------------

/**
 * @brief
 * Represents a node in a singly linked list.
 *
 * This structure holds an integer ID, a string name, and a pointer to the next node in the list.
 */
typedef struct TNode
{
	int id;
	char *name;
	struct TNode *next;
} TNODE;

// ---------------------------------------------------------------------------------------------------------------------

/**
 * @brief
 * Creates a new node with the specified ID and name.
 *
 * Allocates memory for a new TNODE and initializes its ID, name, and next pointer.
 *
 * @param set_id - The ID value to be stored in the new node.
 * @param set_name - The name to be stored in the new node.
 * @return Pointer to the newly created node.
 */
TNODE *createNode(int set_id, char *set_name)
{
	TNODE *node = (TNODE *)malloc(sizeof(TNODE));
	node -> id = set_id;
	node -> name = set_name;
	node -> next = NULL;

	return node;
}

// ---------------------------------------------------------------------------------------------------------------------

/**
 * @brief
 * Appends a new node with the specified ID and name to the start of the list.
 *
 * Creates a new node and inserts it at the beginning of the list.
 *
 * @param list - Pointer to the head of the list.
 * @param set_id - The ID value to be inserted.
 * @param set_name - The name to be inserted.
 */
void appendStart(TNODE **list, int set_id, char *set_name)
{
	TNODE *new_node = createNode(set_id, set_name);
	new_node -> next = *list;
	*list = new_node;
}

// ---------------------------------------------------------------------------------------------------------------------

/**
 * @brief
 * Appends a new node with the specified ID and name to the end of the list.
 *
 * Creates a new node and inserts it at the end of the list.
 *
 * @param list - Pointer to the head of the list.
 * @param set_id - The ID value to be inserted.
 * @param set_name - The name to be inserted.
 */
void appendEnd(TNODE **list, int set_id, char *set_name)
{
	TNODE *new_node = createNode(set_id, set_name);
	TNODE *tmp = *list;
	while(tmp -> next != NULL)
		tmp = tmp -> next;
	tmp -> next = new_node;
}

// ---------------------------------------------------------------------------------------------------------------------

/**
 * @brief
 * Appends a new node with the specified ID and name in the middle of the list.
 *
 * Creates a new node and inserts it after the node with the given previous ID.
 *
 * @param list - Pointer to the head of the list.
 * @param prev_id - The ID of the node after which the new node will be inserted.
 * @param set_id - The ID value to be inserted.
 * @param set_name - The name to be inserted.
 */
void appendMid(TNODE **list, int prev_id, int set_id, char *set_name)
{
	TNODE *tmp = *list;
	while(tmp -> next != NULL)
	{
		if(tmp -> id == prev_id)
		{
			TNODE *new_node = createNode(set_id, set_name);
			new_node -> next = tmp -> next;
			tmp -> next = new_node;
		}
		tmp = tmp -> next;
	}
}

// ---------------------------------------------------------------------------------------------------------------------

/**
 * @brief
 * Deletes a node with the specified ID from the list.
 *
 * Searches for the node with the given ID and removes it from the list.
 *
 * @param list - Pointer to the head of the list.
 * @param id_delete - The ID value of the node to be deleted.
 */
void deleteNode(TNODE **list, int id_delete)
{
	TNODE *tmp = *list, *prev = NULL;
	while (tmp -> next != NULL)
	{
		if (tmp -> id == id_delete)
		{
			if (prev == NULL)
			{
				*list = tmp -> next;
				free(tmp);
				break;
			}
			prev -> next = tmp -> next;
			free(tmp);
			break;
		}
		prev = tmp;
		if (tmp -> next -> id == id_delete && tmp -> next -> next == NULL)
		{
			prev -> next = NULL;
			free(tmp -> next);
			break;
		}
		tmp = tmp -> next;
	}
}

// ---------------------------------------------------------------------------------------------------------------------

/**
 * @brief
 * Deletes the entire list.
 *
 * Frees all nodes in the list and sets the head pointer to NULL.
 *
 * @param list - Pointer to the head of the list.
 */
void deleteList(TNODE **list)
{
	TNODE *tmp = *list, *to_delete = NULL;
	while(tmp -> next != NULL)
	{
		to_delete = tmp;
		tmp = tmp -> next;
		*list = tmp;
		free(to_delete);
		if (tmp -> next == NULL)
		{
			free(tmp);
			*list = NULL;
			break;
		}
	}
}

// ---------------------------------------------------------------------------------------------------------------------
// ---------------------------------------------------------------------------------------------------------------------

int main(void)
{
	TNODE *list = createNode(0, "Name 0");
	appendEnd(&list, 1, "Name 1");
	appendEnd(&list, 2, "Name 2");
	appendEnd(&list, 3, "Name 3");
	appendEnd(&list, 4, "Name 4");
	appendStart(&list, -1, "Name -1");
	appendStart(&list, -2, "Name -2");
	appendStart(&list, -3, "Name -3");
	appendStart(&list, -4, "Name -4");
	appendMid(&list, 0, 1000, "Name 1000");
	appendMid(&list, 1000, 5000, "Name 5000");
	deleteNode(&list, 1000);
	deleteNode(&list, 4);
	deleteNode(&list, -4);
	deleteNode(&list, -3);
	deleteNode(&list, 3);
	deleteNode(&list, 0);
	deleteList(&list);

	while(list != NULL)
	{
		printf("ID = %d, name = %s\n", list -> id, list -> name);
		list = list -> next;
	}
	return 0;
}
