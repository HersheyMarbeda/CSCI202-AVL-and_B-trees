# CSCI 202: AVL and B-Tree Programming Assignment

## Assignment Description
1) Implement a B-Tree Insert function within a program
2) Implement an AVL Tree Insert function within a program

## My Method 
1) I created a B-Tree class with an insert function that inserts a value into the tree.
   The insert function will recursively call itself to insert the value into the correct location.
   If the node is full, the function will split the node and insert the median value into the parent node.
   
2) I created an AVL Tree class with an insert function that inserts a value into the tree.
    The insert function will recursively call itself to insert the value into the correct location.
    The function will then balance the tree by rotating the nodes as needed.
