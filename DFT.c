#define _CRT_SECURE_NO_WARNINGS
#define _USE_MATH_DEFINES

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/* 2次元配列メモリ確保用関数 */
double **malloc_2d(int row, int column){
     int i;
     double **ptr;

     ptr = (double **)calloc(row, sizeof(double *));
     if (ptr == NULL) return NULL;
     for (i = 0; i < row; i++){
          ptr[i] = (double *)calloc(column, sizeof(double));
          if (ptr[i] == NULL) return NULL;
     }
     return ptr;
}

/* 2次元配列メモリ開放用関数 */
void free_2d(double **ptr, int num){
     int i;
     for (i = 0; i < num; i++){
          free(ptr[i]);
     }
     free(ptr);
}

/* フーリエ変換 */
void fourier_transform(double **data, double **fourier, int num){
     int l, k;
     double dtime, dfreq, omega0;

     omega0 = (2.0 * M_PI) / num;
     dtime = data[1][0] - data[0][0];
     dfreq = 1 / (dtime * num);

     for (l = 0; l < num; l++){
          fourier[l][1] = fourier[l][2] = 0.0;
          for (k = 0; k < num; k++){
               fourier[l][1] += data[k][1] * cos(l*k*omega0);
               fourier[l][2] += data[k][1] * sin(l*k*omega0);
          }
          fourier[l][1] *= dtime;
          fourier[l][2] *= -dtime;
          fourier[l][0] = dfreq * l;
     }
}

/* 逆フーリエ変換 */
void inverse_fourier_transform(double **fourier, double **data, int num){
     int k, l;
     double dtime, time, dfreq, omega0;

     omega0 = (2.0 * M_PI) / num;
     dfreq = fourier[1][0] - fourier[0][0];
     dtime = 1 / (dfreq * num);
     time = dtime * num;

     for (k = 0; k < num; k++){
          data[k][1] = 0.0;
          for (l = 0; l < num; l++){
               data[k][1] += (fourier[l][1] * cos(l*k*omega0)) - (fourier[l][2] * sin(l*k*omega0));
          }
          data[k][1] /= time;
          data[k][0] = dtime * k;
     }
}

int main(int argc, char **argv){
     int line = 0, i;
     char buf[1024];
     double **data = NULL, **fourier = NULL;
     //double **data2 = NULL;
     FILE *fp;

     if (argc != 2){
          fprintf(stderr, "不適切なコマンドライン引数\n");
          return EXIT_FAILURE;
     }
     if ((fp = fopen(argv[1], "r")) == NULL){
          fprintf(stderr, "ファイルを開けません\n");
          return EXIT_FAILURE;
     }

     while (fgets(buf, sizeof(buf), fp) != NULL){
          if (buf[0] == '#') continue;
          line++;
     }
     if (feof(fp) == 0){
          fprintf(stderr, "データ読み込み失敗\n");
          return EXIT_FAILURE;
     }
     fseek(fp, 0, SEEK_SET);

     if (((data = malloc_2d(line, 2)) == NULL) || ((fourier = malloc_2d(line, 3)) == NULL) /*|| ((data2 = malloc_2d(line, 3)) == NULL)*/){
          fprintf(stderr, "メモリ確保失敗\n");
          return EXIT_FAILURE;
     }

     for (i = 0; i < line; i++){
          fgets(buf, sizeof(buf), fp);
          if (buf[0] == '#') continue;
          data[i][0] = atof(strtok(buf, ","));
          data[i][1] = atof(strtok(NULL, "\n"));
     }

     fourier_transform(data, fourier, line);
     //inverse_fourier_transform(fourier, data2, line);
     for (i = 0; i < line; i++){
          fprintf(stdout, "%lf, %lf\n", fourier[i][0], sqrt((fourier[i][1] * fourier[i][1]) + (fourier[i][2] * fourier[i][2])) * 10E3);
          //fprintf(stdout, "%lf, %lf\n", data2[i][0], data2[i][1]);
     }

     free_2d(data, line);
     free_2d(fourier, line);
     return EXIT_SUCCESS;
}
