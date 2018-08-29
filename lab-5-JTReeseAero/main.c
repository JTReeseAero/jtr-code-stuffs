#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define direct_right 0
#define direct_down 1
#define direct_left 2
#define direct_up 3

int is_int(char* x){
  int i;
  for (i = 0; i<strlen(x);i++){
    if(i == 0){
      if(x[i] == '-' || isdigit(x[i])){
      }
      else{
	return 0;
      }
    }
    else if (!isdigit(x[i])){
      return 0;
    }
  }
  return 1;
}

int PrintUsage(){
  printf("Sorry that input was not an integer betwixt 1 and 100.\n");
  return 1;
}/*End PrintUsage Function*/

int main(){
  int input;
  char s[100];
  int matrix[100][100];
  int n = 0;
  int r = 0;
  int c = 0;
  int direction = direct_right;
  int streak = 1;
  int remain = 2;
  int maxwidth = 0;
  char squarestr[100];
  char* format;

  printf("Please input a integer betwixt 1 and 100: ");
  scanf("%s",s);
  if (!is_int(s)){
    return PrintUsage();
  }
  input = atoi(s);
  if (input < 1 || input > 100){
    return PrintUsage();
  }
  c = (input-1)/2;/*column*/
  r = (input-1)/2;/*row*/
  while (n < input*input){
    matrix[r][c] = ++n;
    /************************************************/
    if (direct_right == direction){/*start right*/
      remain--;
      if(0 == remain){
	remain = streak;
	direction = direct_down;
	r++;
      }	
      else{
	c++;
      }
    }/*******************************end right*/
    else if (direct_down == direction){/*start down*/
      remain--;
      if(0 == remain){
	streak++;
	remain = streak;
	direction = direct_left;
	c--;
      }
      else{
	r++;
      }
    }/***********************************ending down*/
    else if (direct_left == direction){/*start left*/
      remain--;
      if(0 == remain){
	remain = streak;
	direction = direct_up;
	r--;
      }
      else{
	c--;
      }
    }/**********************************ending left*/
    else if (direct_up == direction){/*start up*/
      remain--;
      if(0 == remain){
	streak++;
	remain = streak;
	direction = direct_right;
	c++;
      }
      else{
	r--;
      }
    }/*********************************ending up*/
  }
  sprintf(squarestr,"%d",input*input);
  maxwidth = strlen(squarestr);
  /************adjusting spacing*****************/
  if(1 == maxwidth){
    format = "%1d ";
  }
  if(2 == maxwidth){
    format = "%2d ";
  }
  if(3 == maxwidth){
    format = "%3d ";
  }
  if(4 == maxwidth){
    format = "%4d ";
  }
  if(5 == maxwidth){
    format = "%5d ";
  }
  /************ending adjusting******************/
  for(r = 0; r<input; r++){
    for (c = 0; c<input; c++){
      printf(format,matrix[r][c]);
    }
    printf("\n");
  }

  return 0;
}/*End Main*/
