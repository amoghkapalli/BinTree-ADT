// file BinTree.h
// Binary Search Tree ADT
#ifndef _BINTREE_H_
#define _BINTREE_H_
#include "NodeData.h"
#include <iostream>
#include <string>
using namespace std;
//---------------------------------------------------------------------------
// Binary Search Tree ADT
//   -- Allows for NodeData objects to be added to a binary search tree
//   -- NodeData objects can also be retrieved 
//   -- BinTrees can be compared through the == and != operators
//   -- The assignment operator allows two BinTrees to be set equal
//   -- 
//
// Implementation and assumptions:
//   -- Implemented using a node structure which has a left and right
//   -- The node stores a nodedata object too with the actual value
//   -- All the methods are implemented recursively
//   -- Testing for this was done using the driver which read inputs
//---------------------------------------------------------------------------
class BinTree {
    // Overloaded << prints the whole Binary Search Tree
    // The list is printed in a inorder traversal (left, root, right)
    // This is implemented recursively and takes a BinTree parameter
    friend ostream& operator<<(ostream& out, const BinTree& a);
    public:
        // No-arg constructor which sets the root to 0
        BinTree();
        // Copy constructor taking in a BinTree object and copying it to *this
        // Copy process is also implemented using the = operator
        BinTree(const BinTree& a);
        // Destructor which uses a helper makeEmpty function
        // Helper function deletes all of the values in the nodes and the left
        // and right connection
        ~BinTree();
        
        //Operator overloads
        BinTree& operator=(const BinTree & other);
        bool operator==(const BinTree& other);
        bool operator!=(const BinTree& other);

        //isEmpty function to check if the tree is empty
        bool isEmpty() const;
        //makeEmpty helper function to delete the tree
        void makeEmpty();

        //insert method to add Nodes to tree given the NodeData
        bool insert(NodeData *val);
        //retrieves a NodeData value if in the tree
        bool retrieve(const NodeData &toFind, NodeData*& found) const;
        
        //returns a NodeData's sibling in the tree
        bool getSibling(const NodeData& parent, NodeData& found) const;
        //returns a NodeData's parent in the tree
        bool getParent(const NodeData& parent, NodeData& found) const;

        //Fills a NodeData array with values from the BinTree
        void bstreeToArray(NodeData* tree[]);
        //Creates a BinTree from a array of NodeDatas
        void arrayToBSTree(NodeData* tree[]);
        //displays the tree
        void displaySideways() const;

        
        
    private:
        // Node structure
        struct Node{		
            Node* left;		
            Node* right;
            NodeData* data;
	    };

        Node* root;

        //RECURSIVE HELPER FUNCTIONS
        void copyHelper(Node* &copy, Node* orig)const;
        
        void operatorPrintHelper(Node *curr) const;
        void makeEmptyHelper(Node* current); 
        Node* nodeCopy(NodeData *in); 
        void retrieveHelper(const NodeData& toFind, NodeData*& found,
         Node* curr) const; 
    
        bool equalHelper(Node* destination, Node *copy);
        bool insertHelper(Node* &destination, NodeData *val);
        void assignmentHelper(Node* &destination, Node *other);
        bool siblingHelper(Node * node, const NodeData& parent,
         NodeData& found) const;
         bool parentHelper(Node * node, const NodeData& parent,
         NodeData& found) const;
        void bstreeToArrayHelper(Node* current, NodeData* arr[], int &val);
        void arrayToBSTreeHelper(Node* &current, NodeData* array[],
        int low,int high);


        void sidewaysHelper(Node*, int) const;
    
};
#endif
