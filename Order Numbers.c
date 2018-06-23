#include <stdio.h>
#include <math.h>

void order_three(double *small, double *middle, double *large);
void order(double *smaller, double *larger);

int main(void) {

	double x1 = 0.0, x2 = 0.0, x3 = 0.0;
	char userCont = '?';

	do {
		printf("Enter three numbers separated by spaces: ");	//get 3 numbers
		scanf("%lf %lf %lf", &x1, &x2, &x3);

		order_three(&x1, &x2, &x3);	//call function
		printf("The numbers in ascending order are: %.2lf %.2lf %.2lf\n", x1, x2, x3);

		printf("Try again (y/n): ");
		scanf("%*c%c", &userCont);
	} while (userCont == 'y' || userCont == 'Y'); //for convenience of testing, not required
}

void order_three(double *small, double *middle, double *large) {
	
	//3 numbers, 3 orders or swapping
	order(small, middle);
	order(small, large);
	order(middle, large);
}

void order(double *smaller, double *larger) {
	double temp = 0;

	//basic swap
	if (*smaller > *larger) {
		temp = *smaller;
		*smaller = *larger;
		*larger = temp;
	}
}