#include <stdio.h>
#include <math.h>


float FactorialCalc(n){

  int c;
  float fact = 1;
  //INVAR: I have none in this loop
  for (c=1 ; c<=n ; c++){
    fact = fact * c;
  }//End for loop
  return fact;
}

int main(){
  //Declaration of variables
  int iter = 0;
  float errordesire = 0;
  float erroriter = 1;
  float x = 0;
  float previous = 0;
  float current = 0;

  //Program input section
  printf("\nPlease give me a number to compute e^x, where x is your number: ");
  scanf("%f", &x);

  printf("\nPlease give me an error convergence value: ");
  scanf("%f", &errordesire);
  //The loop for calculation e^x with a desired precision
  // INVAR: Previous will always become the value of the maclaurin series at the corresponding iteration.
  // INVAR: erroriter will always be the difference between the previous value of the series and the current one
  while(erroriter>errordesire){
    current = previous + (( pow(x, iter)) / ((FactorialCalc(iter))));
    erroriter = current-previous;
    previous = current;
    iter++;
  }
  printf("this is current %f ",current);
  return 0;
}//end main
