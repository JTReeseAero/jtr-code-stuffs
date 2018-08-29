#include <stdio.h>

void initialize_matrix(int M, int N, int nnz, int myMatrix[][N]){
  int r;
  int m,n;
  int running_nnz = 0;

  printf("Made a matrix:\n");

  for (m = 0; m < M; m++){
    for (n = 0; n < N; n++){
       
      if( ((M*N) - (m*N+n)) == (nnz - running_nnz)){
	
	while((r = rand()%100) == 0){
	  printf("rand is %d\n", r);
	}
	mymatrix[m][n] = r;
	running_nnz++;
      }

    }
  }
  return;
}
//*********************************************************
void initialize_COO_matrix(int M, int N, int denseMatrix[][N], struct coo_matrix_ *cooMatrix){
  int m = 0;
  int n = 0;
  int running_nnz = 0;

  
  for (m = 0; m < M; m++){
    for (n = 0; n < N; n++){
      if (denseMatrix[m][n] == 0){
	continue;
      }// end if
      //else we have a non zero value to store
      cooMatrix->rows[running_nnz] = m;
      cooMatrix->columns[running_nnz] = n;
      cooMatrix->values[running_nnz] = denseMatrix[m][n];
      
      running_nnz++;
    }
  }
  
  printf("COO format:\n");
  printf("unsigned rows[%d] = { ", cooMatrix->nnz);
  
  for (running_nnz = 0; running_nnz < cooMatrix->nnz; running_nnz++){
    printf(" %d", cooMatrix->rows[running_nnz]);
  }
  
  printf("COO format:\n");
  printf("unsigned rows[%d] = { ", cooMatrix->nnz);
  for (running_nnz = 0; running_nnz < cooMatrix->nnz; running_nnz++){
    printf(" %d", cooMatrix->rows[running_nnz]);
  }
  
  
  printf("COO format:\n");
  printf("unsigned rows[%d] = { ", cooMatrix->nnz);
  for (running_nnz = 0; running_nnz < cooMatrix->nnz; running_nnz++){
    printf(" %d", cooMatrix->rows[running_nnz]);
  }

  
  return;
}
//********************************************************
void COO_find_value(int row, int col, struct coo_Matrix_ *coo_matrix){
  int i;
  int result;

  printf("looking unti nnz of %d\n", coo_matrix->nnz);

  for( i = 0; i < coo_matrix->nnz; i++){
    printf("found row %d col %d has value %d...\n", coo_matrix->rows[i], coo_matrix->columns[i], coo_matrix->values[i]);

    if((coo_matrix->rows[i] == row) && (coo_matrix->columns[i] == col)){
      result = coo_matrix->values[i];
      break;
    }
    else{
      result = 0;
    }
  }

  printf("the value at (%d, %d) is %d\n", row, col, result); 
  return ;
}

typedef struct csr_matrix_{
  int nrows;
  int nnz;
  unsigned int *row_offsets;
  unsigned int *columns;
  unsigned int *values;
};

void initialize_CSR_matrix(int N, int denseMatrix[][N], struct csr_matrix_ *csrMatrix){
  int m = 0;
  int n = 0;
  running_nnz = 0;

  for(m = 0; m < csrMatrix->nrows; m++){
    csrMatrix->row_offsets[m] = running_nnz;
    for(n = 0; n < N; n++){
      if (denseMatrix[m][n] == 0){
	continue;
      }
      csrMatrix->columns[running_nnz] = n;
      csrMatrix->values[running_nnz] = denseMatrix[m][n];
      running_nnz++;
    }
  }

  csrMatrix->row_offsets[m++] = running_nnz;
  
  assert(csrMatrix->row_offsets[csrMatrix->nrows] == csrMatri->nnz);

  return;
}


int main (){
  initialize_CSR_matrix(N, denseMatrix, &csr_matrix);


  return 0;
}//end main.
