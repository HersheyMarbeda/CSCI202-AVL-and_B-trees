/*
  Program Name: AVL Tree

  Programmer: Hershey Marbeda
  Due Date: 12.2.24
  Last Date Updated: 12.1.24

  Purpose: to implement an AVL tree and its operations (insertion)
*/


#include <iostream>
#include <algorithm> // For max()
using namespace std;

// AVL Tree Node
struct Node
{
   int key, height;
   Node *left, *right;
   
   Node(int k) : key(k), height(1), left(nullptr), right(nullptr) {}
};

// Get the height of the node
inline int height(Node* node)
{
   return node ? node->height : 0;
}

// Rotate right
Node* rightRotate(Node* y)
{
   Node* x = y->left;
   y->left = x->right;
   x->right = y;
   
   y->height = 1 + max(height(y->left), height(y->right));
   x->height = 1 + max(height(x->left), height(x->right));
   return x;
}

   // Rotate left
Node* leftRotate(Node* x)
{
   Node* y = x->right;
   x->right = y->left;
   y->left = x;
   
   x->height = 1 + max(height(x->left), height(x->right));
   y->height = 1 + max(height(y->left), height(y->right));
   return y;
}

   // Get balance factor
inline int getBalance(Node* node)
{
   return height(node->left) - height(node->right);
}

   // Insert a key into the AVL tree
Node* insert(Node* node, int key)
{
   if (!node) return new Node(key);
   
   if (key < node->key)
       node->left = insert(node->left, key);
   else if (key > node->key)
       node->right = insert(node->right, key);
   else
       return node; // Duplicates not allowed
   
   node->height = 1 + max(height(node->left), height(node->right));
   int balance = getBalance(node);
   
   if (balance > 1 && key < node->left->key)
       return rightRotate(node);
   if (balance < -1 && key > node->right->key)
       return leftRotate(node);
   
   if (balance > 1 && key > node->left->key)
   {
       node->left = leftRotate(node->left);
       return rightRotate(node);
   }
   
   if (balance < -1 && key < node->right->key)
   {
       node->right = rightRotate(node->right);
       return leftRotate(node);
   }
   
   return node;
}

   // Preorder traversal
void preOrder(Node* root)
{
   if (root)
   {
       cout << root->key << " ";
       preOrder(root->left);
       preOrder(root->right);
   }
}


int main()
{
   // Table Headings
   cout << string(50, '-') << endl
   << "\t\t\t\tProgam Name: AVL Tree" << endl
   << string(50, '-') << endl << endl;
   
   Node* root = nullptr;
   
   root = insert(root, 0);
   root = insert(root, 10);
   root = insert(root, 100);
   root = insert(root, 800);
   root = insert(root, 90);
   root = insert(root, 5);
   
   cout << "Preorder traversal: ";
   preOrder(root);
   cout << endl;
   
   return 0;
}


   // Output:
/* The constructed AVL Tree would be

         10
       /   \
     100    5
    /  \      \
   90  800     0

*/


