#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "matrix.c"

typedef struct MATRIX{
	int row;
	int column;
	double **data;
} MAT, *MATP;

MATP malloc_matrix(int row, int column){
	int i;
	MATP m;

	if (row <= 0 || column <= 0) exit(EXIT_FAILURE);
	if((m = (MATP)malloc(sizeof(MAT))) == NULL) exit(EXIT_FAILURE);
	m->row = row;
	m->column = column;
	m->data = (double**)malloc(sizeof(double*) * row);
	for(i = 0; i < row; i++){
		if((m->data[i] = (double*)calloc(column, sizeof(double))) == NULL) exit(EXIT_FAILURE);
	}
	return m;
}

void free_matrix(MATP m){
	int i;

	for(i = 0; i < m->row; i++){
		free(m->data[i]);
	}
	free(m->data);
	free(m);
}

void print_matrix(MATP m){
	int i, j;
	for(i = 0; i < m->row; i++){
		for(j = 0; j < m->column; j++){
			printf("%0.3lf ", m->data[i][j]);
		}
		putchar('\n');
	}
}

MATP csv2matrix(char* filename){
	int i, j;
	MATP m;
	int row = 1, column = 1;
	FILE *fp;
	char buf[2048];

	if((fp = fopen(filename, "r")) == NULL) exit(EXIT_FAILURE);

	//get row & column size
	if(fgets(buf, sizeof(buf), fp) == NULL) exit(EXIT_FAILURE);
	strtok(buf, ",\t\n");
	while(strtok(NULL, ",\t\n") != NULL) column++;
	while(fgets(buf, sizeof(buf), fp) != NULL) row++;
	rewind(fp);

	//input data to matrix
	m = malloc_matrix(row, column);
	for(i = 0; i < m->row; i++){
		fgets(buf, sizeof(buf), fp);
		m->data[i][0] = atof(strtok(buf, ",\t\n"));
		for(j = 1; j < m->column; j++){
			m->data[i][j] = atof(strtok(NULL, ",\t\n"));
		}
	}

	fclose(fp);

	return m;
}