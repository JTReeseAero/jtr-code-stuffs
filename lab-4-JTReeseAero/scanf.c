#include <stdio.h> //both scanf and printf are included in this file
int main (int argc, char **argv){
  char s[100];
  while (1){
    printf ("Please input something (length not exceeding 100):\n");
    scanf ("%s", s);
    printf ("Your input is: %s\n", s);
    if (strcmp (s, "0") == 0){
      break;
    }
  }
  return 0;
}
