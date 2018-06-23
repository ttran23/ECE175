#include <stdio.h>


typedef struct seq_s {
	int val;
	struct seq_s *nextp;
} seq;

void deleteList(seq *head);
void printList(seq *head);
void initializeHead(seq **head, seq **tail, int nStart);
void nextCollatz(seq **tail);
int listLength(seq *head);

int main(void) {
	
	int curLength = 0;						// - current seq length
	int maxLength = 0;						// - maximum sequence length
	int maxN = 1;							// - staring point (n) of the longest sequence
	seq *head = NULL, *temp, *tail = NULL;	// - pointers to the head and tail of a linked list
	
	// loop over the possible starting points
	for (int n = 3; n < 1000; n++) {
		// reset the head and tail to null
		head = NULL;
		tail = NULL;
		// initialize the head with the starting point n
		initializeHead(&head, &tail, n);
		temp = head;
		// loop until the last element in the list is 1
		while (temp->val > 1) {
			nextCollatz(&temp);
			temp = temp->nextp;
		}
		tail = temp;
		// find the length of the list
		curLength = listLength(head);
		// is it a maximum?
		if (curLength > maxLength) {
			maxLength = curLength;
			maxN = n;
		}
		// delete the list
		deleteList(head);
	}
	// generate the longest sequence and print it to the terminal

	head = NULL;
	tail = NULL;
	initializeHead(&head, &tail, maxN);
	temp = head;

	while (temp->val > 1) {
		nextCollatz(&temp);
		temp = temp->nextp;
	}
	tail = temp;
	printList(head);
	printf("\n\nThe longest sequence is %d, which occurs when n = %d\n", maxLength, maxN);
	return 0;
}

//delete a list starting with the head
void deleteList(seq *head) {
	seq *temp = head;
	if (head == NULL) {
		return;
	}
	else {
		while (temp->nextp != NULL) {
			temp = temp->nextp;
			free(head);
			head = temp;
		}
		free(temp);
	}
}
//print a list
void printList(seq *head) {

	int count = 1;			//just to print 7 max per line
	while (head != NULL) {
		printf("%d\t", head->val);
		head = head->nextp;
		if (count > 9) {
			count = 0;
			printf("\n");
		}
		count++;
	}
}
//initialize the head such that head->val = nStart
void initializeHead(seq **head, seq **tail, int nStart) {
	if (*head == NULL) {
		*head = (seq*)malloc(sizeof(seq));
		(*head)->val = nStart;
		(*head)->nextp = NULL;
	}
	if (*tail == NULL) {
		*tail = (seq*)malloc(sizeof(seq));
		(*tail)->val = nStart;
		(*tail)->nextp = NULL;
	}
}
//find next integer in the sequence given the tail of the list
void nextCollatz(seq **tail) {
	seq *temp;
	temp = (seq*)malloc(sizeof(seq));
	temp->val = 0;
	temp->nextp = NULL;

	if ((*tail)->val % 2 == 0) {
		temp->val = (*tail)->val / 2;
	}
	else {
		temp->val = (*tail)->val * 3 + 1;
	}

	(*tail)->nextp = temp;
}
//return the length of the sequence
int listLength(seq *head) {
	
	int count = 0;			//var to keep count
	
	while (head != NULL) {	//while list is not empty
		count++;			//count
		head = head->nextp;	//cycle through list
	}

	return count;			//return count
}
