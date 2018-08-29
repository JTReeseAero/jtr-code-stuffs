#include <stdio.h>
#include <string.h>
int main(void) {
  int match = 0; /* correct password */
  char buff[15]; /* array to store password */
  /* ask user for password */
  printf("Enter the password: ");
  scanf("%s", buff);
  /* check if entered password matches stored */
  if(strcmp(buff, "cyc1nenat10n")) {
    printf("\nWrong password!!!\n");
  }
  else {
    printf("\nCorrect password.\n");
    match = 1;
  }
  /* if correct, give root access */
  printf("%d\n",match);
if(match) {
    printf("\nWelcome L364CY! You now have root privileges.\n");
  }
}

