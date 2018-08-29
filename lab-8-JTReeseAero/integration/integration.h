#ifndef integration_h
#define integration_h

struct integral{
  double (*integrand)(double);
  double low;
  double high;
};

double midpoint(struct integral paramz);

double simpson_13(struct integral paramz);

double simpson_38(struct integral paramz);

double gauss_quad (struct integral paramz, int n);

#endif


