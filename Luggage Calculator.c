#include <stdio.h>
#include <math.h>


int main(void) {

	FILE *inp = NULL;
	FILE *outp = NULL;
	int id = 0;
	char class = 'Z';
	double weight = 0.0, cost = 0.0;

	inp = fopen("LuggageWeight.txt", "r");
	if (inp == NULL) {
		printf("File not found.\n");
		return -1;
	}
	else {
		outp = fopen("LuggageCost.txt", "w");	//open file for writing
		
		printf("ID\tClass\tBagWeight\tCost\n");
		while (!feof(inp)) {
			fscanf(inp, "%d %c %lf\n", &id, &class, &weight);

			switch (class) {
			case 'E':
			case 'e':
				if (weight < 25.00) {
					cost = 0;
				}
				else if (weight < 40) {
					cost = 1.5*(weight - 25);
				}
				else {
					cost = 2.0*(weight - 40) + 1.5*(15);
				}
				printf("%d\t%c\t%.2lf\t\t$%.2lf\n", id, class, weight, cost);
				fprintf(outp, "%d\t%c\t%.2lf\t\t$%.2lf\n", id, class, weight, cost);
				break;
			case 'B':
			case 'b':
				if (weight < 35.00) {
					cost = 0;
				}
				else if (weight < 50) {
					cost = 1.25*(weight - 35);
				}
				else {
					cost = 1.50*(weight - 50) + 1.25*(15);
				}
				printf("%d\t%c\t%.2lf\t\t$%.2lf\n", id, class, weight, cost);
				fprintf(outp, "%d\t%c\t%.2lf\t\t$%.2lf\n", id, class, weight, cost);
				break;
			case 'V':
			case 'v':
				if (weight < 60) {
					cost = 0;
				}
				else {
					cost = 30;
				}
				printf("%d\t%c\t%.2lf\t\t$%.2lf\n", id, class, weight, cost);
				fprintf(outp, "%d\t%c\t%.2lf\t\t$%.2lf\n", id, class, weight, cost);
				break;
			default:
				printf("%d\t%c\tWrong Class\n", id, class);
				fprintf(outp, "%d\t%c\tWrong Class\n", id, class);
				break;
			}
		}

		fclose(outp);
		fclose(inp);
		printf("\nAlso printed to file HW4zcost.txt\n\n");
		return 0;
	}
}