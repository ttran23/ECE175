#include <stdio.h>
#include <math.h>

int main(void) {

	//variables for user input
	float distance = 0.0, acceleration = 0.0;

	printf("Enter the distance that the object will travel(meters): ");		//get distance
	scanf("%f", &distance);
	printf("Enter the constant acceleration caused by the gravitation field(meters/s^2): ");		//get acceleration
	scanf("%f", &acceleration);

	//printing with calculations within statement, no need for extra variable time or velocity
	printf("The object will travel %.2f meters in %.2f seconds.\n", distance, sqrt(2 * distance / acceleration));
	printf("After falling for %.2f seconds the object will be traveling %.2f meters/second\n", sqrt(2 * distance / acceleration), acceleration * sqrt(2 * distance / acceleration));
	return 0;
}