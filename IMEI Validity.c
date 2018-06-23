#include <stdio.h>
#include <math.h>


int main(void) {

	int IMEI[15];
	int i, sum = 0, temp = 0, checkDigit = 0;

	printf("Enter 15-digit barcode (separated by spaces):\n");
	for (i = 0; i < 15; i++) {
		scanf("%d", &IMEI[i]);
	}

	//summing algorithm
	for (i = 0; i < 14; i++) {
		if (i % 2 == 0) {
			sum += IMEI[i];
		}
		else {
			temp = 2 * IMEI[i];
			while (temp > 9) {
				temp = (temp / 10) + (temp % 10);
			}
			sum += temp;
		}
	}
	//check digit is last digit of sum, subtracted from 10
	checkDigit = 10 - (sum % 10);
	
	printf("Total sum of 14 digits = %d\n", sum);
	printf("Check digit = %d\n", checkDigit);
	//if check digit matches last IMEI digit
	if (checkDigit == IMEI[14]) {
		printf("IMEI is VALID.\n");
	}
	else {
		printf("IMEI is INVALID.\n");
	}
	return 0;
}