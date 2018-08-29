#include <stdio.h>

double func_test(double);

double midpoint(double a, double b, double (*func)(double));

double simpson_13(double a, double b, double (*func)(double));

double simpson_38(double a, double b, double (*func)(double));

double gauss_quad (double a, double b, int n, double (*func)(double));



int main(){
  double answer = 0;
  double a = 0;
  double b = 0;
  printf("\nPlease give me values for a and b as your integral bounds\t");
  scanf("%f %f" , &a, &b);
  answer = midpoint(a, b, func_test);
  printf("Your answer is: %f\n");
}
