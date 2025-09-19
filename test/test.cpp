#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "AVLTree.h"

using namespace std;

// Checking for invalid commands

TEST_CASE("Invalid commands", "[commands]") {
    AVLTree tree;

    REQUIRE_THROWS(tree.processCommand("insert A11y 45679999"));  // invalid key
    REQUIRE_THROWS(tree.processCommand("remove"));               // missing args
    REQUIRE_THROWS(tree.processCommand("search "));                 // empty argument
    REQUIRE_THROWS(tree.processCommand("insert 123abc"));         // missing value
    REQUIRE_THROWS(tree.processCommand("invalid command"));      // totally invalid
}

// Insert + rotation cases

TEST_CASE("Right Rotation (LL Case)", "[rotations]") {
    AVLTree tree;
    tree.insert("A", 30);
    tree.insert("B", 20);
    tree.insert("C", 10);

    Node* root = tree.getRoot();
    REQUIRE(root->student.id == 20);    
    REQUIRE(root->left->student.id == 10); 
    REQUIRE(root->right->student.id == 30);
}

TEST_CASE("Left Rotation (RR Case)", "[rotations]") {
    AVLTree tree;
    tree.insert("A", 10);
    tree.insert("B", 20);
    tree.insert("C", 30); 

    Node* root = tree.getRoot();
    REQUIRE(root->student.id == 20);      
    REQUIRE(root->left->student.id == 10);
    REQUIRE(root->right->student.id == 30);
}

TEST_CASE("Left-Right Rotation (LR Case)", "[rotations]") {
    AVLTree tree;
    tree.insert("A", 30);
    tree.insert("B", 10);
    tree.insert("C", 20); 

    Node* root = tree.getRoot();
    REQUIRE(root->student.id == 20);       
    REQUIRE(root->left->student.id == 10);
    REQUIRE(root->right->student.id == 30);
}

TEST_CASE("Right-Left Rotation (RL Case)", "[rotations]") {
    AVLTree tree;
    tree.insert("A", 10);
    tree.insert("B", 30);
    tree.insert("C", 20); 

    Node* root = tree.getRoot();
    REQUIRE(root->student.id == 20);
    REQUIRE(root->left->student.id == 10);
    REQUIRE(root->right->student.id == 30);
}


// Insert 100, delete 10 random, verify

TEST_CASE("Bulk insert and delete", "[bulk]") {
    AVLTree tree;

    // Insert 100 nodes
    for (int i = 1; i <= 100; i++) {
        tree.insert(i);
    }
    REQUIRE(tree.size() == 100); // Will implement helper function later to have a size method

    // Delete 10 random nodes
    int toDelete[10] = {5, 12, 33, 47, 58, 69, 75, 82, 91, 100};
    for (int x : toDelete) {
        tree.remove(x);
    }
    REQUIRE(tree.size() == 90);

    // Verify in-order traversal has 90 sorted elements
    vector<int> inorder = tree.inorderTraversal();
    REQUIRE(inorder.size() == 90);
    for (size_t i = 1; i < inorder.size(); i++) {
        REQUIRE(inorder[i-1] < inorder[i]); // strictly increasing
    }
}
