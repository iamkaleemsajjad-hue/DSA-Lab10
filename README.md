# Lab 10 - BST Deletion and AVL Trees

**Name:** Muhammad Kaleem Sajjad  
**CMS:** 544147  
**Class:** BSCS-15E  
**Course:** Data Structures and Algorithms  
**Instructor:** Sara Tariq Sheikh  
**Lab Engineer:** Hassan Mohtashim  
**Date:** 16th November 2026  

---

## About This Lab

This lab covers two main topics. First is deletion in a Binary Search Tree where we handle three different cases depending on how many children the node has. Second is AVL trees which are self-balancing BSTs that use rotations to stay balanced after every insertion and deletion.

---

## Files

| File | Description |
|------|-------------|
| Q1.cpp | BST deletion with all three cases |
| Q2.cpp | AVL insertion with all four rotation types |
| Q3.cpp | AVL deletion with rebalancing at every ancestor |

---

## How to Compile and Run

Make sure you have g++ installed. Open terminal in the lab folder and run:

```
g++ -std=c++11 -o Q1 Q1.cpp
./Q1

g++ -std=c++11 -o Q2 Q2.cpp
./Q2

g++ -std=c++11 -o Q3 Q3.cpp
./Q3
```

Each file compiles and runs independently.

---

## Task Details

### Q1 - BST Deletion

Inserts 50, 30, 70, 20, 40, 60, 80, 65 into an empty BST then deletes three nodes one by one.

- Delete 20 which is a leaf node, just remove it
- Delete 60 which has one child, replace it with that child
- Delete 50 which has two children, replace it with inorder successor

Inorder traversal is printed after each deletion to verify the result. Edge cases tested are missing key, empty tree and a single node tree.

### Q2 - AVL Insertion and Rotations

Tests all four AVL rotation cases using separate trees.

- Sequence 30, 20, 10 triggers LL imbalance, fixed with right rotation
- Sequence 10, 20, 30 triggers RR imbalance, fixed with left rotation
- Sequence 30, 10, 20 triggers LR imbalance, fixed with left then right rotation
- Sequence 10, 30, 20 triggers RL imbalance, fixed with right then left rotation

Preorder and inorder traversals are printed for each case.

### Q3 - AVL Deletion

Inserts 30, 20, 40, 10, 25, 50, 5 into an AVL tree then deletes nodes and checks balance after each one.

- Delete 50 which is a leaf, no rotation needed
- Delete 40 which may cause imbalance at an ancestor

After each deletion the program prints preorder traversal, inorder traversal and node details including key, height and balance factor. Rotations during deletion are chosen based on the balance factor of the heavy child, not the deleted value.

Edge cases tested are missing key, empty tree, single node and a case where the heavy child has balance factor 0 which still needs only a single rotation.

---

## Key Concepts Used

- BST deletion with leaf, one child and two children cases
- Inorder successor to replace a node with two children
- AVL height calculation using height = 1 + max of left and right heights
- Balance factor = left height minus right height
- LL, RR, LR and RL rotations with correct height updates
- Memory cleanup using delete and recursive freeTree function

---

## Notes

- Duplicate values are ignored during insertion
- height of null is treated as 0
- All allocated memory is freed before the program exits
