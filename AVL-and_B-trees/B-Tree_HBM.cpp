/*
     Program Name: B-Tree
     
     Programmer: Hershey Marbeda
     Due Date: 12.2.24
     Last Date Updated: 12.1.24
     
     Purpose: to implement an B-tree and its operations (insertion)
 */

#include <iostream>
using namespace std;

// A BTree node
class BTreeNode
{
    int* keys;  // An array of keys
    int t;      // Minimum degree (defines the range for number of keys)
    BTreeNode** C; // An array of child pointers
    int n;
    bool leaf;
    
public:
    BTreeNode(int _t, bool _leaf);   // Constructor
    
    // A utility function to insert a new key in the subtree rooted with this node
    void insertNonFull(int k);
    
    // A utility function to split the child y of this node. i is index of y in child array C[].
    void splitChild(int i, BTreeNode* y);
    
    // A function to traverse all nodes in a subtree rooted with this node
    void traverse();
    
    // A function to search a key in the subtree rooted with this node.
    BTreeNode* search(int k);
    
        
    friend class BTree;
};

    // A BTree
class BTree
{
    BTreeNode* root; // Pointer to root node
    int t;
public:
    // Constructor
    BTree(int _t) { root = NULL; t = _t; }
    
    // Function to traverse the tree
    void traverse() { if (root != NULL) root->traverse(); }
    
    // Function to search a key in this tree
    BTreeNode* search(int k) { return (root == NULL) ? NULL : root->search(k); }
    
    // The main function that inserts a new key in this B-Tree
    void insert(int k);
};

// Constructor for BTreeNode class
BTreeNode::BTreeNode(int t1, bool leaf1)
{
        
    t = t1;
    leaf = leaf1;
    
    // Allocate memory for maximum number of possible keys and child pointers
    keys = new int[2 * t - 1];
    C = new BTreeNode*[2 * t];
    
        
    n = 0;
}

// Function to traverse all nodes in a subtree rooted with this node
void BTreeNode::traverse()
{
        
    int i;
    for (i = 0; i < n; i++)
    {
        if (leaf == false) C[i]->traverse();
        cout << " " << keys[i];
    }
    
    if (leaf == false) C[i]->traverse();
}

// Function to search key k in subtree rooted with this node
BTreeNode* BTreeNode::search(int k)
{
        
    int i = 0;
    while (i < n && k > keys[i]) i++;
    
    
    if (keys[i] == k) return this;
    
    if (leaf == true) return NULL;
    
    
    return C[i]->search(k);
}

// The main function that inserts a new key in this B-Tree
void BTree::insert(int k)
{
    // If tree is empty
    if (root == NULL)
    {
        // Allocate memory for root
        root = new BTreeNode(t, true);
        root->keys[0] = k;  // Insert key
        root->n = 1;        // Update number of keys in root
    }
    
    else
    {
           
        // If root is full, then tree grows in height
        if (root->n == 2 * t - 1)
        {
            // Allocate memory for new root
            BTreeNode* s = new BTreeNode(t, false);
            
            s->C[0] = root;
            
            s->splitChild(0, root);
            
            
            int i = 0;
            if (s->keys[0] < k) i++;
            s->C[i]->insertNonFull(k);
            
            // Change root
            root = s;
        }
        
        else
        {
            root->insertNonFull(k);
        }
    }
}

    // A utility function to insert a new key in this node
void BTreeNode::insertNonFull(int k)
{
        // Initialize index as index of rightmost element
    int i = n - 1;
    
        // If this is a leaf node
    if (leaf == true)
    {
        while (i >= 0 && keys[i] > k)
        {
            keys[i + 1] = keys[i];
            i--;
        }
        
        // Insert the new key at found location
        keys[i + 1] = k;
        n = n + 1;
    }
    
    else
        { // If this node is not leaf
               // Find the child which is going to have the new key
            while (i >= 0 && keys[i] > k) i--;
            
            // See if the found child is full
            if (C[i + 1]->n == 2 * t - 1)
            {
            // If the child is full, then split it
                splitChild(i + 1, C[i + 1]);
                
                if (keys[i + 1] < k) i++;
         }
        C[i + 1]->insertNonFull(k);
    }
}

// A utility function to split the child y of this node
void BTreeNode::splitChild(int i, BTreeNode* y)
{
        
    BTreeNode* z = new BTreeNode(y->t, y->leaf);
    z->n = t - 1;
    
   
    for (int j = 0; j < t - 1; j++) z->keys[j] = y->keys[j + t];
    
    // Copy the last t children of y to z
    if (y->leaf == false)
    {
        for (int j = 0; j < t; j++) z->C[j] = y->C[j + t];
    }
    
    
    y->n = t - 1;
    
    // create space for new child
    for (int j = n; j >= i + 1; j--) C[j + 1] = C[j];
    
    // Link the new child to this node
    C[i + 1] = z;
    
    
    for (int j = n - 1; j >= i; j--) keys[j + 1] = keys[j];
    
    // Copy the middle key of y to this node
    keys[i] = y->keys[t - 1];
    
    
    n = n + 1; // incrementation
}

    
int main()
{
    // Table Headings
    cout << string(50, '-') << endl
         << "\t\t\t\tProgam Name: B-Tree" << endl
         << string(50, '-') << endl << endl;
    
    BTree t(3); // A B-Tree with minimum degree 3
    t.insert(5);
    t.insert(20);
    t.insert(56);
    t.insert(1000);
    t.insert(909);
    t.insert(30);
    t.insert(7);
    t.insert(18);
    
    cout << "Traversal of the constructed tree is ";
    t.traverse();
    cout << endl;
    
    int k = 6;
    
    BTreeNode* result = t.search(k);
    if (result != nullptr)
    {
        cout << "Searching for " << k << ": Found" << endl;
    }
    
    else
    {
        cout << "Searching for " << k << ": Not Found" << endl;
    }
    
    k = 909;
    
    result = t.search(k);
    if (result != nullptr)
    {
        cout << "Searching for " << k << ": Found" << endl;
    }
    
    else
    {
        cout << "Searching for " << k << ": Not Found" << endl;
    }
    
    cout << endl << endl;
    return 0;
}

