// Balance Factor of an AVL tree: height(left-subtree) - height(right-subtree)
// Ops:
//  Left rotation -- unbalanced from an insertion to the right's subtree
//  Right rotation -- unbalanced from an insertion to the left's subtree
//  Left-Right rotation -- Left rotation followed by a right rotation
//  Right-Left rotation -- Right rotation followed by a left rotation

#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
  int data;
  int height;
  struct node* left;
  struct node* right;
}Node;

// Utility function to get the height of a tree
int height(Node* n)
{
  if(n == NULL)
    return 0;
  return n->height;
}

int max(int a, int b)
{
  return (a > b) ? a:b;
}

Node* create_node(int data)
{
  Node* new = (Node*) malloc(sizeof(Node));
  new->data = data;
  new->left = NULL;
  new->right = NULL;
  new->height = 1; // new node is initially added at the leaf
}

// Utility function to rotate a subtree. 
Node* rightRotate(Node* n)
{
  Node* l = n->left;
  Node* r = l->right;

  // l becomes the new root
  l->right = n;
  n->left = r;

  // update their heights
  n->height = max(height(n->left), height(n->right))+1;
  l->height = max(height(l->left), height(l->right))+1;

  //return the new root
  return l;
}

// Utility function to right rotate a subtree. 
Node* leftRotate(Node* n)
{
  Node* r = n->right;
  Node* l = r->left;

  // r becomes the new root
  r->left=n;
  n->right = l;

  //update the heights
  n->height = max(height(n->left), height(n->right))+1;
  r->height = max(height(r->left), height(r->right))+1;

  //return the new root 
  return r;
}

int getBalance(Node* n)
{
  if(n == NULL)
    return 0;
  return (height(n->left) - height(n->right));
}

Node* insert(Node* n, int data)
{
  // 1. Perform normal BST insertion
  if(n == NULL)
    return(create_node(data));

  if(data < n->data)
    n->left = insert(n->left, data);
  else if(data > n->data)
    n->right = insert(n->right, data);
  else // equal keys aren't allowed in BST
    return n;

  // 2. Update the height of this ancestor node
  n->height = 1 + max(height(n->left), height(n->right));

  // 3. Get the balance factor of the node to see if it's unbalanced
  int balance = getBalance(n);

  // if the node is unbalanced, there are 4 cases
  // Left Left case
  if(balance > 1 && data < n->left->data)
    return rightRotate(n);

  // Right right case
  if(balance < -1 && data > n->right->data)
    return leftRotate(n);

  // Left Right case
  if(balance > 1 && data > n->left->data)
  {
    n->left = leftRotate(n->left);
    return rightRotate(n);
  }

  // Right Left case
  if(balance < -1 && data < n->right->data)
  {
    n->right = rightRotate(n->right);
    return leftRotate(n);
  }

  return n;
}

Node* min_node(Node* n)
{
  Node* curr = n;
  while(curr->left != NULL)
    curr = curr->left;
  return curr;
}

Node* delete(Node* root, int data)
{
  // 1. Perform a standard BST delete
  if(root == NULL)
    return root;

  // Key is smaller, go left
  if(data < root->data)
    root->left = delete(root->left, data);

  // Key is greater, go right
  else if(data > root->data)
    root->right = delete(root->right, data);

  // Equal -- node to be deleted
  else
  {
    // node with only one child, or no children
    if((root->left == NULL) || root->right == NULL)
    {
      Node* tmp = root->left ? root->left:root->right;

      // No child case
      if(tmp == NULL)
      {
        tmp = root;
        root = NULL;
      }
      // only one child
      else
        *root = *tmp; // copy the contents of the non-empty child

      free(tmp);
    }
    // Node with 2 children
    else
    {
      // get the inorder sucessor
      Node* tmp = min_node(root->right);

      // Copy successors data to this node
      root->data = tmp->data;

      // Delete the successor
      root->right = delete(root->right, tmp->data);
    }
  }

  // if the tree had only one node, then return
  if(root == NULL)
    return root;

  // 2. Update the height of the current node
  root->height = 1 + max(height(root->left), height(root->right));

  // 3. Get the balance factor
  int balance = getBalance(root);

  // Left Left Case
  if(balance > 1 && getBalance(root->left) >= 0)
    return rightRotate(root);

  // Left right case
  if(balance > 1 && getBalance(root->left) < 0)
  {
    root->left = leftRotate(root->left);
    return rightRotate(root);
  }

  // Right Right case
  if(balance < -1 && getBalance(root->right) <= 0)
    return leftRotate(root);

  // Right left case
  if(balance < -1 && getBalance(root->right) > 0)
  {
    root->right = rightRotate(root->right);
    return leftRotate(root);
  }

  return root;
}

void preOrder(Node* root)
{
  if(root != NULL)
  {
    printf("%d ", root->data);
    preOrder(root->left);
    preOrder(root->right);
  }
}

int main()
{
    Node *root = NULL;
 
  /* Constructing tree given in the above figure */
    root = insert(root, 9);
    root = insert(root, 5);
    root = insert(root, 10);
    root = insert(root, 0);
    root = insert(root, 6);
    root = insert(root, 11);
    root = insert(root, -1);
    root = insert(root, 1);
    root = insert(root, 2);
 
    /* The constructed AVL Tree would be
            9
           /  \
          1    10
        /  \     \
       0    5     11
      /    /  \
     -1   2    6
    */
 
    printf("Preorder traversal of the constructed AVL "
           "tree is \n");
    preOrder(root);
 
    root = delete(root, 10);
 
    /* The AVL Tree after deletion of 10
            1
           /  \
          0    9
        /     /  \
       -1    5     11
           /  \
          2    6
    */
 
    printf("\nPreorder traversal after deletion of 10 \n");
    preOrder(root);
 
    return 0;
}