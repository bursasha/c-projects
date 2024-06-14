#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

// ---------------------------------------------------------------------------------------------------------------------
// ---------------------------------------------------------------------------------------------------------------------

/**
 * @brief
 * Represents a node in a binary search tree.
 *
 * This structure holds an integer data value and pointers to the left and right children nodes.
 */
typedef struct BSTNODE
{
	int l_Data;
	struct BSTNODE *l_Left;
	struct BSTNODE *l_Right;
} BSTNODE;

// ---------------------------------------------------------------------------------------------------------------------

/**
 * @brief
 * Creates a new node with the specified data.
 *
 * Allocates memory for a new BSTNODE and initializes its data, left, and right pointers.
 *
 * @param set_data - The data value to be stored in the new node.
 * @return Pointer to the newly created node.
 */
BSTNODE *createNode (int set_data)
{
	BSTNODE *new_node = (BSTNODE *)malloc(sizeof(BSTNODE));
	new_node->l_Data = set_data;
	new_node->l_Left = NULL;
	new_node->l_Right = NULL;

	return new_node;
}

// ---------------------------------------------------------------------------------------------------------------------

/**
 * @brief
 * Inserts a new node with the specified data into the binary search tree.
 *
 * Recursively traverses the tree to find the correct position for the new node based on binary search tree properties.
 *
 * @param root - Pointer to the root of the tree.
 * @param set_data - The data value to be inserted.
 * @return Pointer to the root of the tree after insertion.
 */
BSTNODE *appendNode (BSTNODE *root, int set_data)
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

// ---------------------------------------------------------------------------------------------------------------------

/**
 * @brief
 * Searches for a node with the specified data in the binary search tree.
 *
 * Recursively traverses the tree to find a node with the given data value.
 *
 * @param root - Pointer to the root of the tree.
 * @param search_data - The data value to search for.
 * @return 1 if the data is found, 0 otherwise.
 */
int searchNode (BSTNODE *root, int search_data)
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

// ---------------------------------------------------------------------------------------------------------------------
// ---------------------------------------------------------------------------------------------------------------------

int main (void)
{
	BSTNODE *root = NULL;

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
