#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define ARRAY_SIZE(a) sizeof(a)/sizeof(a[0])
#define ALPHABET_SIZE (26)
#define CHAR_TO_IDX(c) ((int)c - (int)'a')

typedef struct t_node
{
  struct t_node* children[ALPHABET_SIZE];
  bool is_end;
}t_node;

t_node* new_node()
{
  t_node* new = (t_node*) malloc(sizeof(t_node));
  new->is_end = false;
  for(int i = 0; i < ALPHABET_SIZE; i++)
  {
    new->children[i] = NULL;
  }
  return new;
}

void insert(t_node* root, const char* key)
{
  int level;
  int length = strlen(key);
  int index;

  t_node* iterator = root;

  for(level = 0; level < length; level++)
  {
    index = CHAR_TO_IDX(key[level]);
    if(!iterator->children[index])
      iterator->children[index] = new_node();

    iterator = iterator->children[index];
  }
  iterator->is_end = true;    // this sets the last node to be the end of the word
}

bool search(t_node* root, const char* key)
{
  int level;
  int length = strlen(key);
  int index;

  t_node* iterator = root;

  for(level = 0; level < length; level++)
  {
    index = CHAR_TO_IDX(key[level]);

    if(!iterator->children[index])
      return false;

    iterator = iterator->children[index];
  }
  return (iterator != NULL && iterator->is_end);
}

int main()
{
  FILE* dictionary = fopen("./words", "r");
  char* word;
  t_node* root = new_node();

  if(dictionary == NULL)
  {
    printf("Can't open file for reading.\n");
  }
  else
  {
    while(fscanf(dictionary, "%s", word) != EOF)
    {
      insert(root, word);
    }
    fclose(dictionary);
  }
  return 0;
}
