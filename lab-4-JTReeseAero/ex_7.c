#include <stdio.h>
#include <ctype.h>
#include <string.h>

int check(char* x){
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

int main (){
  printf("Give me an integer or not integer: \n");
  char s[10000];
  scanf("%s",s);
  if (check(s) == 0 ){
    printf("That is an integer.\n");
    return 0;
  }
  else{
    printf("That is not an integer.\n");
    return 1000;
  }
}

