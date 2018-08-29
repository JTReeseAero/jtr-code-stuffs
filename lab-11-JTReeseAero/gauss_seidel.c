#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include "csv.h"
#include <math.h>

struct matrix{
  int r;
  int c;
  double **matf;
};

struct counts {
  long unsigned fields;
  long unsigned rows;
  long unsigned columns;
};

struct element {
  int rows;
  int cols;
  int values;

};

//*****************function used by csvparse***************************************

void cb1 (void *s, size_t len, void *data) {
  ((struct counts *)data)->fields++;
}

void cb2 (int c, void *data) {
  ((struct counts *)data)->rows++;
}

void storfield (void *s, size_t len, void *data){
  struct matrix *mw = ((struct matrix *)data);
  double v = atof(s);
  mw->matf[mw->r][mw->c] = v;
  mw->c++;
}

void countrow (int c, void *data){
  struct matrix *mw = ((struct matrix *)data);
  mw->r++;
  mw->c = 0;
}
//********************cvinfo func****************************
static int is_space(unsigned char c) {
  if (c == CSV_SPACE || c == CSV_TAB) return 1;
  return 0;
}

static int is_term(unsigned char c) {
  if (c == CSV_CR || c == CSV_LF) return 1;
  return 0;
}
//********************initialize matrix***********************
int init_matrix(struct matrix *mw){
  mw->r = 0;
  mw->c = 0;
  mw->matf = NULL;

  return 0; 
}
//********************allocate memory**************************
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
//********************freeing the memory*********************
int free_matrix(struct matrix *mw){
  int i = 0;

  for(i = 0; i < mw->r; ++i){
    free(mw->matf[i]);
  }
  free(mw->matf);
  return 0;
}
//*********************Compressing the sparse****************
int sparse_compr(struct matrix *mat){
 
  // do stuff


  return 0;
}
//*********************file reading**************************
int file_read(const char *file, struct matrix *mw){
  FILE *fp;
  struct csv_parser p;
  char buf[1024];
  size_t bytes_read;
  unsigned char options = 0;
  struct counts co = {0, 0};
  printf("degug3\n");
  if (csv_init(&p, options) != 0) {
    fprintf(stderr, "Failed to initialize csv parser\n");
    return 1;
  }
  
  csv_set_space_func(&p, is_space);
  csv_set_term_func(&p, is_term);

  //  printf("debug4\n");
  // printf("File name: %s\n", file);
  fp = fopen(file, "rb");
  // printf("debug4.1\n");
  // Read line from file
  // printf("%i\n",fp);
  if (!fp) {
    fprintf(stderr, "Failed to open %s: %s\n", file, strerror(errno));
    return 2;
  }
  // printf("debug5\n");
  while ((bytes_read=fread(buf, 1, 1024, fp)) > 0) {
    if (csv_parse(&p, buf, bytes_read, cb1, cb2, &co) != bytes_read) {
      fprintf(stderr, "Error while parsing file: %s\n", csv_strerror(csv_error(&p)));
      return 7;
    }
  }

  csv_fini(&p, cb1, cb2, &co);

  if (ferror(fp)) {
    fprintf(stderr, "Error while reading file %s\n", file);
    fclose(fp);
    return 3;
  }

  printf("%s: %lu fields, %lu rows\n", file, co.fields, co.rows);


  co.columns = co.fields / co.rows;
  allocate_matrix(co.rows, co.columns, mw);
  rewind(fp);

  csv_free(&p);
  options = CSV_APPEND_NULL;
  if (csv_init(&p, options) != 0) {
    fprintf(stderr, "Failed to initialize csv parser\n");
    return 4;
  }
  //printf("about to do the while\n");

  //INVAR this is the csv code, but we are chunking through the file by 1024 bytes and parsing it. 
  mw->r = 0;
  mw->c = 0;
  while ((bytes_read=fread(buf, 1, 1024, fp)) > 0) {
    if (csv_parse(&p, buf, bytes_read, storfield, countrow, mw) != bytes_read) {
      fprintf(stderr, "Error while parsing file: %s\n", csv_strerror(csv_error(&p)));
      return 6;
    }
  }
  //printf("after the while\n");

  csv_fini(&p, storfield, countrow, mw);
  mw->r = co.rows;
  mw->c = co.columns;
  
  if (ferror(fp)) {
    fprintf(stderr, "Error while reading file %s\n", file);
    fclose(fp);
    return 5;
  }
  
  
  csv_free(&p);
  //printf("right before return\n");
  return 0;
}
//********************Printing to a file***************
int fileprint(struct matrix *mw,const char *fileout){
  FILE *filename; 
  int r = 0;
  int c = 0;
  filename = fopen(fileout, "w+");
  if(NULL == filename){
    printf("The file cannot be opened\n");
    return 1;
  }

  for(r = 0; r<mw->r; r++){
    for (c = 0; c<mw->c; c++){
      if(c == mw->c - 1){
	fprintf(filename, "%f",mw->matf[r][c]);
      }
      else{
	fprintf(filename, "%f,",mw->matf[r][c]);
      }
    }
    fprintf(filename, "\n");
  }
  fclose(filename);
  return 0;  
}
//*********************************************************
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
//***********Seidel****************************************
int gauss_seidel(struct matrix *A, double TOL, int maxiter, struct matrix *ans){
  int n = A->r;
  double *b = (double*) calloc(n, sizeof(double));
  double *x = (double*) calloc(n, sizeof(double));
  int i = 0;

  for(i = 0; i < n; i++){
    b[i] = A->matf[i][n];
  }
  double *dx = (double*) calloc(n, sizeof(double));
  i = 0;
  int j = 0;
  int k = 0;

  for(k = 0; k < maxiter; k++){
    double sum = 0.0;
    for(i = 0; i < n; i++){
      dx[i] = b[i];
      for(j=0; j<n; j++){
	dx[i] -= A->matf[i][j]*x[j];
      }
      dx[i] /= A->matf[i][i]; 
      x[i] += dx[i];
      sum += fabs(dx[i]);
    }
    printf("%4d : %.3e\n",k,sum);
    if(sum <= TOL) break;
  }
  
  printf("answers\n");
  // int r = 0;

  /*for(r = 0; r < n; r++){
    printf("%f\n", x[r]);
    }*/

  allocate_matrix(n,1,ans);
  i = 0;
  
  for(i = 0; i < n; i++){
    ans->matf[i][0] = x[i];
  }
 
  // print_matrix(A);
  free(dx);
  free(b);
  free(x);
  return 0;
}
//***********fucntion that calls fucntions so main looks pretty********
int filecall(const char *filein, const char *fileout, double TOL, int maxiter){
  int err;
  struct matrix mat;
  struct matrix ans;
  init_matrix(&mat);
  init_matrix(&ans);
  
  // printf("debug2.1\n");
  //printf("File (in filecall): %s\n", filein);
  err = file_read(filein, &mat);
  //printf("debug2\n");

  if(err != 0){
    free_matrix(&mat);
    return 1;
  }
  print_matrix(&mat);
  printf("\n\n");
  gauss_seidel(&mat, TOL, maxiter, &ans);
  //  print_matrix(&ans);

  if(fileprint(&ans,fileout) != 0){
    free_matrix(&ans);
    free_matrix(&mat);
    return 2;
  }

  free_matrix(&ans);
  free_matrix(&mat);
  return 0;
}
//********************************************
int user_input(struct matrix *mw){
  int n = 0;
  int i = 0;
  int j = 0;

  printf("\nHow many equations: ");
  scanf("%d",&n);

  allocate_matrix(n, n+1, mw);
  
  printf("\nEnter the elements of augmented matrix row-wise:\n");
  for(i=0; i<n; i++) {
      for(j=0; j<(n+1); j++){
	printf(" A[%d][%d]:", i,j);
	scanf("%lf",mw->matf[i]+j);
      }
  }
  print_matrix(mw);
  return 0;   
}

int printcmdline(){
  return 0;
}
//******************************************
int usercall(double TOL, int maxiter){
  struct matrix mat;
  struct matrix ans;

  init_matrix(&ans);
  init_matrix(&mat);
  user_input(&mat);
  gauss_seidel(&mat, TOL, maxiter, &ans);
  print_matrix(&ans);
  
  // print_matrix(&mat);
  free_matrix(&ans);
  free_matrix(&mat);

  return 0;
}

int main(int argc, char **argv){
  printf("\n\nUsage: if the user wishes to change the tolerance enter -t\n"); 
  printf("if the user wishes to change the iteration count enter -i\n");
  printf("Please enter the flags last!\n\n");
  double TOL = .001;
  int maxiter = 100;
  int flagcount = 0;
  
  if (argc > 4){
    printf("Sorry you input to many arguments\n");
    return 1;
  }
  char **original = argv;  
  while (*(++argv)) {
    if (strcmp(*argv, "-t") == 0) {
      printf("Please enter the tolerance you would like to have: \n");
      scanf("%lf", &TOL);
      flagcount++;
    }
    else if (strcmp(*argv, "-i") == 0) {
      printf("Please enter the number of iteration you would like to have: \n");
      scanf("%d", &maxiter);
      flagcount++;
      continue;
    }
  }
  
  argv = original;
  if ((argc == 3 && flagcount == 1) || (argc > 3) || (argc == 2 && flagcount == 0)){
    // printf("debug\n");
    if(filecall(argv[1],"solvedSeidel.csv", TOL,  maxiter) != 0){
      return 1;
    }
  }
  
  else if ((argc == 3 && flagcount == 2) || (argc == 2 && flagcount == 1) || (argc == 1 && flagcount == 0)) {
    if(usercall(TOL,maxiter) != 0){
      return 2;
    }
  }
  
  return 0;
}//end main
