#include<stdio.h>
#include<stdlib.h>

struct matrix{
  int r;
  int c;
  double **matf;
};

int allocate_matrix(int row, int column, struct matrix *mw){
  mw->r = row;
  mw->c = column;
  int i = 0;

  mw->matf = malloc(sizeof(double *) * row);
  for(i = 0; i < row; ++i){
    mw->matf[i] = malloc(sizeof(double) * column);
  }

  return 0;
}

int print_matrix(struct matrix *mw){
  int r = 0;
  int c = 0;

  for(r = 0; r<mw->r; r++){
    for (c = 0; c<mw->c; c++){
      printf("%f ",mw->matf[r][c]);
    }
    printf("\n");
  }
  return 0;
}

int main()
{
    // Declare Vairables
    int i,j,k,n;
    float c;
    double  x[100]; // You'll need a few more variables, but only one matrix
    struct matrix mw;

    // Request System Order (Number of Equtions)
    printf("\nHow many equations: ");
    scanf("%d",&n);
    // Allocate Dynamic Veriables
    allocate_matrix(n, n+1, &mw);

    // Request Augmented Matrix Values
    printf("\nEnter the elements of augmented matrix row-wise:\n");
    for(i=0; i<n; i++)
    {
        for(j=0; j<(n+1); j++)
        {
            printf(" A[%d][%d]:", i,j);
            scanf("%lf",mw.matf[i]+j);
        }
    }
    print_matrix(&mw);    

    // Diagnolize the matrix
    for(j=0; j<n; j++)
    {
        for(i=0; i<n; i++)
        {
            if(i!=j)
            {
	      c = mw.matf[i][j]/mw.matf[j][j];
                for(k=0; k<n+1; k++)
                {
		  mw.matf[i][k] -= c*mw.matf[j][k];
                }
            }
        }
    }
    print_matrix(&mw);

    printf("\nThe solution is:\n");
    for(i=0; i<n; i++)
    {
      x[i] = mw.matf[i][n]/mw.matf[i][i];
      printf("\n x%d=%lf\n",i,x[i]);
    }
    return(0);
}
