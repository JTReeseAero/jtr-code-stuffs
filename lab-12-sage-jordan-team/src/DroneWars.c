// A simple program that computes the square root of a number
#define _BSD_SOURCE
#include <stdio.h>
#include "DroneWars.h"
#include <stdlib.h>
#include <string.h>

union Challenge_Answer {
  int i;
  const char * str;
  float f;
  char arr[256];
  char ** str_array;
};

//**********Calculation Function*******************************
int Calc(const char *str){
  FILE *math;

  printf("Calc Challenge\n");
  printf("the string is: %s\n", str);

  math = fopen("math","w");
  if (math == NULL){
    printf("There was an error with fopen\n");
  }

  if (fprintf(math, "%s\n", str) < 0){
    printf("There was an error with fprintf\n");
  }

  fclose(math);
  printf("debug 1\n");
  math = popen("echo quit | bc -q math", "r");

  if (math == NULL){
    printf("There was an error with popen\n");
  }

  printf("debug 2\n");
  char ans[1000];

  if(fgets(ans, 1000, math) == NULL){
    printf("There was an error with fgets\n");
  }

  printf("debug 3\n");
  printf("Ans is %s\n", ans);
  int answer = atoi(ans);
  pclose(math);

  return answer;
}//end calculation function

//************Sub-String Function******************************
const char * Sub_Str(const char *str1, const char *str2){

  printf("SubStr Challenge\n");
  printf("str1 = %s\n", str1);
  printf("str2 = %s\n", str2);

  const char * strans = strstr(str1, str2);

  printf("ans = %s\n", strans);
  return strans;
}//end substring function

//************Range Function***********************************
int Range(int numb1, int numb2){

  printf("Range Challenge\n");  
  printf("num1 = %d\n", numb1);
  printf("num2 = %d\n", numb2);
  
  int range = numb1 - numb2;

  printf("range = %d\n", range);
return range;
}//end range function

//************Mean Function************************************
float Mean(float array[], int f_count){

  printf("Mean Challenge\n");
  printf("f_count = %d\n", f_count);

  int count;
  float sum = 0;
  float ans = 0;

  for (count = 0; count < f_count; count++){
    printf("%f ", array[count]); 
   sum += array[count];
  }

  ans = sum/f_count;
  printf("answer = %f\n", ans);

  return ans;
}//end mean function

//************Minimum Function*********************************
float Min(float array[], int f_count){

  printf("Minimum Challenge\n");
  printf("f_count = %d\n", f_count);

  int count;
  float min = array[0];

  for (count = 1; count < f_count; count++){
    if (array[count] < min){
      min = array[count];
    }
  }

  printf("minimum = %f\n", min);

  return min;
}//end Minumum function

//************Maximum Function*********************************
float Max(float array[], int f_count){

  printf("Maximum Challenge\n");
  printf("f_count = %d\n", f_count);

  int count;
  float max = array[0];

  for (count = 1; count < f_count; count++){
    if (array[count] > max){
      max = array[count];
    }
  }

  printf("maximum = %f\n", max);

  return max;
}//end maximum function

//************Reverse Function*********************************
int Reverse(const char *str, char * ans){

  printf("Reverse Challenge\n");
  printf("string = %s\n", str);

  int length = strlen(str);
  int count;

  for (count = 0; count < length; count ++){
    ans[count] = str[length - count - 1];
  }

  ans[length] = 0;

  return 0;
}//end reverse function

//************Find Function************************************
int Find(const char *str, const char charact){

  printf("Find Challenge\n");
  printf("string = %s\n", str);
  printf("character = %c\n", charact);

  const char * ans = memchr(str, charact, strlen(str));
  int pos = ans - str;

  printf("position = %d\n", pos);

  return pos;
}//end finding function

//************Tokenize function********************************
char **Token(const char *str){

  printf("Tokenize Challenge\n");
  printf("string = %s\n", str);

  int len = strlen(str);
  char *copy = malloc((len + 1) * sizeof(char));
  strcpy(copy, str);
  char **tokens = malloc(len * sizeof(char *));
  int num = 0;
  char *token;
  char *temp = copy;

  while((token = strtok(temp, " \t")) != NULL){
    tokens[num] = malloc((strlen(token) + 1) * sizeof(char));
    strcpy(tokens[num], token);
    temp = NULL;
    num++;
  }
  /* sent[0] = "This";
  sent[1] = "is";
  sent[2] = "a";
  sent[3] = "test";
  sent[4] = "of";
  sent[5] = "your";
  sent[6] = "string";
  sent[7] = "tokenizer";*/
  
  //Ask Brian what the heck Tokenize wants us to do and how to return it.
  return tokens;
}//end tokenizing function

//***********Moving the agent**********************************
int move(struct Round round){
  int i = 0;
  int j = 0;

  for(i = 0; i < 3; i++){
    for(j = 0; j < 3; j++){
      printf("%d ", round.vision[i][j]);
   
    }
    printf("\n");
  }

  if(round.vision[0][1] != true){
    return 1;
  }

  else  if(round.vision[1][2] != true){
    return 2;
  }

  else if(round.vision[2][1] != true){
    return 3;
  }

  else if(round.vision[1][0] != true){
    return 4;
  }



  return 0;
}
//************Handling the functions...Function****************
int Handle_Challenge(struct Round round){
  printf("\n\n");
  union Challenge_Answer *ans = round.ans_ptr;
  if (round.chal_typ == calc){
    // printf("Did I get here?\n");
    ans->i = Calc(round.chal_dat.calc);
    // *(int *)round.ans_ptr = Calc(round.chal_dat.calc);
    //ans->i = 5;
  }
  else if (round.chal_typ == substr){
    ans->str = Sub_Str(round.chal_dat.substr.s1, round.chal_dat.substr.s2);  
  }
  else if (round.chal_typ == range){
    ans->i = Range(round.chal_dat.range.a, round.chal_dat.range.b);
  }
  else if (round.chal_typ == mean){
    ans->f = Mean(round.chal_dat.minmaxmean.nums, round.chal_dat.minmaxmean.datalen);
  }
  else if (round.chal_typ == min){
    ans->f = Min(round.chal_dat.minmaxmean.nums, round.chal_dat.minmaxmean.datalen);
  }
  else if (round.chal_typ == max){
    ans->f = Max(round.chal_dat.minmaxmean.nums, round.chal_dat.minmaxmean.datalen);
  }
  else if (round.chal_typ == rev){
    Reverse(round.chal_dat.rev, ans->arr);
  }
  else if (round.chal_typ == find){
    ans->i = Find(round.chal_dat.find.s1, round.chal_dat.find.key);
  }
  else if (round.chal_typ == token){
   ans->str_array = Token(round.chal_dat.token);  
}
  return 0;
}

int handle_plot(FILE *fp, const char *output){
  int i;
  int row = 0;
  int col = 0;
  int val = 0;
  char buf[255];
  FILE *fpout;
  fpout = fopen("plot.dat", "w");
  if(fpout == NULL){
    printf("There was an error with fopen in handle_plot\n");
    return 1;
  }

  while(1){
    if(fgets(buf, sizeof buf, fp) == NULL){
      break;
    }
    if(buf[0] == '#'){
      continue;
    }
    printf("O\t%s", buf);
    sscanf(buf, "%d %d %d", &col, &row, &val);
    printf("X\t%d %d %d\n", col, row, val);
    fprintf(fpout, "%d %d %d\n", col, row, val);
  }
  
  fclose(fpout);

  char command[1000];
  sprintf(command, "gnuplot -e \"outfile='%s'\" plotscript.txt",output);
  system(command);
  return 0;
}

int Agent_1(struct Round round) {

  Handle_Challenge(round);
  return  move(round);

}

int Agent_2(struct Round round) {

  Handle_Challenge(round);
  return move(round);

}

void Display(FILE *agent_1_board, FILE *agent_2_board) {
  handle_plot(agent_1_board, "agent1.png");
  handle_plot(agent_2_board, "agent2.png");

}

