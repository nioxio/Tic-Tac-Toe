#include <stdio.h>
#include <windows.h>
#pragma warning(disable:4996)

int currentPlayer;
int placed;
int player1Wins;
int player2Wins;

char slot[10];

int main() {
	srand(time(0));
	// ASCII art
	printf("\033[33m __     __     ______     __         ______     ______     __    __     ______      \033[36m  ______   ______\n");
	printf("\033[33m/\\ \\  _ \\ \\   /\\  ___\\   /\\ \\       /\\  ___\\   /\\  __ \\   /\\ \"-./  \\   /\\  ___\\      \033[36m/\\__  _\\ /\\  __ \\\n");
	printf("\033[33m\\ \\ \\/ \".\\ \\  \\ \\  __\\   \\ \\ \\____  \\ \\ \\____  \\ \\ \\/\\ \\  \\ \\ \\-./\\ \\  \\ \\  __\\    \033[36m  \\/_/\\ \\/ \\ \\ \\/\\ \\\n");
	printf("\033[33m \\ \\__/\".~\\_\\  \\ \\_____\\  \\ \\_____\\  \\ \\_____\\  \\ \\_____\\  \\ \\_\\ \\ \\_\\  \\ \\_____\\    \033[36m   \\ \\_\\  \\ \\_____\\\n");
	printf("\033[33m  \\/_/   \\/_/   \\/_____/   \\/_____/   \\/_____/   \\/_____/   \\/_/  \\/_/   \\/_____/     \033[36m   \\/_/   \\/_____/\n\n");
	printf("\033[31m ______   __     ______  \033[32m      ______   ______     ______   \033[37m     ______   ______     ______\n");
	printf("\033[31m/\\__  _\\ /\\ \\   /\\  ___\\   \033[32m   /\\__  _\\ /\\  __ \\   /\\  ___\\     \033[37m /\\__  _\\ /\\  __ \\   /\\  ___\\\n");
	printf("\033[31m\\/_/\\ \\/ \\ \\ \\  \\ \\ \\____   \033[32m  \\/_/\\ \\/ \\ \\  __ \\  \\ \\ \\____     \033[37m\\/_/\\ \\/ \\ \\ \\/\\ \\  \\ \\  __\\\n");
	printf("\033[31m   \\ \\_\\  \\ \\_\\  \\ \\_____\\   \033[32m    \\ \\_\\  \\ \\_\\ \\_\\  \\ \\_____\\    \033[37m   \\ \\_\\  \\ \\_____\\  \\ \\_____\\\n");
	printf("\033[31m    \\/_/   \\/_/   \\/_____/    \033[32m    \\/_/   \\/_/\\/_/   \\/_____/     \033[37m   \\/_/   \\/_____/   \\/_____/\n\n");
	// Set values for first run
	slot[1] = slot[2] = slot[3] = slot[4] = slot[5] = slot[6] = slot[7] = slot[8] = slot[9] = '-';
	do {
		// Start game loop
		if (game() == 1) {
			// If player 1 Wins print that and add to their score.
			system("cls");
			player1Wins++;
			printf("\033[36mPlayer 1 Wins!");
		}
		else {
			// If player 2 Wins print that and add to their score.
			system("cls");
			player2Wins++;
			printf("\033[36mPlayer 2 Wins!");
		}
		// Reset values for next run, if there will be any
		slot[1] = slot[2] = slot[3] = slot[4] = slot[5] = slot[6] = slot[7] = slot[8] = slot[9] = '-';
		placed = 0;
		// Print the scoreboard and ask if the players want to continue.
		printf("\n\033[33mCurrent Score:\n Player 1: %d\n Player 2: %d\n\nPress Q to exit or any key to continue.\n\033[30m", player1Wins, player2Wins);
		// End loop only if the players press Q
	} while (tolower(getch()) != 'q');
}

int game() {
	// Randomize which player starts
	currentPlayer = (rand() % 2)+1;
	// Display the playing board
	displayGrid(1);
	// Start infinite game loop
	while (1) {
		// See if both players have placed all their things
		if (placed >= 6) {
			// Remove one of the players things
			slot[takeInput(0)] = '-';
			// Update playing board
			displayGrid(0);
		}
		// See which players turn it is, then let that player place their thing accordingly
		if (currentPlayer == 1)
			slot[takeInput(1)] = 'x';
		else
			slot[takeInput(1)] = 'o';
		placed++;
		// Update playing board
		displayGrid(0);
		// See if the player won or not
		if (winCheck() == currentPlayer) {
			// If the player is returned, return that again as the winner
			return currentPlayer;
		}
		// Change which players turn it is
		if (currentPlayer != 1)
			currentPlayer = 1;
		else
			currentPlayer = 2;
		displayGrid(0);
	}
}

int takeInput(int i) {
	// Set the value of c to that of the current players things
	char c = 'o';
	if (currentPlayer == 1)
		c = 'x';
	// If the function was called with the number 0, make sure that the slot the player choses has their own thing on it
	if (i == 0) {
		// Take input
		char input = getch();
		// See if input as an int is between 48 and 58 (which includes the numbers 1-9 as chars)
		if ((int)input > 48 && (int)input < 58 && slot[((int)input)-48] == c) {
			// Return the input as the correct int
			return ((int)input)-48;
		} else
			takeInput(i);
	}
	// If the function was not called with the number 0, make sure that the slot the player choses is empty
	else {
		// Take input
		char input = getch();
		// See if input as an int is between 48 and 58 (which includes the numbers 1-9 as chars)
		if ((int)input > 48 && (int)input < 58 && slot[((int)input)-48] == '-') {
			// Return the input as the correct int
			return ((int)input)-48;
		} else
			takeInput(i);
	}
}

int displayGrid(int i) {
	// If this function is called with the number 1, don't clear the screen
	if(i != 1)
		system("cls");
	// Show the playing board
	printf("\033[36mPlayer %d's turn\033[37m", currentPlayer);
	printf("\n  7   8   9\n");
	printf("  %c # %c # %c", slot[7], slot[8], slot[9]);
	printf("\n  #########\n");
	printf("4 %c # %c # %c 6", slot[4], slot[5], slot[6]);
	printf("\n  #########\n");
	printf("  %c # %c # %c", slot[1], slot[2], slot[3]);
	printf("\n  1   2   3\n");
	return 0;
}

int winCheck() {
	// Set the value of c to that of the current players things
	char c = 'o';
	if (currentPlayer == 1)
		c = 'x';
	// Check all possible combinations individually, if one of them matches return the current player as the winner
	if ((slot[1] == c && slot[2] == c && slot[3] == c) ||
		(slot[4] == c && slot[5] == c && slot[6] == c) ||
		(slot[7] == c && slot[8] == c && slot[9] == c) ||
		(slot[7] == c && slot[4] == c && slot[1] == c) ||
		(slot[8] == c && slot[5] == c && slot[2] == c) ||
		(slot[9] == c && slot[6] == c && slot[3] == c) ||
		(slot[1] == c && slot[5] == c && slot[9] == c) ||
		(slot[3] == c && slot[5] == c && slot[7] == c))
		return currentPlayer;
	// If nothing matched, return 0
	return 0;
}