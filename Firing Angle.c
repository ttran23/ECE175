#include <stdio.h>
#include <math.h>

int main(void) {

	//variables for user input
	float angle = 0.0, velocity = 0.0;
	char user = '?';

	do {
		printf("Enter firing angle (degrees): ");	//get angle
		scanf("%f", &angle);
		printf("Enter initial velocity (m/s): ");	//get velocity
		scanf("%f", &velocity);

		//conditional statements to meet requirement
		if (angle < 0 || angle > 90) {
			printf("Angle must be between 0 and 90 degrees.\n");
		}
		else if (velocity < 0 || velocity > 100) {
			printf("Velocity must be between 0 and 100 m/s.\n");
		}
		else {
			//calculations
			angle *= 3.14159 / 180.0;
			printf("The horizontal distance the ball travels is :: %.2f m ::\n\n", (2*velocity*velocity)*(cos(angle)*sin(angle))/9.81);
		}

		printf("Try again (y/n): ");
		scanf("%*c%c", &user);
	} while (user == 'y' || user == 'Y'); //for convenience sake of repeating

	return 0;
}