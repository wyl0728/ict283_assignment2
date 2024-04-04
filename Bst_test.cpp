#include "Bst.h"
#include <iostream>
#include <string>

// Test case for insertion and traversal methods
void testInsertAndTraversal() {
    Bst<int> tree;
    // Inserting elements into the tree
    tree.Insert(15);
    tree.Insert(10);
    tree.Insert(20);
    tree.Insert(8);
    tree.Insert(12);
    tree.Insert(17);
    tree.Insert(25);

    // Display the elements in InOrder traversal (should be sorted order)
    std::cout << "InOrder Traversal: ";
    tree.InOrderTraversal([](const int& data) { std::cout << data << " "; });
    std::cout << std::endl;

    // Display the elements in PreOrder traversal
    std::cout << "PreOrder Traversal: ";
    tree.PreOrderTraversal([](const int& data) { std::cout << data << " "; });
    std::cout << std::endl;

    // Display the elements in PostOrder traversal
    std::cout << "PostOrder Traversal: ";
    tree.PostOrderTraversal([](const int& data) { std::cout << data << " "; });
    std::cout << std::endl;
}

// Test case for the remove functionality
void testRemove() {
    Bst<int> tree;
    // Building the tree
    tree.Insert(15);
    tree.Insert(10);
    tree.Insert(20);
    tree.Insert(8);
    tree.Insert(12);
    tree.Insert(17);
    tree.Insert(25);

    std::cout << "Original Tree InOrder Traversal: ";
    tree.InOrderTraversal([](const int& data) { std::cout << data << " "; });
    std::cout << std::endl;

    // Remove a node with one child and check tree structure after removal
    tree.Remove(10);

    std::cout << "After Removing 10, InOrder Traversal: ";
    tree.InOrderTraversal([](const int& data) { std::cout << data << " "; });
    std::cout << std::endl;
}

// Test cases for checking the copy and move constructors
void testCopyAndMove() {
    Bst<int> originalTree;
    // Populate the original tree
    originalTree.Insert(10);
    originalTree.Insert(5);
    originalTree.Insert(15);

    // Testing the copy constructor
    Bst<int> copiedTree = originalTree;
    std::cout << "Copied Tree InOrder Traversal: ";
    copiedTree.InOrderTraversal([](const int& data) { std::cout << data << " "; });
    std::cout << std::endl;

    // Testing the move constructor
    Bst<int> movedTree = std::move(originalTree);
    std::cout << "Moved Tree InOrder Traversal: ";
    movedTree.InOrderTraversal([](const int& data) { std::cout << data << " "; });
    std::cout << std::endl;
}

int main() {
    std::cout << "Testing Insert and Traversal" << std::endl;
    testInsertAndTraversal();

    std::cout << "\nTesting Remove" << std::endl;
    testRemove();

    std::cout << "\nTesting Copy and Move Constructors" << std::endl;
    testCopyAndMove();

    return 0;
}
