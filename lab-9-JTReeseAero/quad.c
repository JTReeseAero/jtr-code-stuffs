#include<stdio.h>
#include<math.h>

int main(){
  long double a;
  long double b;
  long double c;
  long double d;
  long double root1;
  long double root2;


  printf("Enter a of quadratic equation: ");
  scanf("%Lf", &a);
  printf("Enter b of quadratic equation: ");
  scanf("%Lf", &b);
  printf("Enter c of quadratic equation: ");
  scanf("%Lf", &c);

  discriminant = b * b - 4 * a * c;
  long  double  bot = 2*a;

  if(bot == 0){ //checks to see is the denominator is zero, if it is we cannot divide by zero, so we use the alternate equation.

    if(discriminant < 0){
      printf("Roots are complex.\n");
      printf("Roots of quadratic equation are: ");
      // printf("%Lf%+Lfi", 2*c/-b, 2*c/sqrt(-discriminant));
      // printf(", %Lf%+Lfi\n", 2*c/-b, -2*c/sqrt(-discriminant));
      //since we don't need to output complex number I commmented these, out but I was curious as to how it was done.
      return 0;
    }

    else if(discriminant == 0){
      printf("Equal Roots\n");

      root1 = 2*c/-b;
      printf("Both of the roots are: %Lf\n ", root1);
      return 0;
    }

    else{
      printf("Real Roots\n");

      root1 = (2*c)/(-b + sqrt(discriminant));
      root2 = (2*c)/(-b - sqrt(discriminant));
      printf("Roots of this quadratic equation are: %Lf , %Lf\n", root1, root2);
    }
  }

  else{

    //uses original equation to find roots

    if(discriminant < 0){
      printf("Roots are complex.\n");

      printf("Roots of quadratic equation are: ");
      printf("%Lf%+Lfi", -b/bot, sqrt(-discriminant)/bot);
      printf(", %Lf%+Lfi\n", -b/bot, -sqrt(-discriminant)/bot);

      return 0;
    }
  }
}//end main.
