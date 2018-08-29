#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

struct MyFloat{
  char *mantissa;
  char *expo;
  int  sign;
  int expobits;
  int mantbits;
};

int decimaltobinary(int whole, double dec, char *s){
  char output[1000];
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
  strcpy(output,"");
  for (j = i - 1; j >= 0; j--){
    count = binwhole[j];
    strcat(output, count ? "1" : "0");
  }
  //**************************************************
  strcat(output, ".");
  int h = 0;
  int bindec[1000];
  double frac = 1;
  double bob = 0;
  int right = 0;
  while (frac > 0){
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
    strcat(output, right ? "1" : "0");
    h++;
  }
  strcpy(s,output);  

  return 0;
}/*end of function*/


  
int init_myfloat(struct MyFloat *in, int expobits, int mantbits){
  in->sign = 0;
  in->mantissa = malloc(mantbits * sizeof(char));
  in->expo = malloc(expobits * sizeof(char));
  in->expobits = expobits;
  in->mantbits = mantbits;
  return 0;
}

int free_myfloat(struct MyFloat *in){
  free(in->mantissa);
  free(in->expo);
  in->mantissa = NULL;
  in->expo = NULL;
  return 0;
}

int set_myfloat(struct MyFloat *in,int sign, int whole, double dec){
  in->sign = sign;
  char buffer[1000];
  int shift = 0;
  decimaltobinary(whole,dec,buffer);
  printf("%s\n", buffer);
  
  char *p;
  p = strchr(buffer, '.');
  int numleft = p - buffer;
  if (1 == numleft){
    shift = 0;
  }

  else if(0 == numleft) {
    char *one;
    one = strchr(buffer,'1');
    if (NULL == one){
      in->sign = 0;
      return 0;
    }

    else{
      int numzero = one - (buffer + 1);
      shift = -(numzero + 1);
    }
  }

  else{
    shift = numleft-1;
  }
  //bias =  2^(expobits-1)-1
  int bias = 0;
  bias = pow(2,in->expobits-1) - 1;
  int exponent = shift + bias;
  char expbuff[100];
  decimaltobinary(exponent, 0, expbuff);
  printf("%s\n", expbuff);
  
  *strchr(expbuff,'.') = 0;
  printf("%s\n", expbuff);
  int index = 0;
  int lead = in->expobits - strlen(expbuff);
  if (lead >= 0){
    for(index = 0; index < strlen(expbuff); index++){
      in->expo[index+lead] = ('0' == expbuff[index]) ? 0 : 1; 
    }
  }

  else{
    //too many bits in expbuff than can fit in expo
    char *h = expbuff - lead;
    for (index = 0; index < strlen(h); index++){
      in->expo[index] = ('0' == h[index]) ? 0 : 1;
    } 
  }
  
 
  printf("%s\n", buffer);
  char *h = strchr(buffer,'1');
  h++;

  index = 0;
  while(index < in->mantbits && *h){
    if(*h == '.'){
      h++;
    }
    else{
      in->mantissa[index] = ('0' == *h) ? 0 : 1;
      index++;
      h++;
    }
  }
  
  //HI Brian!

  return 0;
}

int print_myfloat(struct MyFloat *in){
  int i = 0;
  printf("Your floating point bit representation is: %d ",in->sign);
  for (i = 0; i < in->expobits; i++){
    printf("%d", in->expo[i]);
  }
  printf(" ");
  for (i = 0; i < in->mantbits; i++){
    printf("%d", in->mantissa[i]);
  }
  printf("\n");
  return 0;
}


int main(){
  int whole = 0;
  double dec = 0;
  int expo = 0;
  int fract = 0;
  char input[1000];
  int sign = 0;

  printf("Please give me a number of bits for the exponent: ");
  scanf("%d", &expo);
  printf("\nPlease give me a number of bits for the fraction: ");
  scanf("%d", &fract);
  printf("\nPlease give me a number to be represented in IEEE 754 bit representation: ");
  scanf("%s", input); 

  const char *p = input;  
  if (*p == '-'){
    sign = 1;
    p++;
  }
  
  whole = atoi(p);// This assumes that the right side of the radix is less than what an int can hold
  const char chr = '.';
  char *bob;
  bob = strchr(p, chr);
  if (NULL != bob){
    dec = atof(bob);// decimal is less than a float. 
  }
    
  struct MyFloat mf;
  init_myfloat(&mf,expo,fract);
  set_myfloat(&mf,sign,whole,dec);
  print_myfloat(&mf);
  free_myfloat(&mf);
  
  
  return 0;
}//end main
