#include <stdio.h>
#include <math.h>

int main(void) {

	double val = 0.0; //user val
	int i; //loop variable
	double sum = 0.0, average = 1.0, sumSq = 0.0;

	for (i = 0; i < 8; i++) {
		printf("Enter data value: ");
		scanf("%lf", &val);

		sum = average * i;			//previous sum, average * n
		sum += val;					//add to sum
		average = sum / (i + 1);	//new average
		sumSq += val*val;			//sum squared

		printf("Running average of %d values is %.2lf\n", i + 1, average);
		printf("Accumulated sum of squares of %d values is %.2lf\n\n", i + 1, sumSq);
	}

	printf("Average of %d values is %.2lf\n", i, average);
	printf("Standard Deviation is %.3lf\n", sqrt(sumSq / i - average*average));

	return 0;
}