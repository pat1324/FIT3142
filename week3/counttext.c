#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int countwords(FILE *f);

int main(){
  char filename[20];

  printf("Enter filename: ");
  scanf("%s", filename);

  FILE *file = fopen(filename, "r");
  int wordcount = countwords(file);
  fclose(file);

  printf("words in file: %d\n", wordcount);


  return 0;
}

int countwords(FILE *f){
  int count = 0;
  char ch;
  if (ch = fgetc(f) != EOF){
    while ((ch = fgetc(f)) != EOF){
      if (ch == '\n' || ch == ' '){
          count++;
      }
    }
    count++;//last word in file will have EOF trailing it
  }
  return count;
}
