#ifndef DRONE_WARS_H
#define DRONE_WARS_H

#include <stdio.h>

typedef enum { false, true } bool;

enum Challenge_Type {
  calc,
  substr,
  range,
  mean,
  min,
  max,
  rev,
  find,
  token
};

struct MinMaxMean
{
  int datalen;
  float *nums;
};

struct Range
{
  int a;
  int b;
};

struct SubStr
{
  char s1[256]; // The string to search in for both challanges
  char s2[256]; // Used for the "Sub-string" challange
  char key;     // Used for the "find" challange
};

union Challenge_Data {
  char calc[256];
  struct SubStr substr;
  struct Range range;
  struct MinMaxMean minmaxmean;
  char rev[256];
  struct SubStr find;
  char token[256];
};

struct Round
{
  bool vision[3][3];
  enum Challenge_Type chal_typ;
  union Challenge_Data chal_dat;
  void* ans_ptr;
};

int Agent_1(struct Round);
int Agent_2(struct Round);
void Display(FILE*, FILE*);

#endif /* DRONE_WARS_H */