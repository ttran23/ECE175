#include <stdio.h>

int primality(int n);

int main(void) {

	FILE *inp = NULL;
	FILE *outp = NULL;
	int tempVal = 0;
	int counter = 0;

	//open file for reading
	inp = fopen("NumberList.txt", "r");
	if (inp == NULL) {						//check to make sure file has been
		printf("File not found.\n");		//opened before proceeding
		return -1;
	}
	else {
		outp = fopen("NumberPrimes.txt", "w");	//open file for writing
		while (!feof(inp)) {					//loop until end of file
			
			fscanf(inp, "%d", &tempVal);		//scan from file
			
			if (primality(tempVal)==1) {		//check primality and print to file
				fprintf(outp, "%d\n", tempVal);
				counter++;						//count how many primes were found
			}
		}

		printf("Total primes printed to file: %d\n", counter);
		fclose(outp);	//close files
		fclose(inp);
		return 0;
	}
}

int primality(int n) {
	
	if (n == 2) {
		return 1;
	}
	else if (n%2 == 0) {
		return 2;
	}
	else {
		for (int i = 3; i < n; i += 2) {
			if (n%i == 0) {
				return i;
			}
		}
		return 1;
	}
}