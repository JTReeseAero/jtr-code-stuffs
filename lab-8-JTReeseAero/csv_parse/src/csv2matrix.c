/*
csvinfo - reads CSV data from input file(s) and reports the number
          of fields and rows encountered in each file
*/

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

struct matrix_write{
  int r;
  int c;
  short usefloat;
  int **mat;
  float **matf;
};



void cb1 (void *s, size_t len, void *data) {
  ((struct counts *)data)->fields++;
}

void cb2 (int c, void *data) {
  ((struct counts *)data)->rows++;
}

void storfield (void *s, size_t len, void *data){
  struct matrix_write *mw = ((struct matrix_write *)data);
  if(1 == mw->usefloat){
    float v = atof(s);
    mw->matf[mw->r][mw->c] = v;
  }
  else{
    int v = atoi(s);
    mw->mat[mw->r][mw->c] = v;
  }
  mw->c++;
}

void countrow (int c, void *data){
  struct matrix_write *mw = ((struct matrix_write *)data);
  mw->r++;
  mw->c = 0;
}

static int is_space(unsigned char c) {
  if (c == CSV_SPACE || c == CSV_TAB) return 1;
  return 0;
}

static int is_term(unsigned char c) {
  if (c == CSV_CR || c == CSV_LF) return 1;
  return 0;
}


int main (int argc, char *argv[]){
 
 FILE *fp;
  struct csv_parser p;
  char buf[1024];
  size_t bytes_read;
  unsigned char options = 0;
  struct counts co = {0, 0};
  short usefloat = 0;


  if (argc < 2) {
    fprintf(stderr, "Usage: csvinfo [-s] files\n");
    exit(EXIT_FAILURE);
  }
  
  if (csv_init(&p, options) != 0) {
    fprintf(stderr, "Failed to initialize csv parser\n");
    exit(EXIT_FAILURE);
  }
  
  csv_set_space_func(&p, is_space);
  csv_set_term_func(&p, is_term);
  
  while (*(++argv)) {
    if (strcmp(*argv, "-f") == 0) {
      usefloat = 1;
      continue;
    }
    
    fp = fopen(*argv, "rb");
    if (!fp) {
      fprintf(stderr, "Failed to open %s: %s\n", *argv, strerror(errno));
      continue;
    }
    
    while ((bytes_read=fread(buf, 1, 1024, fp)) > 0) {
      if (csv_parse(&p, buf, bytes_read, cb1, cb2, &co) != bytes_read) {
        fprintf(stderr, "Error while parsing file: %s\n", csv_strerror(csv_error(&p)));
      }
    }
    
    csv_fini(&p, cb1, cb2, &co);
    
    if (ferror(fp)) {
      fprintf(stderr, "Error while reading file %s\n", *argv);
      fclose(fp);
      continue;
    }
    
    printf("%s: %lu fields, %lu rows\n", *argv, co.fields, co.rows);
  }
  

 
  co.columns = co.fields / co.rows;
  int **matr = 0;
  float **matrf = 0;
  int i;
 
 if (0 == usefloat){
    matr = malloc(sizeof(int *) * co.rows);
    for(i = 0; i < co.rows; ++i){
      matr[i] = malloc(sizeof(int) * co.columns);
    }
  }
 else{
   matrf= malloc(sizeof(float *)  * co.rows);
   for(i = 0; i < co.rows; ++i){
     matrf[i] = malloc(sizeof(float) * co.columns);
   }
 }
  /******************************************start of parsing*************************************/  
  rewind(fp);

  struct matrix_write storage;
  storage.r = 0;
  storage.c = 0;
  storage.usefloat = usefloat;
  storage.mat = matr;
  storage.matf = matrf;
  
  csv_free(&p);
  options = CSV_APPEND_NULL;
  if (csv_init(&p, options) != 0) {
    fprintf(stderr, "Failed to initialize csv parser\n");
    exit(EXIT_FAILURE);
  }
  //INVAR this is the csv code, but we are chunking through the file by 1024 bytes and parsing it. 
  while ((bytes_read=fread(buf, 1, 1024, fp)) > 0) {
    if (csv_parse(&p, buf, bytes_read, storfield, countrow, &storage) != bytes_read) {
      fprintf(stderr, "Error while parsing file: %s\n", csv_strerror(csv_error(&p)));
    }
  }

  csv_fini(&p, storfield, countrow, &storage);

  if (ferror(fp)) {
    fprintf(stderr, "Error while reading file %s\n", *argv);
    fclose(fp);
    return 1;
  }
  
  int r;
  int c;
  //INVAR The matrix prints each column and then the row
  for(r = 0; r<co.rows; r++){
    for (c = 0; c<co.columns; c++){
      if(1 == usefloat){
	printf("%f ",matrf[r][c]);
      }
     
      else{
	printf("%d " ,matr[r][c]);
      }
    }
    printf("\n");
  }

  free(matr);
  free(matrf);
  fclose(fp);
  csv_free(&p);
  exit(EXIT_SUCCESS);
}//end Main
