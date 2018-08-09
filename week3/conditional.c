#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(){
  char buf[100];
  int input;
  int flag;

  printf("Enter a value: ");

  fgets(buf, sizeof(buf), stdin);
  input = atoi(buf);
  if (!isdigit(*buf)){
    printf("not a valid number");
    return 1;
  }

  memset(buf, 0, sizeof(buf));

  printf("Enter non-zero value to set flag to true or 0 to set flag to false: ");
  fgets(buf, sizeof(buf), stdin);
  flag = atoi(buf);
  if (!isdigit(*buf)){
    printf("not valid input");
    return 1;
  }



  if (input < 0){
    printf("less than 0\n");
  }
  else if (input > 0){
    printf("greater than 0\n");
  }
  else if (input == 0){
    printf("equal to 0\n");
  }

  if (input <= 99){
    printf("less than or equal to 99\n");
  }
  else if (input >= 100){
    printf("greater than or equal to 100\n");
  }

  if (input > 0 && input < 50){
    printf("between 0 and 50 non inclusive\n");
  }
  else if (input < 0 || input > 50){
    printf("less than 0 or greater than 50\n");
  }

  if (!flag){
    printf("flag false\n");
  }
  else{
    printf("flag true\n");
  }

  return 0;
}
