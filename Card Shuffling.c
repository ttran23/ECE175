#include <stdio.h>
#include <string.h>
#include <time.h>

typedef struct card_s {
	char suit;		//clubs, spades, hearts, diamonds
	int face;		//1: Ace, 2-10, 11: Jack, 12: Queen, 13: King
	struct card_s *nextp;
}card;

card *Create_Deck(void);
void Print_Deck(card *head);
void Shuffle_Deck(card *head);
void Delete_Top_Card(card *head);
void Deal_Card(card **deck, card **player);

int main(void) {
	card *deckhead = NULL;
	card *playerhead = NULL, *playercurr = NULL, *playertemp;
	card *dealerhead = NULL, *dealercurr = NULL, *dealertemp;
	srand((int)time(0));
	int i;

	//create deck
	deckhead = Create_Deck();
	//print deck as is:
	printf("Unshuffled deck:\n");
	Print_Deck(deckhead);
	//shuffle deck
	Shuffle_Deck(deckhead);
	//print shuffled deck
	printf("\nShuffled deck:\n");
	Print_Deck(deckhead);
	
	printf("\n\n+_+_+_Dealing to players_+_+_+\n");
	for (i = 0; i < 16; i++) {

		if (i % 2 == 0) {	//deal to player
			playertemp = (card*)malloc(sizeof(card));
			playertemp->face = deckhead->face;
			playertemp->suit = deckhead->suit;
			if (playerhead == NULL) {
				playerhead = playertemp;
			}
			else {
				playercurr->nextp = playertemp;
			}
			playercurr = playertemp;
			playercurr->nextp = NULL;
		}
		else {				//deal to dealer
			dealertemp = (card*)malloc(sizeof(card));
			dealertemp->face = deckhead->face;
			dealertemp->suit = deckhead->suit;
			if (dealerhead == NULL) {
				dealerhead = dealertemp;
			}
			else {
				dealercurr->nextp = dealertemp;
			}
			dealercurr = dealertemp;
			dealercurr->nextp = NULL;
		}

		//delete top card
		card *decktemp = deckhead;
		deckhead = deckhead->nextp;
		free(decktemp);
	}

	//print player and dealer hand
	printf("\nPlayer hand:\n");
	Print_Deck(playerhead);
	printf("\nDealer hand:\n");
	Print_Deck(dealerhead);

	//print remaining deck
	printf("\nCards left in deck:\n");
	Print_Deck(deckhead);
	return 0;
}



card *Create_Deck(void) {
	card *head = NULL, *temp, *tail = NULL;
	int i;
	
	for (i = 0; i < 52; i++) {
		temp = (card*)malloc(sizeof(card));

		temp->face = (i % 13) + 1; //assigns 1-13.
		
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
		//to not have a huge list of cards
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

	for (i = 0; i < 100; i++) {
		card1 = head;
		card2 = head;
		rand1 = rand() % 52;
		rand2 = rand() % 52;

		for (j = 0; j < rand1; j++) {
			card1 = card1->nextp;
		}
		for (j = 0; j < rand2; j++) {
			card2 = card2->nextp;
		}

		temp.suit = card1->suit;
		temp.face = card1->face;
		card1->suit = card2->suit;
		card1->face = card2->face;
		card2->suit = temp.suit;
		card2->face = temp.face;
	}

}

