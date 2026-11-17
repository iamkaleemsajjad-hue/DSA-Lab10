// Name: Muhammad Kaleem Sajjad
// CMS: 544147
// Class: BSCS-15E
// Lab 10 - Task 1: BST Deletion

#include <iostream>
using namespace std;

// node structure for BST
struct Node {
    int data;
    Node* left;
    Node* right;
    int height;
};

// creates a new node and sets default values
Node* newNode(int val) {
    Node* n = new Node();
    n->data = val;
    n->left = nullptr;
    n->right = nullptr;
    n->height = 1;
    return n;
}

// inserts a value into the BST recursively
Node* insertBST(Node* root, int val) {
    if (root == nullptr)
        return newNode(val);
    if (val < root->data)
        root->left = insertBST(root->left, val);
    else if (val > root->data)
        root->right = insertBST(root->right, val);
    return root;
}

// returns the smallest node in a subtree
Node* findMin(Node* root) {
    while (root->left != nullptr)
        root = root->left;
    return root;
}

// deletes a node from BST and handles all three cases
Node* deleteBST(Node* root, int val) {
    if (root == nullptr) {
        cout << "Key " << val << " not found." << endl;
        return nullptr;
    }

    if (val < root->data)
        root->left = deleteBST(root->left, val);
    else if (val > root->data)
        root->right = deleteBST(root->right, val);
    else {
        // case 1: leaf node, just delete it
        if (root->left == nullptr && root->right == nullptr) {
            delete root;
            return nullptr;
        }
        // case 2: only right child exists
        else if (root->left == nullptr) {
            Node* temp = root->right;
            delete root;
            return temp;
        }
        // case 2: only left child exists
        else if (root->right == nullptr) {
            Node* temp = root->left;
            delete root;
            return temp;
        }
        // case 3: two children, find inorder successor and copy its value
        else {
            Node* succ = findMin(root->right);
            root->data = succ->data;
            root->right = deleteBST(root->right, succ->data);
        }
    }
    return root;
}

// prints nodes in sorted order
void inorder(Node* root) {
    if (root == nullptr)
        return;
    inorder(root->left);
    cout << root->data << " ";
    inorder(root->right);
}

// frees all nodes to avoid memory leaks
void freeTree(Node* root) {
    if (root == nullptr)
        return;
    freeTree(root->left);
    freeTree(root->right);
    delete root;
}

int main() {
    Node* root = nullptr;

    // insert all values into the BST
    int vals[] = {50, 30, 70, 20, 40, 60, 80, 65};
    for (int v : vals)
        root = insertBST(root, v);

    cout << "Inorder after insertion: ";
    inorder(root);
    cout << endl;

    // delete 20 which is a leaf node
    root = deleteBST(root, 20);
    cout << "After deleting 20: ";
    inorder(root);
    cout << endl;

    // delete 60 which has one child
    root = deleteBST(root, 60);
    cout << "After deleting 60: ";
    inorder(root);
    cout << endl;

    // delete 50 which has two children
    root = deleteBST(root, 50);
    cout << "After deleting 50: ";
    inorder(root);
    cout << endl;

    // test deleting a key that is not in the tree
    root = deleteBST(root, 99);

    // test deleting from an empty tree
    Node* empty = nullptr;
    empty = deleteBST(empty, 10);

    // test a tree with only one node
    Node* single = newNode(100);
    single = deleteBST(single, 100);
    if (single == nullptr)
        cout << "Single node deleted, tree is now empty." << endl;

    freeTree(root);
    return 0;
}
