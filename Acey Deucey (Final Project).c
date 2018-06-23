#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <time.h>

/*
GAME DESCRIPTION:
Acey Deucey

Set-up:
	+ Minimum of 4 players, no max limit
	+ Players enter amount of starting money
		++ Must be at least $6
	+ Deck of 52 cards is created and shuffled
		++ When out of cards, create new deck?

Gameplay:
	+ Each player will add $5 to the pot to begin
	+ Two cards are dealt to a player from the deck
	+ Based on rules, they either add $1 to pot, add $0 (skip), or bet
		+ FIRST ROUND: only max of $1 bet
		+ SECOND ROUND FORWARD: no limit
	+ Game ends when pot is $0 or all players run out of money.

Game Rules:
	+ If both cards are equal, player must add $1 to pot and move to next player
	+ If not (2 and 5), player can "bet" the amount and then a third is drawn
		++ If third card is between 2 and 5, player wins the amount bet from the pot
		++ If third card is outside of range, player loses bet and adds it to the pot
		++ If third card is ON the edge, player loses DOUBLE the bet and adds to pot

*/

typedef struct card_s {
	char suit;		//clubs, spades, hearts, diamonds
	int face;		//1: Ace, 2-10, 11: Jack, 12: Queen, 13: King
	struct card_s *nextp;
} card;

typedef struct player_s {
	char name[100];
	float bank;
	struct player_s *listp;
} player;

player *Create_Player(int numPlayers);
void Print_Players(player *head);
card *Create_Deck(void);
void Print_Deck(card *head);
void Shuffle_Deck(card *head);
void Print_Card(char suit, int face);
void Write_ToFile(player *head);

int main(void) {
	// Setting time variable for randomizer
	srand((int)time(0));

	// Variables for player
	player *playersHead = NULL, *playerTemp = NULL;
	card playerCard1, playerCard2, playerCard3;
	float playerBet = 0.0;
	int numPlayers = 0;

	// Variables for deck
	card *deckHead = NULL;
	card *temp = NULL; 

	// Variables for loops
	int i = 0;
	float moneyPot = 0;	// Basically keep going till pot is $0, so it's a loop counter.
	int round = 1;		// Keeps track of rounds
	
	// Setting up the game
	printf("\n+=+=+=+=+=+=+=+=+=+=+=+");
	printf("\nWelcome to Acey Deucey");
	printf("\n By: Your");
	printf("\n     God");
	printf("\n+=+=+=+=+=+=+=+=+=+=+=+");

	// Get amount of players in game, minimum of 4.
	while (numPlayers < 4) {
		printf("\n\nEnter the amount of players: ");
		scanf("%d", &numPlayers);
	}

	// Create instances/list of players with a function
	// Assign playersHead pointer to point to head of that list.
	playersHead = Create_Player(numPlayers);

	// Printing out players, just to make sure list was created correctly
	Print_Players(playersHead);

	// Just to avoid a cluttered console output, not necessary
	printf("\nPress ENTER to view deck list\n");
	getc(stdin);
	getc(stdin);
	system("cls");

	// Create new deck of 52 cards
	printf("\nCreating deck\n.\n.\n.\n.\n");
	deckHead = Create_Deck();

	// Print deck before shuffling
	printf("\nUnshuffled deck:\n");
	Print_Deck(deckHead);

	// Shuffle deck
	printf("\nShuffling deck\n.\n.\n.\n.\n");
	Shuffle_Deck(deckHead);

	// Print deck after shuffling
	printf("\nShuffled deck:\n");
	Print_Deck(deckHead);

	// Just to avoid a cluttered console output, not necessary
	printf("\nPress ENTER to proceed to game\n");
	getc(stdin);
	getc(stdin);
	system("cls");

	// Taking initial pot value
	printf("\nTaking player pot to begin game\n");
	playerTemp = playersHead;
	while (playerTemp != NULL) {
		printf("%s has a bank of $%.2f\n", playerTemp->name, playerTemp->bank);
		printf("Deducting $5 from %s and adding to the pot\n", playerTemp->name);
		playerTemp->bank -= 5;
		moneyPot += 5;
		printf("%s now has $%.2f left in the bank\n\n", playerTemp->name, playerTemp->bank);
		printf("Current money pot is: $%.2f\n", moneyPot);
		playerTemp = playerTemp->listp;
	}

	printf("\nPress ENTER to proceed to game\n");
	getc(stdin);
	getc(stdin);
	system("cls");

	while (moneyPot > 0) {
		// Resetting temp pointer back to top of list
		playerTemp = playersHead;
		printf("Round %d\n", round);
		while (playerTemp != NULL) {
			printf("Current money pot is: $%.2f\n\n", moneyPot);
			if (playerTemp->bank == 0) {
				printf("%s has ran out of money. Skipping turn.", playerTemp->name);
			}
			else {
				printf("\n%s has a bank of $%.2f\n", playerTemp->name, playerTemp->bank);
				printf("\nDealing card to %s\n", playerTemp->name);
				// Card 1
				playerCard1.suit = deckHead->suit;
				playerCard1.face = deckHead->face;
				temp = deckHead;
				deckHead = deckHead->nextp;
				free(temp);
				// Card 2
				playerCard2.suit = deckHead->suit;
				playerCard2.face = deckHead->face;
				temp = deckHead;
				deckHead = deckHead->nextp;
				free(temp);
				// Print cards
				Print_Card(playerCard1.suit, playerCard1.face);
				Print_Card(playerCard2.suit, playerCard2.face);
				// Check game
				if (playerCard1.face == playerCard2.face) {
					printf("Identical cards. Lose.\n");
					printf("Taking $1 from player and adding to money pot.\n");
					playerTemp->bank -= 1;
					moneyPot += 1;
					printf("Money pot is now: $%.2f\n", moneyPot);
				}
				else {
					printf("Cards are not identical. Place your bet (0 to discard): ");
					scanf("%f", &playerBet);
					while (playerBet > playerTemp->bank || playerBet < 0) {
						printf("Please enter a valid bet. %s's bank is $%.2f\n", playerTemp->name, playerTemp->bank);
						scanf("%f", &playerBet);
					}
					// Card 3
					if (playerBet == 0) {
						printf("Discarding card. Moving to next player.\n");
					}
					else {
						printf("Drawing third card: ");
						playerCard3.suit = deckHead->suit;
						playerCard3.face = deckHead->face;
						temp = deckHead;
						deckHead = deckHead->nextp;
						free(temp);
						Print_Card(playerCard3.suit, playerCard3.face);

						// Normally this is in its own CheckWin function but I got lazy
						if (playerCard3.face == playerCard1.face || playerCard3.face == playerCard2.face) {
							printf("Card drawn is an EDGE CASE!\n");
							printf("You lose DOUBLE the bet.\n");
							
							if (playerBet * 2 > playerTemp->bank) {
								playerBet = playerTemp->bank;
								playerTemp->bank = 0;
								printf("Lost all money.\n");
							}
							else {
								playerBet *= 2;
								playerTemp->bank -= playerBet;
								printf("%s now has a bank of $%.2f\n", playerTemp->name, playerTemp->bank);
							}
							printf("Taking $%.2f from player and adding to money pot.\n", playerBet);
							moneyPot += playerBet;
						}
						else if (playerCard3.face < playerCard1.face && playerCard3.face > playerCard2.face) {
							printf("Card drawn is OUTSIDE OF RANGE!\n");
							printf("You lose the bet.\n");

							if (playerBet > playerTemp->bank) {
								playerBet = playerTemp->bank;
								playerTemp->bank = 0;
								printf("Lost all money.\n");
							}
							else {
								playerTemp->bank -= playerBet;
								printf("%s now has a bank of $%.2f\n", playerTemp->name, playerTemp->bank);
							}
							printf("Taking $%.2f from player and adding to money pot.\n", playerBet);
							moneyPot += playerBet;
						}
						else {
							printf("Card drawn is WITHIN THE RANGE!\n");
							printf("You win the bet.\n");
							
							if (playerBet > moneyPot) {
								playerBet = moneyPot;
								moneyPot = 0;
								playerTemp->bank += playerBet;
								printf("Taking $%.2f from the money pot and adding to player.\n", playerBet);
								printf("%s now has a bank of $%.2f\n", playerTemp->name, playerTemp->bank);
								printf("Pot is all out of money.\n");
							}
							else {
								playerTemp->bank += playerBet;
								printf("Taking $%.2f from the money pot and adding to player.\n", playerBet);
								printf("%s now has a bank of $%.2f\n", playerTemp->name, playerTemp->bank);
							}
							moneyPot -= playerBet;
						}
					}
				}
			}
			if (moneyPot <= 0) {
				break;
			}
			playerTemp = playerTemp->listp;
			printf("\n\n");
		}
		round++;
		printf("\nPress ENTER to proceed to NEXT ROUND\n");
		getc(stdin);
		getc(stdin);
		system("cls");
	}
	printf("\n\nGAME OVER\n\n");
	printf("Pot is all out of money!\n");
	printf("The final statistics are:\n");
	Print_Players(playersHead);
	printf("\nWrite these statistics to a file? (Y/N)  ");
	char tempLUL = ' ';
	scanf("%*c%c", &tempLUL);
	if (tempLUL == 'y' || tempLUL == 'Y') {
		Write_ToFile(playersHead);
		printf("\nDone writing to file.\n");
		printf("\nPress ENTER to proceed to NEXT ROUND\n");
		getc(stdin);
		getc(stdin);
		system("cls");
	}

	return 0;
}

player *Create_Player(int numPlayers) {
	// Temp pointers to allocate and move along the list
	player *head = NULL, *temp, *tail = NULL;
	int i;

	for (i = 0; i < numPlayers; i++) {
		// Create/Allocate memory
		temp = (player*)malloc(sizeof(player));		

		// Populating the data for the new memory created
		// Get user name
		printf("\nEnter player %d's name (First Name Only): ", i+1);	// i+1 because iterator starts at 0
		scanf("%s", &temp->name);

		// In case they enter more than 1 name
		fflush(stdin);

		// Get user money, making sure at least enough to start game
		do {
			printf("Enter bank amount (Minimum $6 to play): ");
			scanf("%f", &temp->bank);
		}  while (temp->bank < 6);

		// Link to NULL so there isn't an issue with pointer pointing to random memory
		temp->listp = NULL;

		// Standard linking a list together
		if (head == NULL) {
			head = temp;
		}
		else {
			tail->listp = temp;
		}
		tail = temp;
	}

	return head;
}

void Print_Players(player *head) {
	player *temp = head;
	int i = 1;
	while (temp != NULL) {
		printf("\nPlayer %d: %s\n", i++, temp->name);
		printf("%s's bank: $%.2f\n", temp->name, temp->bank);
		temp = temp->listp;
	}
	printf("\n");
}

card *Create_Deck(void) {
	card *head = NULL, *temp, *tail = NULL;
	int i;

	for (i = 0; i < 52; i++) {
		temp = (card*)malloc(sizeof(card));

		// Assigns 1-13.
		temp->face = (i % 13) + 1; 

		// Changing console font to "Rastor Font" for symbols
		if (i < 13) {			//Clubs is 5
			temp->suit = 5;
		}
		else if (i < 26) {		//Spades is 6
			temp->suit = 6;
		}
		else if (i < 39) {		//Heart is 3
			temp->suit = 3;
		}
		else {					//Diamonds is 4
			temp->suit = 4;
		}
		temp->nextp = NULL;

		// Standard list linking
		if (head == NULL) {
			head = temp;
		}
		else {
			tail->nextp = temp;
		}
		tail = temp;
	}
	return head;
}

void Print_Deck(card *head) {
	card *temp = head;
	int spacing = 0;

	while (temp != NULL) {
		// Only purpose is to not have on long line of cards
		if (spacing > 12) {
			spacing = 0;
			printf("\n");
		}
		//cases for J/Q/K/A
		if (temp->face == 11) {
			printf("J%c ", temp->suit);
		}
		else if (temp->face == 12) {
			printf("Q%c ", temp->suit);
		}
		else if (temp->face == 13){
			printf("K%c ", temp->suit);
		}
		else if (temp->face == 1) {
			printf("A%c ", temp->suit);
		}
		else {
			printf("%d%c ", temp->face, temp->suit);
		}
		temp = temp->nextp;			//go to next card

		spacing++;
	}
	printf("\n");
}

void Shuffle_Deck(card *head) {
	card temp, *card1, *card2;
	int rand1 = 0, rand2 = 0, i, j;

	// Shuffle 500 times
	for (i = 0; i < 500; i++) {
		card1 = head;
		card2 = head;
		rand1 = rand() % 52;
		rand2 = rand() % 52;

		// Getting to the random card in the deck
		for (j = 0; j < rand1; j++) {
			card1 = card1->nextp;
		}
		for (j = 0; j < rand2; j++) {
			card2 = card2->nextp;
		}

		// Swapping values of cards
		temp.suit = card1->suit;
		temp.face = card1->face;
		card1->suit = card2->suit;
		card1->face = card2->face;
		card2->suit = temp.suit;
		card2->face = temp.face;
	}
}

void Print_Card(char suit, int face) {
	printf("\n,----,\n");
	if (face == 1) {
		printf("| A  |");
	}
	else if (face == 10) {
		printf("| 10 |");
	}
	else if (face == 11) {
		printf("| J  |");
	}
	else if (face == 12) {
		printf("| Q  |");
	}
	else if (face == 13) {
		printf("| K  |");
	}
	else {
		printf("| %d  |", face);
	}

	printf("\n|  %c |", suit);
	printf("\n'----'\n");
	

}

void Write_ToFile(player *head) {
	FILE *outp = NULL;
	player *temp = head;

	outp = fopen("AceyDeuceyResults.txt", "w");
	if (outp == NULL) {
		printf("Unable to locate/create file.\n");
		return -1;
	}

	while (temp != NULL) {
		fprintf(outp, "%s\t$%.2f\n", temp->name, temp->bank);
		temp = temp->listp;
	}

	fclose(outp);
}