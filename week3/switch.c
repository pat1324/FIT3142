#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main(){
  char buf[100];
  int input;

  printf("Enter a value: ");

  fgets(buf, sizeof(buf), stdin);
  input = atoi(buf);
  if (!isdigit(*buf)){
    printf("not a valid number");
    return 1;
  }

  switch (input){
    case 1:
      printf("1\n");
    case 2:
      printf("2\n");
    case 3:
      printf("3\n");
    default:
      printf("default");
  }
}
