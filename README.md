# Data-Structures

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
    
Avl Tree implementation:
https://github.com/SreenathMopuri/Data-Structures/blob/main/avlTree.cpp
