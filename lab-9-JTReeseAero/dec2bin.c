#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int decimaltobinary(int whole, float dec){
  int binwhole[1000];
  int i = 0;
  while (whole > 0) {
    // storing remainder in binary array
    binwhole[i] = whole % 2;
    whole = whole / 2;
    i++;
  }
  
  int j = 0;
  int count = 0;
  for (j = i - 1; j >= 0; j--){
    count = binwhole[j];
    printf("%d", count);
  }
  //**************************************************
  printf(".");
  int h = 0;
  int bindec[1000];
  float frac = 1;
  float bob = 0;
  int right = 0;
  while (frac > 0 && h < 10){
    bob = dec * 2;
    if (bob >= 1){
      bindec[h] = 1;
      frac = bob - 1;
    }
    else{
      bindec[h] = 0;
      frac = bob;
    }
    dec = frac;
    //   printf("%f\n",frac);
    right = bindec[h];
    printf("%d", right);
    h++;
  }
  
  printf("\n");
  return count;
}/*end of function*/


int main(){
  int whole = 0;
  float dec = 0;
  char input[1000];

  printf("Please give me a number to be converted to binary: ");
  scanf("%s", input);
  whole = atoi(input);
  const char ch = '.';
  char *p;
  p = strchr(input, ch);
  if (NULL != p){
    dec = atof(p);
  }
  
  decimaltobinary(whole,dec);
  return 0;
}/*end main*/
