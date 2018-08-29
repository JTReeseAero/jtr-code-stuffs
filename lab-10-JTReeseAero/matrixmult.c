#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include "csv.h"

struct counts {
  long unsigned fields;
  long unsigned rows;
  long unsigned columns;
};

struct matrix{
  int r;
  int c;
  double **matf;
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
//*********************my own matrix functions*******************************
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
//*********************file reading**************************
int file_read(const char *file, struct matrix *mw){
  FILE *fp;
  struct csv_parser p;
  char buf[1024];
  size_t bytes_read;
  unsigned char options = 0;
  struct counts co = {0, 0};

  if (csv_init(&p, options) != 0) {
    fprintf(stderr, "Failed to initialize csv parser\n");
    return 1;
  }
  
  csv_set_space_func(&p, is_space);
  csv_set_term_func(&p, is_term);

  fp = fopen(file, "rb");
  if (!fp) {
    fprintf(stderr, "Failed to open %s: %s\n", file, strerror(errno));
    return 2;
  }

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
//************************multiplying the matrices*************************************

int multi_mat(struct matrix *mat1, struct matrix *mat2,struct matrix *mat3){


  if (mat1->c != mat2->r){
    printf("Your matrix dimension do not match, therefore cannot do multiplication\n");
    return 1;
  }
  
  allocate_matrix(mat1->r, mat2->c, mat3);

  //stopped here
  /*or(i = 0; i < dimension; i++){
    for(j = 0; j < dimension; j++){
      for(k = 0; k < dimension; k++){
  	C[dimension*i+k] += A[dimension*i+j] * B[dimension*j+k];
      }
    }
  }*/
  

 
  /*or (int j = 0; j < n; j++)
    {
      for (int k = 0; k < n; k++)
	Bcolj[k] = b[k, j];

      for (int i = 0; i < n; i++)
        {
	  double s = 0;
	  for (int k = 0; k < n; k++)
	    s += a[i,k] * Bcolj[k];
	  c[j, i] = s;
        }
	}*/


  int r = 0;
  int c = 0;
  int k = 0;
  double loc = 0;

  for(r = 0; r < mat3->r; r++){
    for(c = 0; c < mat3->c; c++){
      loc = 0;
      for(k = 0; k < mat1->c; k++){
	loc += mat1->matf[r][k] * mat2->matf[k][c];
      }
      mat3->matf[r][c] = loc;
    }
  }

  return 0;
}
//********************Printing to a file***************
 
int fileprint(struct matrix *mw){
  FILE *filename; 
  int r = 0;
  int c = 0;
  filename = fopen("ans.csv", "w+");

  for(r = 0; r<mw->r; r++){
    for (c = 0; c<mw->c; c++){
      fprintf(filename, "%f ",mw->matf[r][c]);
    }
    fprintf(filename, "\n");
  }
  fclose(filename);
  return 0;  
}





//********************Begin Main***********************
int main (int argc, char *argv[]){ 


  if (argc != 3) {
    fprintf(stderr, "Command line input should be 2 csv files only.\n");
    exit(EXIT_FAILURE);
  }

  const char *file1 = argv[1];
  const char *file2 = argv[2];
  struct matrix matrix1;
  struct matrix matrix2;
  struct matrix matrix3;
  int result = 0;

  init_matrix(&matrix1);
  init_matrix(&matrix2);
  init_matrix(&matrix3);

  result = file_read(file1, &matrix1);
  if (0 != result){
    free_matrix(&matrix3);
    free_matrix(&matrix1);
    free_matrix(&matrix2);
    return 1;
  }

  result = file_read(file2, &matrix2);
  if (0 != result){
    free_matrix(&matrix3);
    free_matrix(&matrix1);
    free_matrix(&matrix2);
    return 1;
  }

  print_matrix(&matrix1);
  printf("\n\n");
  print_matrix(&matrix2);
  printf("\n\n");

  result = multi_mat(&matrix1, &matrix2, &matrix3);
  if (0 != result){
    free_matrix(&matrix3);
    free_matrix(&matrix1);
    free_matrix(&matrix2);
    return 1;
  }
  print_matrix(&matrix3);
  fileprint(&matrix3);

  free_matrix(&matrix3);
  free_matrix(&matrix1);
  free_matrix(&matrix2);
  
  return 0;
}//end the current function called main
