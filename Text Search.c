#include <stdio.h>
#include <string.h>

#define MAX_SIZE 1000

int main(void) {
	FILE *inp = NULL;
	char userSearch[MAX_SIZE] = "";		//string for user input
	char buffer[MAX_SIZE] = "";			//string from file
	int lineNum = 1;					//start count at 1, since sentences begin with 1.

	inp = fopen("TextList.txt", "r");
	if (inp == NULL) {					//safety net, ends program if no file is found. Avoids bad access
		printf("No file.\n");
		return -1;
	}
	else {
		printf("Enter the target string: ");
		fgets(userSearch, MAX_SIZE, stdin);				//gets user string
		userSearch[strlen(userSearch) - 1] = '\0';		//replaces last char '\n' with '\0'

		while (!feof(inp)) {							//while not end of file , ZyBook 11.5.3
			fgets(buffer, MAX_SIZE, inp);				//get string
			if (strstr(buffer, userSearch) != NULL) {	//compare user string to file string
				printf("%d. %s\n", lineNum, buffer);	//if returned null (i.e. found a match), prints line number and current line
			}
			lineNum++;									//increment line count
		}
		fclose(inp);
		return 0;
	}
}