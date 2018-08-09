#include <stdio.h>

#define MAX 5

void main(){
  /*while loop*/
  int i = 0;
  while (i<MAX){
    printf("while loop %d\n", i);
    i++;
  }

  /*for loop*/
  for (int j = 0;j < MAX; j++){
    printf("for loop %d\n", j);
  }

  /*infinite loop with break*/

  int inf_test = 0;
  for(;;){
    inf_test++;
    printf("infinite %d\n", inf_test);
    if (inf_test == MAX){
      break;
    }
  }
}
