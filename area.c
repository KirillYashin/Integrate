#include <stdio.h>
#include <string.h>
#include <math.h>

extern float f1(float x);
extern float f2(float x);
extern float f3(float x);
static int iter = 0;

float root(float f(float), float g(float), float a, float b, float eps1) {
	float x1 = a, x2 = b, x3, tmp;
	do {
		iter++;
		tmp = x2;
		x3 = x2 - (f(x2) - g(x2)) * (x1 - x2) / ( f(x1) - g(x1) - f(x2) + g(x2) );
		x1 = x2;
		x2 = x3;
	} while (fabs(x3 - tmp) > eps1);
	return x3;
}

float integral(float f(float), float a, float b, float eps2) {
	float n = 1/eps2;
	float h = (b - a) / n;
	float sum1 = 0, sum2 = 0;
	for (int i = 1; i < n; i += 2)
		sum1 += 4*f(a + i*h);
	for (int i = 2; i < n; i += 2)
		sum2 += 2*f(a + i*h);
	float integral = (h / 3) * (f(a) + sum1 + sum2 + f(b));
	return fabs(integral);
}

// e^x+2; -2x+8; -5/x
int main (int argc, char* argv[]) {
	if (argc > 1) {
		if (!strcmp(argv[1], "-help"))
			printf("%s\n%s\n%s\n%s\n", "-abs		abscissas of intersections", 
			"-iter		number of iterations", "-r		test root", "-i		test integral");
	}
	for (int i = 1; i < argc; i++) {
		if(!strcmp(argv[i], "-r")) {
			int fir, sec; float a, b, eps1;
			printf("Enter the numbers of the functions and the actual parameters to calculate the root.\n");
			scanf("%i %i %f %f %f", &fir, &sec, &a, &b, &eps1);
			if ( ( (fir == 1) && (sec == 2) ) || ( (sec == 2) && (fir == 1) ) )
				printf("%f\n", root(f1, f2, a, b, eps1));
			if ( ( (fir == 1) && (sec == 3) ) || ( (sec == 3) && (fir == 1) ) )
				printf("%f\n", root(f1, f3, a, b, eps1));
			if ( ( (fir == 2) && (sec == 3) ) || ( (sec == 3) && (fir == 2) ) )
				printf("%f\n", root(f2, f3, a, b, eps1));
			}
		}
	for (int i = 1; i < argc; i++)
		if(!strcmp(argv[i], "-i")) {
			int func; float a, b, eps2;
			printf("Enter the number of the function and the actual parameters to calculate the integral.\n");
			scanf("%i %f %f %f", &func, &a, &b, &eps2);
			if ( func == 1 )
				printf("%f\n", integral(f1, a, b, eps2));
			if ( func == 2 )
				printf("%f\n", integral(f2, a, b, eps2));
			if ( func == 3 )
				printf("%f\n", integral(f3, a, b, eps2));
			}

	float eps1 = 0.001, eps2 = 0.001;
	float a = -3; float b = -2;
	float x1 = root(f1, f3, a, b, eps1);
	a = -1, b = -0.1;
	float x2 = root(f2, f3, a, b, eps1);
	a = 1, b = 2;
	float x3 = root(f1, f2, a, b, eps1);
	for (int i = 1; i < argc; i++)
		if(!strcmp(argv[i], "-iter"))
			printf("number of iterations is %i\n", iter);
	for (int i = 1; i < argc; i++)
		if(!strcmp(argv[i], "-abs"))
			printf("intersections:\nx1 = %f\nx2 = %f\nx3 = %f\n", x1, x2, x3);
	
	float part_1;
	float part_2;
	if ( (x1 <= x2) && (x2 <= x3) ) {
		part_1 = fabs(integral(f1, x1, x2, eps2) - integral(f3, x1, x2, eps2));
		part_2 = fabs(integral(f1, x2, x3, eps2) - integral(f2, x2, x3, eps2));
	}
	if ( (x1 <= x3) && (x3 <= x2) ) {
		part_1 = fabs(integral(f1, x1, x3, eps2) - integral(f3, x1, x3, eps2));
		part_2 = fabs(integral(f2, x3, x2, eps2) - integral(f3, x3, x2, eps2));
	}
	if ( (x2 <= x1) && (x1 <= x3) ) {
		part_1 = fabs(integral(f2, x2, x1, eps2) - integral(f3, x2, x1, eps2));
		part_2 = fabs(integral(f1, x1, x3, eps2) - integral(f3, x1, x3, eps2));
	}
	if ( (x2 <= x3) && (x3 <= x1) ) {
		part_1 = fabs(integral(f2, x2, x3, eps2) - integral(f3, x2, x3, eps2));
		part_2 = fabs(integral(f1, x3, x1, eps2) - integral(f2, x3, x1, eps2));
	}
	if ( (x3 <= x1) && (x1 <= x2) ) {
		part_1 = fabs(integral(f1, x3, x1, eps2) - integral(f2, x3, x1, eps2));
		part_2 = fabs(integral(f2, x1, x2, eps2) - integral(f3, x1, x2, eps2));
	}
	if ( (x3 <= x2) && (x2 <= x1) ) {
		part_1 = fabs(integral(f1, x3, x2, eps2) - integral(f2, x3, x2, eps2));
		part_2 = fabs(integral(f2, x2, x1, eps2) - integral(f3, x2, x1, eps2));
	}
	
	float area = part_1 + part_2;
	
	printf("the area of the figure is %f\n" , area);
	
	return 0;
}
