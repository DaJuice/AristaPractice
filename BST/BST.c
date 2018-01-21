
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

// Helper function to do an inorder traversal of the binary tree
void inorder(struct node* root){
  if(root != NULL){
    inorder(root->left);
    printf("%d \n", root->data);
    inorder(root->right);
  }
}

Node* insert_node(Node* node, int data) {
  if(node == NULL) { create_node(data); }
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
  }
  if(data == node->data){
    // Three cases
    // #1 is if the tree has one child
    if(node->left == NULL && node->right == NULL){
      
    }
  }
}

int main() {
  return 0;
}
