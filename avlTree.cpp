// AVLTreeDS.cpp : Defines the entry point for the console application.
//

/************************************************************************************
* AVL Tree Data Structure.?
	AVL tree is a self-balancing Binary Search Tree (BST) where the difference between
Heights of left and right subtrees cannot be more than one for all nodes.
Example:
			   d
       /  \
		  b    f
		 / \  /  \
		a   c e   g

Why AVL Trees?
	Most of the BST operations (e.g., search, max, min, insert, delete.. etc) take O(h)
time where h is the height of the BST. The cost of these operations mat become O(n) for
skewed Binary tree. If we make sure that height of the tree remains O(Logn) after every
insertion and deletion, then we can guarantee an upper bound of O(Logn) for all these
operations. The height of an AVL tree is always O(Logn) where n is the no of nodes in the tree.

Implementation of AVL tree?
Following implementation uses the recursive BST insert to insert new node.
	1. Perform the normal BST insertion
	2. The current node must be one of the ancestors of the newly inserted node, Update
		the height of the current node.
	3. Get the balance factor (left subtree height - right subtree height) of the current node.
	4. If balance factor is greater than 1, then the current node is unbalanced and we are
		either in Left Left case of Left Right case. To check whether it is left left case 
		or not, compare the newly inserted key with the key in left subtree root.
	5. If balance factor is less than -1, then the current node is unbalanced and we are 
		either in Right Right case or Right-Left case. To check whether it is Right Right
		case or not, compare the newly inserted key with the key in right subtree root.
************************************************************************************/

#include "stdafx.h"
#include <iostream>
using namespace std;

// An AVL tree node
class avlNode
{
public:
	int key;
	avlNode *left;
	avlNode *right;
	int height;
};

/* A utility function to get the height of the tree */
int height(avlNode *node)
{
	if (node == nullptr)
		return 0;
	return node->height;
}

/* A utility function to get maximum of two integers */
int max(int a, int b)
{
	return (a > b) ? a : b;
}

/* Helper function that allocates a new node with the given key and
 * nullptr left and right pointers. */
avlNode* newNode(int key)
{
	avlNode* node = new avlNode();
	node->key = key;
	node->left = nullptr;
	node->right = nullptr;
	node->height = 1; // new node is initially added at leaf
	return(node);
}

/* A utility function to right rotate subtree rooted with ynode */
avlNode *rightRotate(avlNode *ynode)
{
	avlNode *xnode = ynode->left;
	avlNode *temp = xnode->right;

	// Perform rotation
	xnode->right = ynode;
	ynode->left = temp;

	// Update heights
	ynode->height = max(height(ynode->left), height(ynode->right)) + 1;
	xnode->height = max(height(xnode->left), height(xnode->right)) + 1;

	// Return new root
	return xnode;
}

/* A utility function to left rotate subtree rooted with xnode */
avlNode *leftRotate(avlNode *xnode)
{
	avlNode *ynode = xnode->right;
	avlNode *temp = ynode->left;

	// Perform rotation
	ynode->left = xnode;
	xnode->right = temp;

	// Update heights
	xnode->height = max(height(xnode->left), height(xnode->right)) + 1;
	ynode->height = max(height(ynode->left), height(ynode->right)) + 1;

	// Return new root
	return ynode;
}

// Get Balance factor of node
int getBalance(avlNode *node)
{
	if (node == nullptr)
		return 0;
	return height(node->left) - height(node->right);
}

/* Recursive function to insert a key in the subtree rooted with node and
returns the new root of the subtree. */
avlNode* insert(avlNode* node, int key)
{
	/* 1. Perform the normal BST insertion */
	if (node == NULL)
		return(newNode(key));

	if (key < node->key)
		node->left = insert(node->left, key);
	else if (key > node->key)
		node->right = insert(node->right, key);
	else // Equal keys are not allowed in BST
		return node;

	/* 2. Update height of this ancestor node */
	node->height = 1 + max(height(node->left),
		height(node->right));

	/* 3. Get the balance factor of this ancestor
	node to check whether this node became
	unbalanced */
	int balance = getBalance(node);

	// If this node becomes unbalanced, then
	// there are 4 cases

	// Left Left Case
	if (balance > 1 && key < node->left->key)
		return rightRotate(node);

	// Right Right Case
	if (balance < -1 && key > node->right->key)
		return leftRotate(node);

	// Left Right Case
	if (balance > 1 && key > node->left->key)
	{
		node->left = leftRotate(node->left);
		return rightRotate(node);
	}

	// Right Left Case
	if (balance < -1 && key < node->right->key)
	{
		node->right = rightRotate(node->right);
		return leftRotate(node);
	}

	/* return the (unchanged) node pointer */
	return node;
}

/* Given a non-empty binary search tree, return the node
   with minimum key value found in that tree. Note that
   the entire tree does not need to be searched.*/
avlNode* minValueNode(avlNode* root)
{
	avlNode* node = root;
	// loop down to find the leftmost leaf
	while (node->left != NULL)
		node = node->left;
	return node;
}

/* Recursion function to delete a node with given key from
   subtree with given root. It returns root of the modified subtree*/
avlNode* deleteNode(avlNode* root, int key)
{
	// 1. Perform standard BST delete
	if (root == NULL)
		return root;
	// If the key to be deleted smaller than the root's key
	// then it lies in the leftsubtree
	if (key < root->key)
		root->left = deleteNode(root->left, key);
	// If the key to be deleted greater than the root's key
	// then it lies in rightsubtree
	else if (key > root->key)
		root->right = deleteNode(root->right, key);
	// if the key is same as root's key then this node to be deleted
	else
	{
		// node with only one child or no child
		if (root->left || root->right)
		{
			avlNode* temp = root->left ? root->left : root->right;
			// no child
			if (temp == NULL)
			{
				temp = root;
				root = NULL;
			}
			else // one child
			{
				*root = *temp; // copy the content of child
				delete temp;
			}
		}
		else
		{
			// Node with two childs: get the inorder successor
			avlNode* temp = minValueNode(root->right);
			// copy the inorder successor's data to this node
			root->key = temp->key;
			// Delete the inorder successor
			root->right = deleteNode(root->right, temp->key);
		}
	}

	// if the tree had only one node then return
	if (root == NULL)
		return root;
	// 2. Update height of the current node
	root->height = 1 + max(height(root->left), height(root->right));

	// 3. get the balance factor of the node
	int balance = getBalance(root);

	// if the node becomes unbalanced, then there are 4 cases
	// Left Left case
	if (balance > 1 && getBalance(root->left) >= 0)
		return rightRotate(root);
	// Left Right case
	if (balance > 1 && getBalance(root->left) < 0)
	{
		root->left = leftRotate(root->left);
		return rightRotate(root);
	}

	// Right Right case
	if (balance < -1 && getBalance(root->right) <= 0)
		return leftRotate(root);
	// Right Left case
	if (balance < -1 && getBalance(root->right) > 0)
	{
		root->right = rightRotate(root->right);
		return leftRotate(root);
	}
	return root;
}


// A utility function to print inOrder traversal of 
// the tree, The function also prints height of every node
void inOrder(avlNode *root)
{
	if (root != NULL)
	{
		inOrder(root->left);
		cout << root->key << " ";
		inOrder(root->right);
	}
}

// Driver Code
int main()
{
	avlNode *root = NULL;

	/* Constructing tree given in
	the above figure */
	root = insert(root, 9);
	root = insert(root, 5);
	root = insert(root, 10);
	root = insert(root, 0);
	root = insert(root, 6);
	root = insert(root, 11);
	root = insert(root, -1);
	root = insert(root, 1);
	root = insert(root, 2);

/* The constructed AVL Tree would be
	      9
	     / \
	    1  10
	   / \   \
	   0  5   11
	  /   / \
	-1   2  6
*/

	cout << "Inorder traversal of the "
		"constructed AVL tree is: ";
	inOrder(root);
	cout << endl;
	root = deleteNode(root, 10);

	/* The AVL Tree after deletion of 10
	    1
	   / \
	  0   9
	 /    / \
	-1    5  11
	/ \
 2    6
	*/
	cout << "Inorder traversal of the "
		"constructed AVL tree is: ";
	inOrder(root);
	cout << endl;
	return 0;
}
