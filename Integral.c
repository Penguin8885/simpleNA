#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double function(double x){
	return 1.0 / (1.0 + x);
}

/*区分求積法*/
double quadrature(double (*func)(double), double range1, double range2, int step){
	int i;
	double dx;
	double sum = 0;

	dx = (range2 - range1) / step;

	for (i = 0; i < step; i++){
		sum += func(range1 + dx * i) * dx;
	}

	return sum;
}

/*台形法*/
double trapezoidal(double (*func)(double), double range1, double range2, int step){
	int i;
	double dx;
	double sum = 0;

	dx = (range2 - range1) / step;

	for (i = 0; i < step; i++){
		sum += (func(range1+dx*i) + func(range1+dx*(i+1))) * dx / 2.0;
	}

	return sum;
}

/*シンプソン法*/
double simpson(double (*func)(double), double range1, double range2, int step){
	int i;
	double dx;
	double sum = 0;

	dx = (range2 - range1) / step;

	for (i = 0; i < step; i++){
		sum += (func(range1+dx*i) + 4.0*func(range1+dx*(i+0.5)) + func(range1+dx*(i+1))) * dx / 6.0;
	}

	return sum;
}

/*シンプソン法 3/8公式*/
double simpson3_8(double (*func)(double), double range1, double range2, int step){
	int i;
	double dx;
	double sum = 0;

	dx = (range2 - range1) / step;

	for (i = 0; i < step; i++){
		sum += (func(range1+dx*i) + 3.0*func(range1+dx*(i+1.0/3.0)) + 3.0*func(range1+dx*(i+2.0/3.0)) + func(range1+dx*(i+1))) * dx / 8.0;
	}

	return sum;
}


int main(void){
	double s = 100;
	int step;
	double Q,T,S,S38;
	double ans;

	ans = log(1 + s);
	printf("\nans = %.9lf\n\n", ans);

	for(step = 10; step <= 10000; step *= 10){
		printf("---- step = %d ----\n", step);

		Q = quadrature(function, 0, s, step);
		T = trapezoidal(function, 0, s, step);
		S = simpson(function, 0, s, step);
		S38 = simpson3_8(function, 0, s, step);

		printf("quadrature  : result = %.9lf, error = %.9lf\n", Q, fabs(ans - Q));
		printf("trapezoidal : result = %.9lf, error = %.9lf\n", T, fabs(ans - T));
		printf("simpson     : result = %.9lf, error = %.9lf\n", S, fabs(ans - S));
		printf("simpson 3/8 : result = %.9lf, error = %.9lf\n", S38, fabs(ans - S38));
	}

	return EXIT_SUCCESS;
}