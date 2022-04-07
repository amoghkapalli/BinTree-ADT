#include "BinTree.h"
using namespace std;

//----------------------------------------------------------------------------
// BinTree No-arg Constructor
// Sets the root to nullptr
BinTree::BinTree(){
    root=nullptr;
}


//----------------------------------------------------------------------------
// BinTree Copy Constructor
// Takes in a BinTree object as a parameter
// Copies the tree passed in to *this
// Uses a helper method just like the assignment operator helper
BinTree::BinTree(const BinTree &tree) {
    
    root = nullptr;
    copyHelper(root, tree.root);
    
}

void BinTree::copyHelper(Node* &copy, Node* orig)const {
    Node* copyNode = new Node;
    copyNode->data = new NodeData(*orig->data);
    copyNode->left = nullptr;
    copyNode->right = nullptr;
    copy = copyNode;
    if (orig->left)
        copyHelper(copy->left, orig->left);
    if (orig->right)
        copyHelper(copy->right, orig->right);
}


//----------------------------------------------------------------------------
// BinTree Destructor
// Deletes the tree by a helper function which makes the tree empty
// Make empty uses its own helper to go through all the terms recursively
// and delete the data along with the node setting it to nullptr
BinTree::~BinTree() {
	makeEmpty();
}

void BinTree::makeEmpty(){
    makeEmptyHelper(root);
    root=NULL;
}

void BinTree::makeEmptyHelper(Node* current){
    if (current != nullptr) {
        makeEmptyHelper(current->left);
        makeEmptyHelper(current->right);
        delete current->data;
        current->data=nullptr;
        delete current;
        current = nullptr;
    }
}


//----------------------------------------------------------------------------
// assignment operator=  
// overloaded =: checks if the parameter BinTree is the same and if not *this
// is made empty using the helper from above to make the Tree empty
// The helper then takes in the parameters data and adds it to the new tree
// The helper goes through recursively to copy over all terms
// Returns *this
BinTree& BinTree::operator=(const BinTree &other){
    if(*this == other){
        return *this;
    }
    makeEmpty();
    assignmentHelper(root, other.root);
    return *this;

}

void BinTree::assignmentHelper(Node* &destination, Node *other){
    Node* temp=new Node;
    //NodeData *newT = new NodeData(*other->data);        
    temp->data = new NodeData(*other->data);
    temp->left = nullptr;
    temp->right = nullptr;
    destination = temp;
    if(other->left){
        assignmentHelper(destination->left, other->left);
    }
    if(other->right){
        assignmentHelper(destination->right, other->right);
    }
}


//----------------------------------------------------------------------------
// operator==  
// overloaded ==: returns if the two trees are equal
// Uses a recursive helper method to check that each term 
// in both trees are equal to each other
// returns false if the sets are equal
bool BinTree::operator==(const BinTree& other){
    if (root==nullptr && other.root==nullptr)
        return true;
    else
        return equalHelper(root, other.root);
}

bool BinTree::equalHelper(Node* current, Node *otherCurrent){
    
    if (current == nullptr && otherCurrent == nullptr) 
        return true; 
    else if ((current != nullptr && otherCurrent == nullptr)||(current == nullptr && otherCurrent != nullptr))
        return false; 

    else{
        if(*current->data==*otherCurrent->data && 
        equalHelper(current->left, otherCurrent->left) 
        && equalHelper(current->right, otherCurrent->right)){
        return true;
        }
        return false;
    }
}


//----------------------------------------------------------------------------
// operator!=  
// overloaded !=: returns if the two trees are equal or not
// returns false if the sets are equal
bool BinTree::operator!=(const BinTree& other){
    return !(*this == other);
}



//----------------------------------------------------------------------------
// isEmpty
// isEmpty method checks if the BinTree is empty and has no values at the root
bool BinTree::isEmpty() const{
    if(root==nullptr) return true;
    return false;
}


//----------------------------------------------------------------------------
// insert
// insert method inserts a node into the tree and uses a helper to find the 
// appropriate insertion spot in the tree. The helper checks the value 
// to be inserted and traverses through the tree to see if its 
// less than or greater than the other values. If equal the value isnt added
bool BinTree::insert(NodeData *val){
    if(val == nullptr){
        return false;
    }
    if(root==nullptr){
        Node *repl = new Node();
        repl->data=val;
        repl->left=nullptr;
        repl->right=nullptr;
        root=repl;
        return true;
    }
    return insertHelper(root, val);
}
bool BinTree::insertHelper(Node* &destination, NodeData *val){
    if (*val < *(destination->data)){
	    if (destination->left == nullptr){
            Node *nd = new Node;
            nd->data = val;
            nd->left = nullptr;
            nd->right = nullptr;
            destination->left = nd;
			return true;
        }
		return insertHelper(destination->left, val);
	}
    if (*val > *(destination->data)){
	    if (destination->right == nullptr){
			Node *nd = new Node;
            nd->data = val;
            nd->left = nullptr;
            nd->right = nullptr;
            destination->right = nd;
			return true;
        }
		return insertHelper(destination->right, val);
	}
    return false;
}



//----------------------------------------------------------------------------
// retrieve
// retrieve method checks if a NodeData is found and if so returns a bool
// But, it also returns a pointer NodeData to the object
// Returns true if the value is found
// Uses a recursive helper to go through all the values until found 
// and if null is reached and no value was found then found is set to null
bool BinTree::retrieve(const NodeData &toFind, NodeData*& found) const{
    BinTree::Node* temp = root;
	if (temp != nullptr) {
		retrieveHelper(toFind, found, temp);
	} else {
		return false;
    }
    if(found != nullptr){
        return true;
    }
    return false;
	
}
void BinTree::retrieveHelper(const NodeData& toFind, NodeData*& found, Node* temp) const{
    if(temp==nullptr){
        found=nullptr;
    }
    else if(*temp->data==toFind){
        found=temp->data;
    }
    else if (*temp->data < toFind){
		retrieveHelper(toFind, found, temp->right);
	}
    else if (*temp->data > toFind){
		retrieveHelper(toFind, found, temp->left);
	}
    
}


//----------------------------------------------------------------------------
// getSibling
// getSibling method returns the secondary sibling if there are 2 siblings
// if the left sibling NodeData value in a tree is passed in, the right is stored 
// and true is returned.
// Recursive helper used to find the NodeData val
bool BinTree::getSibling(const NodeData& toFind, NodeData& found) const{
    BinTree::Node* temp = root;
    return siblingHelper(temp, toFind, found);
    
}

bool BinTree::siblingHelper(Node* node, const NodeData& toFind, 
NodeData& found) const{
   if (node == nullptr) { 
        return false;
    }
    if (node->left != nullptr && *node->left->data == toFind) {
        if (node->right != nullptr) { 
            found = *node->right->data;
            return true;
        }
        return false;
    } else if (node->right != nullptr && *node->right->data == toFind) { 
        if (node->left != nullptr) { 
            found = *node->left->data;
            return true;
        }
        return false;
    }
    return (siblingHelper(node->left, toFind, found) || 
        siblingHelper(node->right, toFind, found));
}


//----------------------------------------------------------------------------
// getParent
// getParent method returns the parent if the NodeData passed in is a sibling
// in the BinTree object. If so, true is returned otherwise false
// Recursive helper used to find the NodeData val
bool BinTree::getParent(const NodeData& toFind, NodeData& found) const{
    BinTree::Node* temp = root;
    NodeData* finding;
    if(temp==nullptr || !retrieve(toFind, finding)){
        return false;
    }
    else{
        return parentHelper(temp, toFind, found);
    }
}
bool BinTree::parentHelper(Node* node, const NodeData& toFind, 
NodeData& found) const{
    if(node==nullptr){
        return false;
    }
    if((*node->left->data)==toFind && (node->left)!=nullptr){
        found = *node->data;
        return true;
    }
    else if((*node->right->data)==toFind && ((node->right)!=nullptr)){
        found = *node->data;
        return true;
    }
    return(siblingHelper(node->left, toFind, found)|| siblingHelper(node->right, toFind, found));
}

//----------------------------------------------------------------------------
// bstreeToArray
// bstreeToArray method takes in a BinTree and converts it to a array by 
// adding the data vals into the array inorder
void BinTree::bstreeToArray(NodeData* arr[]) {
    int tracker = 0;
    bstreeToArrayHelper(root, arr, tracker);
    makeEmpty();
}

void BinTree::bstreeToArrayHelper(Node* current, NodeData* arr[] , int & tracker) {
    if (current != nullptr) {
		bstreeToArrayHelper(current->left, arr, tracker);
        arr[tracker] = current->data;
        current->data = nullptr;
        tracker++;
		bstreeToArrayHelper(current->right, arr, tracker);
	}
}

//----------------------------------------------------------------------------
// arrayToBSTree
// arrayToBSTree method takes in a array of NodeData and converts it into a 
// BSTTree. Since it is in order, the array is split into two and the terms 
// are added from the middle outwards recursively
void BinTree::arrayToBSTree(NodeData* array[]) {
    makeEmpty();
    int high = 0;
    for(int i=0; i<100; i++){
        if(array[i]!=nullptr){
            high++;
        }
    }
    arrayToBSTreeHelper(root, array, 0, high - 1);
}
void BinTree::arrayToBSTreeHelper(Node* &current, NodeData* array[],
 int low,int high) {
    
    if (low <= high) {
        int mid = (low + high) / 2;
        Node* node = new Node;
        NodeData* d = new NodeData(*array[mid]);
        delete array[mid];
        array[mid] = nullptr;
        node->data = d;
        node->left = nullptr;
        node->right = nullptr;
        current = node;
        arrayToBSTreeHelper(current->left, array, low, mid - 1);
        arrayToBSTreeHelper(current->right, array, mid + 1, high);
    }
}

// Overloaded << prints the whole Binary Search Tree
// The list is printed in a inorder traversal (left, root, right)
// This is implemented recursively and takes a BinTree parameter
ostream& operator<<(ostream& out, const BinTree& a){
    cout<<"root: " << a.root->data<<endl;
    a.operatorPrintHelper(a.root);
    out << endl;	
	return out;
}

void BinTree::operatorPrintHelper(Node *curr) const{
    if(curr!=NULL){
        operatorPrintHelper(curr->left);
        cout<< *curr->data << " ";
        operatorPrintHelper(curr->right);
    }
}



void BinTree::displaySideways() const {
   sidewaysHelper(root, 0);
}

void BinTree::sidewaysHelper(Node* current, int level) const {
   if (current != nullptr) {
      level++;
      sidewaysHelper(current->right, level);

      // indent for readability, same number of spaces per depth level 
      for(int i = level; i >= 0; i--) {
          cout << "        ";
      }

      cout << *current->data << endl;        // display information of object
      sidewaysHelper(current->left, level);
   }
}
