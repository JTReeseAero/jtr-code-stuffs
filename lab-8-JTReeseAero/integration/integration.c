#include <stdio.h>
#include "integration.h"

double midpoint(struct integral paramz){
  
  double solution = (paramz.high-paramz.low)*paramz.integrand((paramz.low+paramz.high)/2);
  return solution;

}//end midpoint method

double simpson_13(struct integral paramz){
  double solution = ((paramz.high-paramz.low)/6) * (paramz.integrand(paramz.low) + 4*paramz.integrand((paramz.low+paramz.high)/2) + paramz.integrand(paramz.high));
  return solution;

}//End Simpson 1/3 method

double simpson_38(struct integral paramz){
  double solution = ((paramz.high-paramz.low)/8) * (paramz.integrand(paramz.low) + 3*paramz.integrand((2*paramz.low+paramz.high)/3) + 3*paramz.integrand((paramz.low+2*paramz.high)/3) + paramz.integrand(paramz.high));
  return solution;

}//End Simpson 3/8 method

double gauss_quad (struct integral paramz,int n){
  double *t[9];
  double *w[9];
  int i;
  double c;
  double m;
  double solution = 0;
  
  double t2[] = {.57735027, -.57735027};
  double w2[] = {1, 1};
  
  double t3[] = {0, .77459667, -.77459667};
  double w3[] = {.88888889, .55555555, .55555555};
  
  double t4[] = {0.33998104, -0.33998104, 0.86113631, -0.86113631};
  double w4[] = {0.65214515, 0.65214515, 0.34785485, 0.34785485};
  
  double t5[] = {0.0, 0.53846931, -0.53846931, 0.90617985, -0.90617985};
  double w5[] = {0.56888889, 0.47862867, 0.47862867, 0.23692689, 0.23692689};
  
  double t6[] = {0.23861919, -0.23861919, 0.66120939, -0.66120939, 0.93246951, -0.93246951};
  double w6[] = {0.46791393, 0.46791393, 0.36076157, 0.36076157, 0.17132449, 0.17132449};
  
  double t7[] = {0.0, 0.40584515, -0.40584515, 0.74153119, -0.74153119, 0.94910791, -0.94910791};
  double w7[] = {0.41795918, 0.38183005, 0.38183005, 0.27970539, 0.27970539, 0.12948497, 0.12948497};
  
  double t8[] = {0.18343464, -0.18343464, 0.52553241, -0.52553241, 0.79666648, -0.79666648, 0.96028986, -0.96028986};
  double w8[] = {0.36268378, 0.36268378, 0.31370665, 0.31370665, 0.22238103, 0.22238103, 0.10122854, 0.10122854};
  
  double t9[] = {0.0, 0.32425342, -0.32425342, 0.61337143, -0.61337143, 0.83603111, -0.83603111, 0.96816024, -0.96816024};
  double w9[] = {0.33023936, 0.31234708, 0.31234708, 0.26061070, 0.26061070, 0.18064816, 0.18064816, 0.08127439, 0.08127439};
  
  double t10[] = {0.14887434, -0.14887434, 0.43339539, -0.43339539, 0.67940957, -0.67940957, 0.86506337, -0.86506337, 0.97390653, -0.97390653};
  double w10[] = {0.29552422, 0.29552422, 0.26926672, 0.26926672, 0.21908636, 0.21908636, 0.14945135, 0.14945135, 0.06667134, 0.06667134};
  
  t[0] = t2;
  t[1] = t3;
  t[2] = t4;
  t[3] = t5;
  t[4] = t6;
  t[5] = t7;
  t[6] = t8;
  t[7] = t9;
  t[8] = t10;
  
  w[0] = w2;
  w[1] = w3;
  w[2] = w4;
  w[3] = w5;
  w[4] = w6;
  w[5] = w7;
  w[6] = w8;
  w[7] = w9;
  w[8] = w10;
  
  c = .5 * (paramz.high+paramz.low);
  m = .5 * (paramz.high-paramz.low);
  
  //Loop INVAR: solution is a continous sum. So after each loop solution is all previous solutions
  for (i = 0; i < n; i++){
    solution += w[n-2][i] * paramz.integrand(c + m*t[n-2][i]);    
  }
  solution = solution * m;
  return solution;
}//end Gauss Quad method
