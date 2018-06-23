#include <stdio.h>
#include <math.h>

void print_complex(float z_r, float z_i);
void add_complex(float z1_r, float z1_i, float z2_r, float z2_i, float *z3_r, float *z3_i);
void mul_complex(float z1_r, float z1_i, float z2_r, float z2_i, float *z3_r, float *z3_i);
void div_complex(float z1_r, float z1_i, float z2_r, float z2_i, float *z3_r, float *z3_i);

int main(void) {
	float z1r = 0.0, z1i = 0.0, z2r = 0.0, z2i = 0.0, z3r = 0.0, z3i = 0.0;
	char operation = '?', userCont = '?';

	printf("Complex number calculator\n");
	do {
		printf("Enter first number (real and imaginary): ");
		scanf("%f %f", &z1r, &z1i);
		printf("Enter second number (real and imaginary): ");
		scanf("%f %f", &z2r, &z2i);
		printf("\nA for (+)\tS for (-)\tM for (*)\tD for (/)\n");
		printf("Your choice is: ");
		scanf("%*c%c", &operation);

		switch (operation) {
		case 'A':
		case 'a':
			print_complex(z1r, z1i);
			printf("+");
			print_complex(z2r, z2i);
			printf("=");
			add_complex(z1r, z1i, z2r, z2i, &z3r, &z3i);
			print_complex(z3r, z3i);
			break;
		case 'S':
		case 's':
			print_complex(z1r, z1i);
			printf("-");
			print_complex(z2r, z2i);
			printf("=");
			add_complex(z1r, z1i, -z2r, -z2i, &z3r, &z3i);
			print_complex(z3r, z3i);
			break;
		case 'M':
		case 'm':
			print_complex(z1r, z1i);
			printf("*");
			print_complex(z2r, z2i);
			printf("=");
			mul_complex(z1r, z1i, z2r, z2i, &z3r, &z3i);
			print_complex(z3r, z3i);
			break;
		case 'D':
		case 'd':
			if (z2r == 0 && z2i == 0) {
				printf("Denominator must be non-zero!\n");
			}
			else {
				print_complex(z1r, z1i);
				printf("/");
				print_complex(z2r, z2i);
				printf("=");
				div_complex(z1r, z1i, z2r, z2i, &z3r, &z3i);
				print_complex(z3r, z3i);
			}
			break;
		default:
			printf("Your choice is invalid.\n");
			break;
		}

		printf("\nTry again (y/n): ");
		scanf("%*c%c", &userCont);
		printf("\n\n");
	} while (userCont == 'y' || userCont == 'Y');
}

void print_complex(float z_r, float z_i) {
	if (z_r == 0 && z_i == 0) {	//prints (0.00) if both are zero
		printf("(0.00)");
	}
	else if (z_i == 0) {		//prints (3.00) if real exists but imaginary is zero
		printf("(%.2lf)", z_r);
	}
	else if (z_r == 0) {		//prints (3.00i) if real is zero but imaginary exists
		printf("(%.2lfi)", z_i);
	} 
	else {
		if (z_i < 0) {			//if imaginary is negative, print as is
			printf("(%.2lf%.2lfi)", z_r, z_i);
		}
		else {					//else add a + sign
			printf("(%.2lf+%.2lfi)", z_r, z_i);
		}
	}
}

/*
Complex Calculations are from the following website:
http://mathworld.wolfram.com/ComplexNumber.html
*/
void add_complex(float z1_r, float z1_i, float z2_r, float z2_i, float *z3_r, float *z3_i) {
	*z3_r = z1_r + z2_r;
	*z3_i = z1_i + z2_i;
}

void mul_complex(float z1_r, float z1_i, float z2_r, float z2_i, float *z3_r, float *z3_i) {
	*z3_r = z1_r*z2_r - z1_i*z2_i;
	*z3_i = z1_r*z2_i + z1_i*z2_r;
}

void div_complex(float z1_r, float z1_i, float z2_r, float z2_i, float *z3_r, float *z3_i) {
	float denom = z2_r*z2_r + z2_i*z2_i;
	*z3_r = (z1_r*z2_r + z1_i*z2_i) / denom;
	*z3_i = (z1_i*z2_r - z1_r*z2_i) / denom;
}