#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct voltage {
  int nodeV;
  double voltage;
};

struct resistance {
  int fnode_resist;
  int secnode_resist;
  double resist;
  char direction;
  double current;
};

struct loop {
  int *nodeL;
  int num_node_loop;
};

struct comment {
  char *comments;
};

struct DOTdata {
  char linetype; //C is comment, V is voltage, R is resistor, L is loop
  struct voltage v;
  struct resistance r;
  struct loop L;
  struct comment c;
};

struct matrix{
  int r;
  int c;
  double **matf;
};

//***********************************************************************
int data_free(struct DOTdata *dd){
  if (dd->linetype == 'C'){
    free(dd->c.comments);
  }

  else if(dd->linetype == 'L'){
    free(dd->L.nodeL);
  }
  return 0;
}

//***********************************************************************

int is_voltage(const char *line){
  if(strstr(line, " [label = \"V")){
      return 1;
  }

  else{return 0;}     
}

//***********************************************************************

int is_resist(const char *line){
  if(strstr(line, " [label = \"R")){
    return 1;
  }

  else{return 0;}
}

//***********************************************************************

int is_loop(const char *line){
  if(strstr(line, "//")){
    return 1;
  }

  else{return 0;}
}

//***********************************************************************
double find_val(const char *line){
  const char *bob;  
  bob = strchr(line, '=');
  if(bob == NULL){
    return -1;
  }
  
  bob = strchr(++bob, '=');
  if(bob == NULL){
    return -1;
  }

  double val = atof(++bob);
  return val;
}

//***********************************************************************
int volt_val(const char *line, struct DOTdata *dd){
  int node = atoi(line);
  double volt = find_val(line);
  
  if (volt < 0){
    printf("There is a problem with the finding function\n");
    return 1;
  }

  dd->linetype = 'V';
  dd->v.voltage = volt;
  dd->v.nodeV = node;
  //  printf("Node = %d and the voltage is %lf\n", node, volt);
  return 0;  
}

//***********************************************************************
int resist_val(const char *line, struct DOTdata *dd){
  int fnode = atoi(line);
  int secnode = 0;
  const char *right = strstr(line, "->");
  const char *left = strstr(line, "<-");
  if (right == NULL && left == NULL){
    return -1;
  }

  char direct;
  if(right != NULL){
    direct = 'R';
    right += 2;
    secnode = atoi(right);
  }
  else{
    direct = 'L';
    left += 2;
    secnode = atoi(left);
  }

  double resist = find_val(line);

  dd->linetype = 'R';
  dd->r.fnode_resist = fnode;
  dd->r.secnode_resist = secnode;
  dd->r.resist = resist;
  dd->r.direction = direct;

  //  printf("Node 1 = %d and Node 2 = %d and the resistance is %lf in the direction %c\n\n", fnode, secnode, resist, direct);
  return 0;
}

//***********************************************************************
int loop(const char *line, struct DOTdata *dd){
  int node = 0;
  int count = 0;
  line += 2;
  const char *orig = line;
 
  while(*line){
    count ++;
    line = strstr(line, "->");
    if (line == NULL){
      break;
    }
    line += 2;
  }

  line = orig;
  dd->L.nodeL = (int *)calloc(count, sizeof(int));
  count = 0;
  while(*line){
    node = atoi(line);
    dd->L.nodeL[count] = node;
    count ++;
    // printf("Node %d to ",node);
    line = strstr(line, "->");
    if (line == NULL){
      break;
    }
    line += 2;
  }
  
  dd->linetype = 'L';
  dd->L.num_node_loop = count;
  printf("\n");
  return 0;
}

//***********************************************************************
int comment (const char *line, struct DOTdata *dd){
  dd->linetype = 'C';
  dd->c.comments = (char*)calloc(strlen(line)+1, sizeof(char));
  strcpy(dd->c.comments, line); 
  return 0;
}

//***********************************************************************
int print_struct(struct DOTdata *dd){
  if(dd->linetype == 'R'){
    printf("Node 1 = %d and Node 2 = %d and the resistance is %lf in the direction %c\n\n", dd->r.fnode_resist, dd->r.secnode_resist, dd->r.resist, dd->r.direction);
  }

  else if(dd->linetype == 'V'){
    printf("Node = %d and the voltage is %lf\n", dd->v.nodeV, dd->v.voltage);
  }

  else if(dd->linetype == 'L'){ 
    int i = 0;
    for(i = 0; i < dd->L.num_node_loop; i++){
      printf("Node %d to ",dd->L.nodeL[i]);
    }
    printf("\nNumber of Node elements is %d\n", dd->L.num_node_loop);
  }

  else if(dd->linetype == 'C'){
    printf("%s\n", dd->c.comments);
  }

  return 0;
}

//***********************************************************************
int file_out(struct DOTdata *dd, int num, const char *outfile){
  FILE *fp;
  fp = fopen(outfile, "w");
  if (fp == NULL){
    printf("There was an error with fopen\n");
  }

  int j = 0;
  for(j = 0; j < num; j++){
    if(dd[j].linetype == 'R'){
      fprintf(fp, "%d %s %d [label = \"I = %0.4lf\"];\n", dd[j].r.fnode_resist, (dd[j].r.direction == 'R') ? "->" : "<-", dd[j].r.secnode_resist, dd[j].r.current);
    }
    
    else if(dd[j].linetype == 'V'){
      fprintf(fp, "%d [label = \"V = %0.4lf\"];\n", dd[j].v.nodeV, dd[j].v.voltage);
    }
    
    else if(dd[j].linetype == 'C'){
      fprintf(fp, "%s", dd[j].c.comments);
    }
  }

  fclose(fp);
  return 0;
}

//***********************************************************************
int allocate_matrix(int row, int column, struct matrix *mw){
  mw->r = row;
  mw->c = column;
  int i = 0;

  mw->matf = calloc(row,sizeof(double *));
  for(i = 0; i < row; ++i){
    mw->matf[i] = calloc(column, sizeof(double));
  }

  return 0;
}

//***********************************************************************
int init_matrix(struct matrix *mw){
  mw->r = 0;
  mw->c = 0;
  mw->matf = NULL;

  return 0; 
}

//***********************************************************************
int print_matrix(struct matrix *mw){
  int r = 0;
  int c = 0;

  for(r = 0; r<mw->r; r++){
    for (c = 0; c<mw->c; c++){
      printf("%f\t",mw->matf[r][c]);
    }
    printf("\n");
  }
  return 0;
}

//***********************************************************************
int gauss_jordan(struct matrix *mw){
  int j = 0;
  int i = 0;
  int k = 0;
  double c = 0;
  int n = mw->r;

  printf("\n\n gauss r = %d and c = %d\n\n", mw->r, mw->c);
  // printf("\n\n column value in gauss = %d \n\n", n);

  for(j=0; j<n; j++){
    for(i=0; i<n; i++){
      if(i!=j){
	c = mw->matf[i][j]/mw->matf[j][j];
	for(k=0; k<n+1; k++){
	  mw->matf[i][k] -= c*mw->matf[j][k];
	}
      }
    }
  }

  /* double x[100];

  for(i=0; i<n; i++){
    x[i] = mw->matf[i][n]/mw->matf[i][i];
    printf("\n x%d= %lf\n",i,x[i]);
  }
  */
  return 0;
}

//***********************************************************************
int store_current(struct matrix *mw, struct DOTdata *dd, int lines){
  int j = 0;
  int num_current = 0;
  int n = mw->r;
  printf("\n\n store r = %d and c = %d\n\n", mw->r, mw->c);

  for(j = 0; j < lines; j++){
    if (dd[j].linetype == 'R'){
      dd[j].r.current = mw->matf[num_current][n]/mw->matf[num_current][num_current];
      num_current++;
    }
  }

  return 0;
}

//***********************************************************************
int construct_matrix(struct DOTdata *dd, int lines,  struct matrix *mat){
  int edges = 0;
  int num_loop = 0;
  int max = 0;
  int j = 0;
  int v1node = 0;
  int v2node = 0;
  double v1 = 0;
  double v2 = 0;
  init_matrix(mat);

  for(j = 0; j< lines; j++){
   
    if(dd[j].linetype == 'R'){
      if(dd[j].r.fnode_resist > max){
	max = dd[j].r.fnode_resist;
      }

      if(dd[j].r.secnode_resist > max){
	max = dd[j].r.secnode_resist;
      }
      edges++;
    }

    else if(dd[j].linetype == 'L'){
      num_loop++;
    }

    else if(dd[j].linetype == 'V'){
      if(v1node == 0){
	v1node = dd[j].v.nodeV;
	v1 = dd[j].v.voltage;
      }
      else{
	v2node = dd[j].v.nodeV;
	v2 = dd[j].v.voltage;
      }

      if (dd[j].v.nodeV > max){
	max = dd[j].v.nodeV;
      }
    }

    else if(dd[j].linetype == 'C'){
      //do nothing???
    }
  }
  printf("\n\n v1 = %lf v2 = %lf v1node = %d v2node = %d\n\n", v1, v2, v1node, v2node);
  int row = num_loop + (max - 2);

  allocate_matrix(row, edges+1, mat);

  int k = 0;
  int q = 0;
  int resistcount = 0;
  int *noderow = calloc(max - 2, sizeof(int));
  int nrcount = 0;
  int h = 0;
  int loopindex = max - 2;

  for(k = 0; k < lines; k++){
    if (dd[k].linetype == 'R'){
      if(dd[k].r.fnode_resist != v1node && dd[k].r.fnode_resist != v2node){
	int found = -1;
	for(q = 0; q < nrcount; q++){
	  if(dd[k].r.fnode_resist == noderow[q]){
	    found = q;
	    break;
	  }
	}
	if(found == -1){
	  found = nrcount;
	  noderow[nrcount] = dd[k].r.fnode_resist;
	  nrcount++;
	}
	if(dd[k].r.direction == 'R'){
	  mat->matf[found][resistcount] = 1;
	}
	else{
	  mat->matf[found][resistcount] = -1;
	}
      }
      if(dd[k].r.secnode_resist != v1node && dd[k].r.secnode_resist != v2node){
	int found = -1;
        for(q = 0; q < nrcount; q++){
          if(dd[k].r.secnode_resist == noderow[q]){
            found = q;
            break;
          }
        }
        if(found == -1){
          found = nrcount;
          noderow[nrcount] = dd[k].r.secnode_resist;
          nrcount++;
        }
        if(dd[k].r.direction == 'L'){
          mat->matf[found][resistcount] = 1;
        }
        else{
          mat->matf[found][resistcount] = -1;
        }
      }
      resistcount++;
    }
    //=====================================
    else if(dd[k].linetype == 'L'){
      for(q = 0; q < dd[k].L.num_node_loop; q++){
	int resistindex = 0;
	int from_node = dd[k].L.nodeL[q];
	int to_node = (q < (dd[k].L.num_node_loop - 1)) ? dd[k].L.nodeL[q+1] : dd[k].L.nodeL[0];
	if(from_node == v1node && to_node == v2node){
	  mat->matf[loopindex][edges] = v2 - v1;
	}
	else if(from_node == v2node && to_node == v1node){
	  mat->matf[loopindex][edges] = v1 - v2;
	}
	for(h = 0; h < lines; h++){
	  if (dd[h].linetype == 'R'){
	    if(dd[h].r.fnode_resist == from_node && dd[h].r.secnode_resist == to_node){
	      if(dd[h].r.direction == 'R'){
		mat->matf[loopindex][resistindex] = dd[h].r.resist;
	      }
	      else{
		mat->matf[loopindex][resistindex] = -dd[h].r.resist;
	      }
	    }
	    else if(dd[h].r.fnode_resist == to_node && dd[h].r.secnode_resist == from_node){
	      if(dd[h].r.direction == 'L'){
                mat->matf[loopindex][resistindex] = dd[h].r.resist;
              }
              else{
                mat->matf[loopindex][resistindex] = -dd[h].r.resist;
              }
	    }
	    resistindex++;
	  }
	}
      }
      loopindex++;
    }
  }

  double temp = 0;

  for(k = 0; k < mat->r; k++){

    if(mat->matf[k][k] == 0){
      //printf("\n\n row %d is bad\n\n",k);
      for(q = 1; q < (mat->r-k); q++){

	if(mat->matf[k+q][k] !=0){
	  int newrow = k+q;
	  //printf("\n\nnewrow = %d\n\n", newrow);
	  int oldrow = k;
	  //printf("\n\noldwrow = %d\n\n", oldrow);
	  for(h = 0; h < mat->c; h++){
	    //printf("\n\nhere\n\n");
	    temp = mat->matf[newrow][h];
	    mat->matf[newrow][h] = mat->matf[oldrow][h];
	    mat->matf[oldrow][h] = temp;
	  }
	}
      }
    }
  }



  print_matrix(mat);
  gauss_jordan(mat);
  store_current(mat, dd, lines);

  return 0;
}

//***********************************************************************
int fileopen(const char *filename){
  FILE *fp;
  fp = fopen(filename, "r");
  if (fp == NULL){
    printf("There was an error with fopen\n");
  }

  struct matrix mat;  
  int lim = 0;
  char line[100];
  int linecount = 0;
  
  while(lim < 1){
    if(fgets(line, 100, fp) == NULL){
      if (!feof(fp)){
	printf("There was an error with fgets\n");
	fclose(fp);
	return 1;
      }
    break;
    }//END if
    linecount++; 
  }
  struct DOTdata *dd = (struct DOTdata *)calloc(linecount, sizeof(struct DOTdata));  
  
  linecount = 0;
  rewind(fp);
  while (lim < 1){
    if(fgets(line, 100, fp) == NULL){
      if (!feof(fp)){
	printf("There was an error with fgets\n");
	fclose(fp);
	return 1;
      }
      break;
    }//END if
    //    printf("Line %d\t is %s", linecount, line);
    if(is_voltage(line)){
      volt_val(line, dd + linecount);
    }
    
    else if(is_resist(line)){
      resist_val(line, dd + linecount);
    }

    else if(is_loop(line)){
      loop(line, dd + linecount);
    }

    else{
      comment(line, dd + linecount);
    }

    linecount++;  
  }// end while
  fclose(fp);
  int i = 0;
  for(i = 0; i < linecount; i++){
    print_struct(dd + i);
  }

  construct_matrix(dd, linecount, &mat);
  file_out(dd, linecount, "ans.dot");


  return 0;
}

//***********************************************************************
int main(int argc, char **argv){

  if (argc > 2){
    printf("Sorry you entered too many command line arguments\n");
    return 1;
  }

  else if(argc < 2){
    printf("Sorry you didn't enter in enough command line arguments\n");
    return 2;
  }

  fileopen(argv[1]);


  return 0;
}// end main
