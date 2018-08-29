#include <stdio.h>

double func_test(double);

double midpoint(double a, double b, double (*func)(double));

double simpson_13(double a, double b, double (*func)(double));

double simpson_38(double a, double b, double (*func)(double));

double gauss_quad (double a, double b, int n, double (*func)(double));



int main(){
  double answer = 0;
  float a = 0;
  float b = 0;
  int n = 0; 
  printf("\nPlease give me a value for a as your lower integral bound: ");
  scanf("%f", &a);
  printf("\nPlease give me a value for b as your upper integral bound: ");
  scanf("%f", &b);
  printf("%f %f\n", a,b);

  answer = midpoint(a, b, func_test);
  printf("Your midpoint answer is: %f\n", answer);

  answer =  simpson_13(a, b, func_test);
  printf("Your Simpson's 1/3 answer is: %f\n", answer);

  answer =  simpson_38(a, b, func_test);
  printf("Your Simpson's 3/8  answer is: %f\n", answer);

  printf("\nPlease give me the n order: ");
  scanf("%d", &n); 
  answer =  gauss_quad(a, b, n, func_test);
  printf("Your Gauss Quad answer is: %f\n", answer);

  return 0;
}
