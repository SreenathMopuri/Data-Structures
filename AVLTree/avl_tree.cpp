/*
 * AVL Tree Implementation using C++
 */

#include <iostream>
using namespace std;

class TreeNode
{
public:
    int data;
    TreeNode *left, *right;
    TreeNode() {
        left = right = NULL;
    }
};

class AVLTree {
private:
    TreeNode* root;
public:
    /* Default constructor */
    AVLTree(): root(NULL) {}
    TreeNode* LeftRotation(TreeNode* node);
    TreeNode* RightRotation(TreeNode* node);
    TreeNode* LeftRightRotation(TreeNode* node);
    TreeNode* RightLeftRotation(TreeNode* node);

    int height(TreeNode* node);
    int MAX(int, int);

    void create();
    TreeNode* insert(TreeNode* node, int);
    void inorder(TreeNode* node);
    void display();
};

// Left Rotation
TreeNode* AVLTree::LeftRotation(TreeNode* parent) {
    TreeNode* tmp;
    tmp = parent->left;
    parent->left = tmp->right;
    tmp->right = parent;
    return tmp;
}

// Right Roration
TreeNode* AVLTree::RightRotation(TreeNode* parent) {
    TreeNode* tmp = parent->right;
    parent->right = tmp->left;
    tmp->left = parent;
    return tmp;
}

// Left Right Rotation
TreeNode* AVLTree::LeftRightRotation(TreeNode* parent) {
    parent->left = RightRotation(parent->left);
    parent = LeftRotation(parent);
    return parent;
}

// Right Left Rotation
TreeNode* AVLTree::RightLeftRotation(TreeNode* parent) {
    parent->left = LeftRotation(parent->right);
    parent = RightRotation(parent);
    return parent;
}

// Height of the tree
int AVLTree::height(TreeNode* tmp) {
    if (tmp == NULL) {
        return -1;
    }
    if (tmp->left == NULL && tmp->right == NULL) {
        return 0;
    }

    return (1 + MAX(height(tmp->left), height(tmp->right)));
}

void AVLTree::create() {
    int val;
    char ch;
    do {
        cout << "Enter Number: ";
        cin >> val;
        root = insert(root, val);
        cout << "continue: ";
        cin >> ch;
    } while(ch == 'y');
    cout << endl;
}

TreeNode* AVLTree::insert(TreeNode* tmp, int val) {
    if (tmp == NULL) {
        tmp = new TreeNode;
        tmp->data = val;
    } else {
        if (val < tmp->data) {
            tmp->left = insert(tmp->left, val);
            if ((height(tmp->left) - height(tmp->right) == 2)) {
                if (val < tmp->left->data)
                    tmp = LeftRotation(tmp);
                else
                    tmp = LeftRightRotation(tmp);
            }
        } else {
            tmp->right = insert(tmp->right, val);
            if ( (height(tmp->left) - height(tmp->right) == -2) ) {
                if (val > tmp->right->data)
                    tmp = RightRotation(tmp);
                else
                    tmp = RightLeftRotation(tmp);

      } else {
            tmp->right = insert(tmp->right, val);
            if ( (height(tmp->left) - height(tmp->right) == -2) ) {
                if (val > tmp->right->data)
                    tmp = RightRotation(tmp);
                else
                    tmp = RightLeftRotation(tmp);
            }
        }
    }
    return tmp;
}

void AVLTree::inorder(TreeNode* tmp) {
    if (tmp != NULL) {
        inorder(tmp->left);
        cout << "\n" << tmp->data;
        inorder(tmp->right);
    }
}

void AVLTree::display() {
    cout << "Data in Sorted way: ";
    inorder(root);
}
int AVLTree::MAX(int a, int b) {
    if (a > b) {
        return a;
    } else {
        return b;
    }
}

int main() {
    AVLTree t;
    t.create();
    t.display();
    cout << endl;
    return 0;
}

