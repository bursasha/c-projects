#include <stdio.h>
#include <stdlib.h>

typedef struct TList 
{
	int id;
	char *name;
	struct TList *next;
} TLIST;

TLIST *createNode(int set_id, char *set_name)
{
	TLIST *node = (TLIST *)malloc(sizeof(TLIST));
	node -> id = set_id;
	node -> name = set_name;
	node -> next = NULL;

	return node;
}

void appendStart(TLIST **list, int set_id, char *set_name)
{
	TLIST *new_node = createNode(set_id, set_name);
	new_node -> next = *list;
	*list = new_node;
}

void appendEnd(TLIST **list, int set_id, char *set_name)
{
	TLIST *new_node = createNode(set_id, set_name);
	TLIST *tmp = *list;
	while(tmp -> next != NULL)
		tmp = tmp -> next;
	tmp -> next = new_node;
}

void appendMid(TLIST **list, int prev_id, int set_id, char *set_name)
{
	TLIST *tmp = *list;
	while(tmp -> next != NULL)
	{
		if(tmp -> id == prev_id)
		{
			TLIST *new_node = createNode(set_id, set_name);
			new_node -> next = tmp -> next;
			tmp -> next = new_node;
		}
		tmp = tmp -> next;
	}
}

void deleteNode(TLIST **list, int id_delete)
{
	TLIST *tmp = *list, *prev = NULL;
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

void deleteList(TLIST **list)
{
	TLIST *tmp = *list, *to_delete = NULL;
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

int main(void)
{
	TLIST *list = createNode(0, "Name 0");
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
