#include <stdio.h>
#include <math.h>

int main(void) {

	//variable for info from user
	int rmLength = 0, rmWidth = 0, tLength = 0;
	float tPrice = 0.0, salesTax = 0.0;	
	//variables for info calculated internally
	int totArea = 0, totTiles = 0;
	float costPreTax = 0.0, costPostTax = 0.0;

	printf("Enter room length (inches): ");		//get length
	scanf("%d", &rmLength);
	printf("Enter room width (inches): ");		//get width
	scanf("%d", &rmWidth);
	printf("Enter tile length (inches): ");		//get tile length
	scanf("%d", &tLength);
	printf("Enter cost per tile (dollars): ");	//get price
	scanf("%f", &tPrice);
	printf("Enter sales tax (percent): ");		//get sales tax
	scanf("%f", &salesTax);

	//calculations
	totArea = rmLength * rmWidth;
	totTiles = ceil((float)rmLength / tLength)*ceil((float)rmWidth / tLength);
	costPreTax = totTiles * tPrice;
	costPostTax = totTiles*tPrice*(1.0 + salesTax / 100.0);

	printf("\n\n");		//print results
	printf("The total area to be tiled is %d square inches\n", totArea);
	printf("The total number of tiles to be purchased is %d\n", totTiles);
	printf("The cost of the purchase before tax is $%.2f\n", costPreTax);
	printf("The cost of the purchase including tax is $%.2f\n", costPostTax);
	return 0;
}