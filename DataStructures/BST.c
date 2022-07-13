#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct BSTList
{
	int l_Data;
	struct BSTList *l_Left;
	struct BSTList *l_Right;
} BSTLIST;

BSTLIST *createNode (int set_data)
{
	BSTLIST *new_node = (BSTLIST *)malloc(sizeof(BSTLIST));
	new_node->l_Data = set_data;
	new_node->l_Left = NULL;
	new_node->l_Right = NULL;

	return new_node;
}

BSTLIST *appendNode (BSTLIST *root, int set_data)
{
	if (!root)
	{
		root = createNode(set_data);
		return root;
	}
	else if (set_data <= root->l_Data)
		root->l_Left = appendNode(root->l_Left, set_data);
	else
		root->l_Right = appendNode(root->l_Right, set_data);
	return root;
}

int searchNode (BSTLIST *root, int search_data)
{
	if (!root)
		return 0;
	else if (search_data == root->l_Data)
		return 1;
	else if (search_data <= root->l_Data)
		return searchNode(root->l_Left, search_data);
	else 
		return searchNode(root->l_Right, search_data);
}

void deleteNode (BSTLIST *root, int delete_data)
{
	if (delete_data == root->l_Data)
	{
		root = NULL;
	}
}

int main (void)
{
	BSTLIST *root = NULL;

	root = appendNode(root, 15);
	appendNode(root, 20);
	appendNode(root, 35);
	appendNode(root, 50);
	appendNode(root, 10);

	assert(searchNode(root, 15) == 1);
	assert(searchNode(root, 20) == 1);
	assert(searchNode(root, 35) == 1);
	assert(searchNode(root, 10) == 1);

	return 0;
}
