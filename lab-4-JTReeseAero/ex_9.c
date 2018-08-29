#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

int CheckUsage(){
  printf("\nPlease give the program and integer. The program will ask you the for characters that many times.\n");
  return 0;
}/*End CheckUsage*/

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

int False(char* s){/*this is bad*/
  if (isint(s) == 1){/*checks to see if user enter an integer*/
    return 0;
    printf("Sorry that was not an integer!");
  }/*ends if statement*/
  else{
    return 1;
  }
}/*end false*/

int main(){
  CheckUsage();
  char s[10000];
  int count;
  int i;
  printf("Hello! How many chars should I take? ");
  scanf("%s",s);
  if(False(s)== 0){;
    CheckUsage();
    /* if (isint(s) == 1){/*checks to see if user enters an integer
       printf("Sorry that was not an integer!");
       CheckUsage();
       }end if statement to if initial input is a number*/
  }  
  else{
    count = atoi(s);
    for(i=0;i<count;i++){
      
      if (i==0){
	printf("\nPlease give me a char: ");
	scanf("%s",s);
	if (strlen(s) != 1){
	  CheckUsage();
	  i--;
	}
      }
      else if(i>0){
	printf("\nThanks! Please give me another char: ");
	scanf("%s",s);
	if (strlen(s) != 1){
	  CheckUsage();
	  i--;
	}
      }
      if (i == count-1){
	printf("Thanks! I am happy with %d chars\n ",count);
      }
    }/*ending main for loop*/
  }/*ending else statement*/
  return 0;
}/*End main*/
