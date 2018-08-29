#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]){

  long double current = 61/11.0;
  long double old = 11/2.0;
  long double new = 0;

  printf("x1 = %Lf\n", old);
  printf("x2 = %Lf\n", current);

  int n = 3;
  int doubleflag = 0;

  while (*(++argv)) {

    if (strcmp(*argv, "-d") == 0) {
      doubleflag = 1;
      continue;
    }
  }
  if(doubleflag == 1){

    for(n = 3; n < 21; n++){

      new = 111 - (1130 - (3000/old))/current;
      old = current;
      current = new;

      printf("x%d = %Lf\n", n, current);

    }
  }
  else{
    for(n = 3; n < 11; n++){

      new = 111 - (1130 - (3000/old))/current;
      old = current;
      current = new;

      printf("x%d = %Lf\n", n, current);

    }
  }
  return 0;
}
