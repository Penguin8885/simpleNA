#include <stdio.h>
#include <math.h>

double function(double x){
	return x*x - 1.0/16.0;
}

void BisectionMethod(double (*func)(double), double range1, double range2, double dx, int repeat){
	int i;
	double s;
	double a, b, median;
	
	for(s = range1; (s + dx) <= range2; s += dx){
		if((func(s) * func(s + dx)) > 0) continue;

		a = s;
		b = s + dx;
		for(i = 0; i < repeat; i++){
			median = (a + b) / 2.0;
			
			if((func(a) * func(median)) <= 0){
				b = median;
			}else {
				a = median;
			}
		}
		
		printf("%.8lf\n", median);
	}
}

int main(void){
	BisectionMethod(function, 0.0, 1.0, 0.0001, 10000);
	return 0;
}