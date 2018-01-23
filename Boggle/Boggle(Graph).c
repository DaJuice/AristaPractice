#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main() {
  FILE* dictionary = fopen("./words", "r");
  char word[64];

  if(dictionary == NULL){
    printf("Can't open file for reading.\n");
  }
  else {
    while(fscanf(dictionary, "%s", word) != EOF) {
      printf("%s\n", word);
    }
    fclose(dictionary);
  }
  return 0;
}
