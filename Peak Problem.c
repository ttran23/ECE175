#include <stdio.h>
#include <math.h>
#define ROW 6
#define COL 7

int main(void) {

	FILE *inp = NULL;
	int i, j;
	int temp;
	int x[ROW][COL];
	int maxPeak = 0, maxRow = 0, maxCol = 0;	//indices for max location

	inp = fopen("PeakProblem.txt", "r");
	if (inp == NULL) {
		printf("File not found.\n");
		return -1;
	}
	else {

		//reading from file of i rows and j columns
		printf("Terrain Data:\n");
		for (i = 0; i < ROW; i++) {
			for (j = 0; j < COL; j++) {
				fscanf(inp, "%d", &x[i][j]);
				printf("%d ", x[i][j]);
			}
			printf("\n");
		}

		printf("\nPeak Data:\n");
		maxPeak = x[0][0];
		for (i = 1; i < ROW - 1; i++) {
			for (j = 1; j < COL - 1; j++) {
				/*
				Top left:	x[i][j] > x[i - 1][j - 1] && 
				Top right:	x[i][j] > x[i + 1][j - 1] && 
				Bot left:	x[i][j] > x[i - 1][j + 1] && 
				Bot right:	&& x[i][j] > x[i + 1][j + 1]
				*/
				if (x[i][j] > x[i][j - 1] && x[i][j] > x[i - 1][j] && x[i][j] > x[i + 1][j] && x[i][j] > x[i][j + 1] ) {
					printf("Peak %d at row %d col %d\n", x[i][j], i, j);

					if (x[i][j] > maxPeak) {
						maxPeak = x[i][j];
						maxRow = i;
						maxCol = j;
					}
				}
			}
		}
		printf("The maximum peak is %d at row %d col %d\n", maxPeak, maxRow, maxCol);
		return 0;
	}
}