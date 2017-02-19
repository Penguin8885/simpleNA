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



/*マシンイプシロンを取り除く関数*/
void MachineEpsilon2Zero(double *a){
	static double eps = 0;
	if (eps == 0) eps = pow(2.0, -50.0);
	if (fabs(*a) <= eps) *a = 0;
}

/*columnにおけるピボット(最大絶対値)を検索してその行数を戻り値とする関数*/
int Search_Pivot(double **matrix, int size, int column){
	int i, max_row;

	column--;	//インデックスとして使用するためにデクリメント

	max_row = column;
	for (i = column + 1; i < size; i++){
		if (fabs(matrix[i][column]) > fabs(matrix[max_row][column])) max_row = i;
	}

	return max_row + 1;	//指定数列のインデックスで扱える形から元に戻す
}

/*行列式を計算する関数(部分ピボット選択付きガウスの消去法)*/
int Determinant(int size, double **left, double *solution){
	int i, j, k;
	double **A = NULL;
	int pivot;					//ピボット
	double c;					//行列の係数を消去するための数
	double tmp;

	if (size < 1) return EXIT_FAILURE;	//行列の大きさが適切で無いとき error

	/*行列のコピーを作成(元の行列のアドレス参照先に影響を与えないため)*/
	if ((A = (double**)malloc(size*sizeof(double*))) == NULL) return EXIT_FAILURE;
	for (i = 0; i < size; i++){
		if ((A[i] = (double*)malloc(size*sizeof(double))) == NULL) return EXIT_FAILURE;
		for (j = 0; j < size; j++){
			A[i][j] = left[i][j];
		}
	}

	/*前進消去*/
	for (i = 0; i < size; i++){
		/*ピボットを検索して行を入れ替える*/
		pivot = Search_Pivot(A, size, i + 1);
		for (j = 0; j < size; j++){
			tmp = A[i][j];
			A[i][j] = A[pivot - 1][j];
			A[pivot - 1][j] = tmp;
		}

		if (A[i][i] == 0){
			*solution = 0;
			return EXIT_SUCCESS;
		}

		/*行に関する計算*/
		for (j = i + 1; j < size; j++){
			c = A[j][i] / A[i][i];	//係数の比の計算

			/*行列Aに関する処理*/
			for (k = i; k < size; k++){
				A[j][k] -= c * A[i][k];
				MachineEpsilon2Zero(&A[j][k]);	//マシンイプシロンによる誤差の修正
			}

		}
	}

	/*解計算(対角要素の掛け算)*/
	*solution = 1;
	for (i = 0; i < size; i++){
		*solution *= A[i][i];
	}

	/*メモリ解放*/
	for (i = 0; i < size; i++) free(A[i]);
	free(A);

	return EXIT_SUCCESS;	//正常終了
}

int main(void){
	int i;
	MATP a;
	double s;

	a = csv2matrix("a.csv");
	puts("--- A ---");
	print_matrix(a);


	Determinant(a->row, a->data, &s);
	puts("--- det(A) ---");
	printf("%lf\n", s);

	free_matrix(a);
	return EXIT_SUCCESS;
}