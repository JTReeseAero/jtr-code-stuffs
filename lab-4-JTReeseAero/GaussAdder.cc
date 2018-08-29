#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

int isint(char* x){
  int i;
  for (i = 0; i<strlen(x);i++){
    if(i == 0){
      if(x[i] == '-' || isdigit(x[i])){
      }
      else{
	return 1;
      }
    }
    else if (!isdigit(x[i])){
      return 1;
    }
  }
  return 0;
}

float GaussAdder(int n){
  int sum = 0;
  printf("GaussAdder says \"I have begun adding number.\"\n");
  sum = (n*(n+1))/2;
  return sum;
}/*end brute adder*/

int main(){
  char s[100000];
  int n;
  float Sum = 0;
  printf("Please give me a positive integer to be summed. This number will be summed in an add one sequence. ");
  scanf("%s",s);
  if (isint(s) == 0){
    printf("Your integer is indeed %s. \n",s);
    n = atoi(s);
    Sum = GaussAdder(n);
    printf("Your sum is %f. \n",Sum);
  }
  else{
    printf("That was not an integer. Please try again. \n");
  }/*end first for loop*/
  return 0;
}/*end main*/
