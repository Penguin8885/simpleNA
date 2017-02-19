#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double function(double x){
	return x*x - 1.0/16.0;
}
double dfunction(double x){
	return 2*x;
}

int NewtonsMethod(double (*func)(double),double (*dfunc)(double), double init, int repeat){
	int i;
	double x;
	double y, dy;
	double eps;
	
	x = init;
	eps = pow(2.0, -20.0);
	
	for(int i; i < repeat; i++){
		y = func(x);
		dy = dfunc(x);
		if(fabs(y) < eps) break;
		if(dy == 0) return EXIT_FAILURE;
		
		x = x - y/dy;
	}
	
	if(fabs(func(x)) < 1){
		printf("%.8lf\n", x);
		return EXIT_SUCCESS;
	}
	else{
		return EXIT_FAILURE;
	}
}

int main(void){
	NewtonsMethod(function, dfunction, 0.5, 10000);
	return 0;
}