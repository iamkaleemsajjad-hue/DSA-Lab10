// Name: Muhammad Kaleem Sajjad
// CMS: 544147
// Class: BSCS-15E
// Lab 10 - Task 2: AVL Insertion and Rotations

#include <iostream>
using namespace std;

// node structure, height is needed for AVL balance checks
struct Node {
    int data;
    Node* left;
    Node* right;
    int height;
};

// creates a new node with height 1 and no children
Node* newNode(int val) {
    Node* n = new Node();
    n->data = val;
    n->left = nullptr;
    n->right = nullptr;
    n->height = 1;
    return n;
}

// returns 0 if node is null, otherwise returns its height
int getHeight(Node* n) {
    if (n == nullptr)
        return 0;
    return n->height;
}

// updates height based on left and right child heights
void updateHeight(Node* n) {
    if (n == nullptr)
        return;
    int lh = getHeight(n->left);
    int rh = getHeight(n->right);
    n->height = 1 + (lh > rh ? lh : rh);
}

// balance factor is left height minus right height
int getBalance(Node* n) {
    if (n == nullptr)
        return 0;
    return getHeight(n->left) - getHeight(n->right);
}

// right rotation used for LL imbalance
Node* rightRotate(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    // perform the rotation
    x->right = y;
    y->left = T2;

    // update y first because it is now the lower node
    updateHeight(y);
    updateHeight(x);

    return x;
}

// left rotation used for RR imbalance
Node* leftRotate(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    // perform the rotation
    y->left = x;
    x->right = T2;

    // update x first because it is now the lower node
    updateHeight(x);
    updateHeight(y);

    return y;
}

// inserts a value and rebalances the tree if needed
Node* insertAVL(Node* root, int val) {
    if (root == nullptr)
        return newNode(val);

    if (val < root->data)
        root->left = insertAVL(root->left, val);
    else if (val > root->data)
        root->right = insertAVL(root->right, val);
    else
        return root; // duplicates are ignored

    // update height on the way back up
    updateHeight(root);
    int balance = getBalance(root);

    // LL case: single right rotation
    if (balance > 1 && val < root->left->data)
        return rightRotate(root);

    // RR case: single left rotation
    if (balance < -1 && val > root->right->data)
        return leftRotate(root);

    // LR case: left rotation on child then right rotation on root
    if (balance > 1 && val > root->left->data) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // RL case: right rotation on child then left rotation on root
    if (balance < -1 && val < root->right->data) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

// prints root, left, right order
void preorder(Node* root) {
    if (root == nullptr)
        return;
    cout << root->data << " ";
    preorder(root->left);
    preorder(root->right);
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

// helper to run a test case and print results
void runTest(const char* label, int arr[], int size) {
    cout << "\n" << label << endl;
    Node* root = nullptr;
    for (int i = 0; i < size; i++)
        root = insertAVL(root, arr[i]);
    cout << "Preorder: ";
    preorder(root);
    cout << endl;
    cout << "Inorder:  ";
    inorder(root);
    cout << endl;
    freeTree(root);
}

int main() {
    // LL case: needs a single right rotation
    int a[] = {30, 20, 10};
    runTest("Sequence a: 30 20 10 - LL right rotation", a, 3);

    // RR case: needs a single left rotation
    int b[] = {10, 20, 30};
    runTest("Sequence b: 10 20 30 - RR left rotation", b, 3);

    // LR case: needs left rotation then right rotation
    int c[] = {30, 10, 20};
    runTest("Sequence c: 30 10 20 - LR double rotation", c, 3);

    // RL case: needs right rotation then left rotation
    int d[] = {10, 30, 20};
    runTest("Sequence d: 10 30 20 - RL double rotation", d, 3);

    return 0;
}
