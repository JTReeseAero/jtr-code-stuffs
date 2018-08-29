#include <stdio.h>
#include "integration.h"

double func_test(double);

int main(){
  struct integral paramz;
  double answer = 0;
  paramz.low = 0;
  paramz.high = 0;
  int n = 0; 
  printf("\nPlease give me a value for a as your lower integral bound: ");
  scanf("%lf", &paramz.low);
  printf("\nPlease give me a value for b as your upper integral bound: ");
  scanf("%lf", &paramz.high);
  printf("%lf %lf\n", paramz.low,paramz.high);
  paramz.integrand = func_test;

  answer = midpoint(paramz);
  printf("Your midpoint answer is: %f\n", answer);

  answer =  simpson_13(paramz);
  printf("Your Simpson's 1/3 answer is: %f\n", answer);

  answer =  simpson_38(paramz);
  printf("Your Simpson's 3/8  answer is: %f\n", answer);

  printf("\nPlease give me the n order: ");
  scanf("%d", &n); 
  answer =  gauss_quad(paramz, n);
  printf("Your Gauss Quad answer is: %f\n", answer);

  return 0;
}
