// Name: Muhammad Kaleem Sajjad
// CMS: 544147
// Class: BSCS-15E
// Lab 10 - Task 3: AVL Insertion and Deletion

#include <iostream>
using namespace std;

// node structure for AVL tree
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

// returns 0 if null, otherwise returns height of the node
int getHeight(Node* n) {
    if (n == nullptr)
        return 0;
    return n->height;
}

// recalculates height using left and right child heights
void updateHeight(Node* n) {
    if (n == nullptr)
        return;
    int lh = getHeight(n->left);
    int rh = getHeight(n->right);
    n->height = 1 + (lh > rh ? lh : rh);
}

// balance factor = left height minus right height
int getBalance(Node* n) {
    if (n == nullptr)
        return 0;
    return getHeight(n->left) - getHeight(n->right);
}

// right rotation for LL imbalance
Node* rightRotate(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    x->right = y;
    y->left = T2;

    // y is now lower so update it first
    updateHeight(y);
    updateHeight(x);

    return x;
}

// left rotation for RR imbalance
Node* leftRotate(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    y->left = x;
    x->right = T2;

    // x is now lower so update it first
    updateHeight(x);
    updateHeight(y);

    return y;
}

// inserts a value and fixes balance on the way back up
Node* insertAVL(Node* root, int val) {
    if (root == nullptr)
        return newNode(val);

    if (val < root->data)
        root->left = insertAVL(root->left, val);
    else if (val > root->data)
        root->right = insertAVL(root->right, val);
    else
        return root; // ignore duplicates

    updateHeight(root);
    int balance = getBalance(root);

    if (balance > 1 && val < root->left->data)
        return rightRotate(root);
    if (balance < -1 && val > root->right->data)
        return leftRotate(root);
    if (balance > 1 && val > root->left->data) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    if (balance < -1 && val < root->right->data) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

// returns the smallest node in a subtree
Node* findMin(Node* root) {
    while (root->left != nullptr)
        root = root->left;
    return root;
}

// checks balance and applies the correct rotation if needed
Node* rebalance(Node* root) {
    updateHeight(root);
    int balance = getBalance(root);

    if (balance > 1) {
        // left child balance >= 0 means single right rotation is enough
        if (getBalance(root->left) >= 0)
            return rightRotate(root);
        else {
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }
    }

    if (balance < -1) {
        // right child balance <= 0 means single left rotation is enough
        if (getBalance(root->right) <= 0)
            return leftRotate(root);
        else {
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }
    }

    return root;
}

// deletes a node and rebalances at every ancestor on the way back up
Node* deleteAVL(Node* root, int val) {
    if (root == nullptr) {
        cout << "Key " << val << " not found." << endl;
        return nullptr;
    }

    if (val < root->data)
        root->left = deleteAVL(root->left, val);
    else if (val > root->data)
        root->right = deleteAVL(root->right, val);
    else {
        // leaf node
        if (root->left == nullptr && root->right == nullptr) {
            delete root;
            return nullptr;
        }
        // only right child
        else if (root->left == nullptr) {
            Node* temp = root->right;
            delete root;
            return temp;
        }
        // only left child
        else if (root->right == nullptr) {
            Node* temp = root->left;
            delete root;
            return temp;
        }
        // two children: replace with inorder successor then delete it
        else {
            Node* succ = findMin(root->right);
            root->data = succ->data;
            root->right = deleteAVL(root->right, succ->data);
        }
    }

    if (root == nullptr)
        return nullptr;

    // fix balance at this node before returning
    return rebalance(root);
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

// prints key, height and balance factor for every node
void printInfo(Node* root) {
    if (root == nullptr)
        return;
    printInfo(root->left);
    cout << "Key: " << root->data << "  Height: " << root->height << "  Balance: " << getBalance(root) << endl;
    printInfo(root->right);
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

    // insert all values into the AVL tree
    int vals[] = {30, 20, 40, 10, 25, 50, 5};
    for (int v : vals)
        root = insertAVL(root, v);

    cout << "After inserting 30, 20, 40, 10, 25, 50, 5:" << endl;
    cout << "Preorder: ";
    preorder(root);
    cout << "\nInorder:  ";
    inorder(root);
    cout << "\nNode info:" << endl;
    printInfo(root);

    // delete 50, no rotation needed here
    cout << "\nDeleting 50:" << endl;
    root = deleteAVL(root, 50);
    cout << "Preorder: ";
    preorder(root);
    cout << "\nInorder:  ";
    inorder(root);
    cout << "\nNode info:" << endl;
    printInfo(root);

    // delete 40, check if any ancestor becomes unbalanced
    cout << "\nDeleting 40:" << endl;
    root = deleteAVL(root, 40);
    cout << "Preorder: ";
    preorder(root);
    cout << "\nInorder:  ";
    inorder(root);
    cout << "\nNode info:" << endl;
    printInfo(root);

    // test missing key
    root = deleteAVL(root, 99);

    // test empty tree
    Node* empty = nullptr;
    empty = deleteAVL(empty, 5);

    // test single node tree
    Node* single = newNode(100);
    single = deleteAVL(single, 100);
    if (single == nullptr)
        cout << "\nSingle node deleted, tree is now empty." << endl;

    // test where heavy child has balance factor 0, single rotation is correct
    cout << "\nHeavy child balance = 0 test:" << endl;
    Node* t = nullptr;
    t = insertAVL(t, 20);
    t = insertAVL(t, 10);
    t = insertAVL(t, 30);
    t = insertAVL(t, 5);
    t = insertAVL(t, 15);
    cout << "Before deleting 30:" << endl;
    printInfo(t);
    // deleting 30 makes root left heavy, left child has balance 0 so single right rotation works
    t = deleteAVL(t, 30);
    cout << "After deleting 30, single right rotation applied:" << endl;
    printInfo(t);
    freeTree(t);

    freeTree(root);
    return 0;
}
