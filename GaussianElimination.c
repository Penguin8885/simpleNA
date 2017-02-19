#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct MATRIX{
	int row;
	int column;
	double **data;
} MAT, *MATP;

MATP malloc_matrix(int row, int column){
	int i;
	MATP m;

	if (row <= 0 || column <= 0) exit(EXIT_FAILURE);
	if ((m = (MATP)malloc(sizeof(MAT))) == NULL) exit(EXIT_FAILURE);
	m->row = row;
	m->column = column;
	m->data = (double**)malloc(sizeof(double*) * row);
	for (i = 0; i < row; i++){
		if ((m->data[i] = (double*)calloc(column, sizeof(double))) == NULL) exit(EXIT_FAILURE);
	}
	return m;
}

void free_matrix(MATP m){
	int i;

	for (i = 0; i < m->row; i++){
		free(m->data[i]);
	}
	free(m->data);
	free(m);
}

void print_matrix(MATP m){
	int i, j;
	for (i = 0; i < m->row; i++){
		for (j = 0; j < m->column; j++){
			printf("%lf ", m->data[i][j]);
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

	if ((fp = fopen(filename, "r")) == NULL) exit(EXIT_FAILURE);

	//get row & column size
	if (fgets(buf, sizeof(buf), fp) == NULL) exit(EXIT_FAILURE);
	strtok(buf, ",\t\n");
	while (strtok(NULL, ",\t\n") != NULL) column++;
	while (fgets(buf, sizeof(buf), fp) != NULL) row++;
	rewind(fp);

	//input data to matrix
	m = malloc_matrix(row, column);
	for (i = 0; i < m->row; i++){
		fgets(buf, sizeof(buf), fp);
		m->data[i][0] = atof(strtok(buf, ",\t\n"));
		for (j = 1; j < m->column; j++){
			m->data[i][j] = atof(strtok(NULL, ",\t\n"));
		}
	}

	fclose(fp);

	return m;
}

int power_method(MATP a, double *l, MATP x){
	int i, j;
	double absx = 0;
	double absv;
	double e;
	e = pow(2.0, -30.0);

	MATP v;
	v = malloc_matrix(x->row, 1);

	if (a->row != a->column || a->column != x->row) return EXIT_FAILURE;

	for (i = 0; i < x->row; i++){
		absx += x->data[i][0] * x->data[i][0];
	}
	absx = sqrt(absx);
	for (i = 0; i < x->row; i++){
		x->data[i][0] /= absx;
	}

	do{
		//v = Ax
		for (i = 0; i < a->row; i++){
			v->data[i][0] = 0;
			for (j = 0; j < a->column; j++){
				v->data[i][0] += a->data[i][j] * x->data[j][0];
			}
		}

		//l = (x,v)
		*l = 0;
		for (i = 0; i < x->row; i++){
			*l += x->data[i][0] * v->data[i][0];
		}

		//x = v/|v|
		absv = 0;
		for (i = 0; i < v->row; i++){
			absv += v->data[i][0] * v->data[i][0];
		}
		absv = sqrt(absv);
		for (i = 0; i < v->row; i++){
			x->data[i][0] = v->data[i][0] / absv;
		}
	} while (fabs(absv - fabs(*l)) > e);

	free_matrix(v);
	return EXIT_SUCCESS;
}

int main(void){
	MATP a, x;
	double l;
	int r;

	a = csv2matrix("a.csv");
	x = csv2matrix("x.csv");
	puts("--- A --- ");
	print_matrix(a);
	puts("--- inital x --- ");
	print_matrix(x);

	r = power_method(a, &l, x);
	puts("--- Eigenvalue --- ");
	printf("%lf\n", l);
	puts("--- Eigenvector --- ");
	print_matrix(x);

	free_matrix(a);
	free_matrix(x);
	return r;
}