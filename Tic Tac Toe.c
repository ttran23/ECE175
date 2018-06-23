#include <stdio.h>

int valid_move(int i, int j, int p1[3][3], int p2[3][3]);
int check_win(int matrix[3][3]);
void print_board(int p1[3][3], int p2[3][3]);

int main(void) {

	int player1[3][3], player2[3][3];	//variable for two players
	int x=0, y=0;						//variable for user input
	int i, j;							//variable for loops
	int round = 1;						//checks if game ends
	
	//initializing both boards to "empty"
	for (i = 0; i < 3; i++) {
		for (j = 0; j < 3; j++) {
			player1[i][j] = 0;
			player2[i][j] = 0;
		}
	}

	while (round <= 9) {		//while there are still available turns
		
		//If round is odd, (i.e. 1,3,5,7,9), player 1 goes
		if (round % 2 == 1) {
			do {		//asks user input, checks if valid move
				printf("Player 1 - Enter your next move: ");
				scanf("%d %d", &x, &y);
			} while (valid_move(x, y, player1, player2) == 0);
			
			player1[x][y] = 1;					//assigns valid move
			print_board(player1, player2);		//prints board
		}
		//if round is even (i.e. round 2,4,6,8) player 2 goes
		else {
			do {		//asks user input, checks if valid move
				printf("Player 2 - Enter your next move: ");
				scanf("%d %d", &x, &y);
			} while (valid_move(x, y, player1, player2) == 0);
			
			player2[x][y] = 1;					//assigns valid move
			print_board(player1, player2);		//prints board
		}

		//checking win conditions
		if (check_win(player1) == 3) {
			printf("Player 1 is the winner.\n");
			break;		//game ends, no need to keep going through rounds
		}
		else if (check_win(player2) == 3) {
			printf("Player 2 is the winner.\n");
			break;
		}

		round++;   //one full round ends, move to round 2

	}

	//after all 9 turns and there are no winners
	if (round > 9) {
		printf("No possible moves remaining, tie game.\n");
	}
	return 0;
}

//checks player validity
int valid_move(int i, int j, int p1[3][3], int p2[3][3]) {
	
	if ((i > 2 || j < 0) || (j > 2 || j < 0)) {
		return 0;		//checks to make sure user input is within array range
	}
	else if (p1[i][j] == 0 && p2[i][j] == 0) {
		return 1;		//if both arrays are empty, valid move
	}
	else {
		return 0;		//if either array has value, invalid move
	}
}

int check_win(int matrix[3][3]) {
	int i; //variable for loop
	
	//check diagonal
	if ((matrix[0][0] + matrix[1][1] + matrix[2][2] == 3) 
		|| (matrix[0][2] + matrix[1][1] + matrix[2][0] == 3)) {
		return 3;
	}

	for (i = 0; i < 3; i++) {
		//check rows
		if ((matrix[i][0] + matrix[i][1] + matrix[i][2] == 3)) {
			return 3;
		}
		//check columns
		if ((matrix[0][i] + matrix[1][i] + matrix[2][i] == 3)) {
			return 3;
		}
	}

	return 0;
}

void print_board(int p1[3][3], int p2[3][3]) {
	int i, j;  //variable for loop

	for (i = 0; i < 3; i++) {
		for (j = 0; j < 3; j++) {
			//prints X/O depending on if there exists values
			if (p1[i][j] == 1) {
				printf("X");
			}
			else if (p2[i][j] == 1) {
				printf("O");
			}
			else {
				printf("-");
			}

			printf(" ");		//prints spaces between
		}
		printf("\n");	//next line
	}
}
