/*
Regression Line .c
ここには回帰直線の傾き,切片を求めるための関数定義が示されています
*/

#include<stdlib.h>

/*回帰直線の係数を求める関数
     data[][2];     //x,yのデータ
     num;          //データの個数
     *a;               //回帰直線 y = ax + b の係数aを格納する変数へのポインタ
     *b;               //回帰直線 y = ax + b の係数bを格納する変数へのポインタ
*/
int Get_RegressionLineCoefficients(double data[][2], unsigned int num, double *a, double *b){
     unsigned int i;
     double sumx, sumy, sumxy, sumx2;     //xの総和, yの総和, x*yの総和, x^2の総和
     double denominator;                         //計算式の分母

     if (num == 0) return EXIT_FAILURE;

     sumx = sumy = sumxy = sumx2 = 0;     //初期化
     for (i = 0; i < num; i++){
          sumx += data[i][0];
          sumy += data[i][1];
          sumxy += data[i][0] * data[i][1];
          sumx2 += data[i][0] * data[i][0];
     }

     denominator = (num * sumx2) - (sumx * sumx);
     *a = ((num * sumxy) - (sumx * sumy)) / denominator;
     *b = ((sumx2 * sumy) - (sumxy * sumx)) / denominator;

     return EXIT_SUCCESS;
}

/*回帰直線の切片を0として回帰直線を求める関数
     data[][2];     //x,yのデータ
     num;          //データの個数
     *a;               //回帰直線 y = ax の係数aを格納する変数へのポインタ
*/
int Get_RegressionLineSlopeWithIntercept0(double data[][2], unsigned int num, double *a){
     unsigned int i;
     double sumxy, sumx2;     //x*yの総和，x^2の総和

     if (num == 0) return EXIT_FAILURE;

     sumxy = sumx2 = 0;          //初期化
     for (i = 0; i < num; i++){
          sumxy += data[i][0] * data[i][1];
          sumx2 += data[i][0] * data[i][0];
     }

     *a = sumxy / sumx2;

     return EXIT_SUCCESS;
}

/*
ここには"regressionline.c"で定義されている関数のプロトタイプ宣言が示されています
*/

#ifndef REGRESSIONLINE_H //二重include防止
#define REGRESSIONLINE_H

int Get_RegressionLineCoefficients(double data[][2], unsigned int num, double *a, double *b);     /*回帰直線の係数を求める関数*/
int Get_RegressionLineSlopeWithIntercept0(double data[][2], unsigned int num, double *a);          /*回帰直線の切片を0として回帰直線を求める関数*/

#endif
