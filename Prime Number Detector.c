#include <stdio.h>
#include <math.h>


int even(int num);
int findDiv(int n);

int main(void) {

	int userNum = 0;
	int temp = 0;
	char userCont = '?';
	
	do {
		printf("Enter a number that you think is a prime number between 2 and 1000: ");
		scanf("%d", &userNum);

		while (userNum < 2 || userNum > 1000) {
			if (userNum < 2) {
				printf("Error, number too small. The smallest prime is 2.\n");
			}
			if (userNum > 1000) {
				printf("Error, largest number accepted is 1000.\n");
			}
			printf("Please re-enter number: ");
			scanf("%d", &userNum);
		}

		//calling function
		temp = findDiv(userNum);

		//if returned val same as user num, report it is prime
		if (temp == userNum) {
			printf("Number is prime!\n");
		}
		//if returned val is even, print even
		else if (temp == 2) {
			printf("2 is the smallest divisor of %d. Number not prime.\n\n", userNum);
		}
		//if returned val is not user num, print smallest divisor found
		else {
			printf("%d is the smallest divisor of %d. Number not prime.\n", temp, userNum);
		}

		printf("Try again (y/n): ");
		scanf("%*c%c", &userCont);
	} while (userCont == 'y' || userCont == 'Y'); //convenience for testing, not required
	return 0;
}

int even(int num) {
	if (num % 2 == 0) {
		return 1;		//if even, return 1
	}
	else {
		return 0;		//if odd, return 0
	}
}

int findDiv(int n) {

	if (even(n) && n != 2) {
		return 2;
	}
	else {
		for (int i = 3; i < n; i += 2) {
			if (n%i == 0) {
				return i;
			}
		}
		return n;
	}
}