
#include <stdio.h>
#include <stdlib.h>

typedef struct node {
  int data;
  struct node* left;
  struct node* right;
}Node;

// Helper function to create a new node
Node* create_node(int data) {
  Node* new = (Node*) malloc(sizeof(Node));
  new->data = data;
  new->left = NULL;
  new->right = NULL;
  return new;
}

// Helper function to find the minimum value in a tree
Node* find_min(Node* node){
  if(node->left == NULL){
    return node;
  }
  else {
    return find_min(node->left);
  }
}

// Helper function to find the max value in a tree
Node* find_max(Node* node) {
  if(node->right == NULL){
    return node;
  }
  else {
    return find_max(node->right);
  }
}

// Helper function to do an inorder traversal of the binary tree
void inorder(struct node* root){
  if(root != NULL){
    inorder(root->left);
    printf("%d \n", root->data);
    inorder(root->right);
  }
}

Node* insert_node(Node* node, int data) {
  if(node == NULL) { return create_node(data); }
  if(data < node->data){
    node->data = insert_node(node->left, data);
  }
  else if(data > node->data){
    node->data = insert_node(node->right, data);
  }
  return node;
}

Node* delete_node(Node* node, int data) {
  if(node == NULL){
    fprintf(stderr, "ERR: Can't delete from an empty tree");
    return root;
  }

  // If key is less, go into the left subtree
  if(data < node->data){
    node->left = delete_node(node->left, data);
  }
  // If key is greater, go into the right subtree
  else if(data > node->data){
    node->right = delete_node(node->right, data);
  }
  // Found the node!
  else {

    if(node->left == NULL){
      Node* temp = node->right;
      free(node);
      return temp;
    }
    else if(node->right == NULL){
      Node* temp = node->left;
      free(node);
      return temp;
    }

    // for a node with two children
    Node* temp = find_min(node->right);
    // copy in-order successor's content to this node
    node->data = temp->data;
    // delete the in-order successor
    node->right = delete_node(node->right, temp->data);
  }
  return node;
}

int main() {
  /* Let us create following BST
           50
        /     \
       30      70
      /  \    /  \
    20   40  60   80 */
  struct node *root = NULL;
  root = insert(root, 50);
  root = insert(root, 30);
  root = insert(root, 20);
  root = insert(root, 40);
  root = insert(root, 70);
  root = insert(root, 60);
  root = insert(root, 80);

  printf("Inorder traversal of the given tree \n");
  inorder(root);

  printf("\nDelete 20\n");
  root = delete_node(root, 20);
  printf("Inorder traversal of the modified tree \n");
  inorder(root);

  printf("\nDelete 30\n");
  root = delete_node(root, 30);
  printf("Inorder traversal of the modified tree \n");
  inorder(root);

  printf("\nDelete 50\n");
  root = delete_node(root, 50);
  printf("Inorder traversal of the modified tree \n");
  inorder(root);

  return 0;
}
