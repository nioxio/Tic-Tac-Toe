#include <stdio.h>
#include <windows.h>
#pragma warning(disable:4996)

int player;
int player1Wins;
int player2Wins;
int draws;
struct row {
	int i1;
	int i2;
	int i3;
	char c1;
	char c2;
	char c3;
}a, b, c, temp;

char test[15];

int main() {
	srand(time(0));
	// ASCII art
	printf("\033[36m __     __     ______     __         ______     ______     __    __     ______        ______   ______\n");
	printf("/\\ \\  _ \\ \\   /\\  ___\\   /\\ \\       /\\  ___\\   /\\  __ \\   /\\ \"-./  \\   /\\  ___\\      /\\__  _\\ /\\  __ \\\n");
	printf("\\ \\ \\/ \".\\ \\  \\ \\  __\\   \\ \\ \\____  \\ \\ \\____  \\ \\ \\/\\ \\  \\ \\ \\-./\\ \\  \\ \\  __\\      \\/_/\\ \\/ \\ \\ \\/\\ \\\n");
	printf(" \\ \\__/\".~\\_\\  \\ \\_____\\  \\ \\_____\\  \\ \\_____\\  \\ \\_____\\  \\ \\_\\ \\ \\_\\  \\ \\_____\\       \\ \\_\\  \\ \\_____\\\n");
	printf("  \\/_/   \\/_/   \\/_____/   \\/_____/   \\/_____/   \\/_____/   \\/_/  \\/_/   \\/_____/        \\/_/   \\/_____/\n\n");
	printf(" ______   __     ______        ______   ______     ______        ______   ______     ______\n");
	printf("/\\__  _\\ /\\ \\   /\\  ___\\      /\\__  _\\ /\\  __ \\   /\\  ___\\      /\\__  _\\ /\\  __ \\   /\\  ___\\\n");
	printf("\\/_/\\ \\/ \\ \\ \\  \\ \\ \\____     \\/_/\\ \\/ \\ \\  __ \\  \\ \\ \\____     \\/_/\\ \\/ \\ \\ \\/\\ \\  \\ \\  __\\\n");
	printf("   \\ \\_\\  \\ \\_\\  \\ \\_____\\       \\ \\_\\  \\ \\_\\ \\_\\  \\ \\_____\\       \\ \\_\\  \\ \\_____\\  \\ \\_____\\\n");
	printf("    \\/_/   \\/_/   \\/_____/        \\/_/   \\/_/\\/_/   \\/_____/        \\/_/   \\/_____/   \\/_____/\n\n");
	// Loop until while statement is met
	do {
		// Reset variables in case this is not the first loop
		player = rand() % 2; // Randomize which player starts
		a.i1 = a.i2 = a.i3 = b.i1 = b.i2 = b.i3 = c.i1 = c.i2 = c.i3 = 0;
		a.c1 = a.c2 = a.c3 = b.c1 = b.c2 = b.c3 = c.c1 = c.c2 = c.c3 = '-';
		// Start game then add score depending on outcome
		int a = game();
		if (a == 1)
			player1Wins++;
		else if (a == 2)
			player2Wins++;
		else if (a == 3)
			draws++;
		system("cls"); // Clear screen with CMD command
		printf("Current score:\n Player 1: %d\n Player 2: %d\n Draws: %d (win/loss/draw)\nPress Q to exit or any key to continue.\n", player1Wins, player2Wins, draws);
		// End loop if user inputs Q
	} while (tolower(getch()) != 'q');
	printf("Press any key to continue...\033[30m"); // Let the user know to press any key to close the program, also hide exit information
}

int game() {
	printf("c - #  - # -\n  #########\nb - # - # -\n  #########\na - # - # -\n  1   2   3\n");
	// Always loop (or at least until return is called)
	for (;;) {
		// If last player was not player 1, make player 1 the active player
		if (player != 1)
			player = 1;
		else
			player = 2;
		// Loop until a valid position is taken as input
		int invalid = 0;
		do {
			invalid = 0;
			printf("Place where? Player %d: ", player);
			char input[3];
			scanf("%s", &input);
			// Set temp to the inputted row
			if (tolower(input[0]) == 'a')
				temp = a;
			else if (tolower(input[0]) == 'b')
				temp = b;
			else if (tolower(input[0]) == 'c')
				temp = c;
			// If the first letter was invalid, loop again
			else invalid = 1;
			// Change values inside temp depending on the second value of input
			if (input[1] == '1' && temp.i1 == 0) {
				temp.c1 = 'X';
				if ((temp.i1 = player) == 2)
					temp.c1 = 'O';
			}
			else if (input[1] == '2' && temp.i2 == 0) {
				temp.c2 = 'X';
				if ((temp.i2 = player) == 2)
					temp.c2 = 'O';
			}
			else if (input[1] == '3' && temp.i3 == 0) {
				temp.c3 = 'X';
				if ((temp.i3 = player) == 2)
					temp.c3 = 'O';
			}
			// If the second letter was invalid, loop again
			else invalid = 1;
			// Update the real grid values
			if (tolower(input[0]) == 'a')
				a = temp;
			if (tolower(input[0]) == 'b')
				b = temp;
			if (tolower(input[0]) == 'c')
				c = temp;
		} while (invalid == 1);
		system("cls"); // Clear screen with CMD command
		// Display grid
		printf("c %c # %c # %c\n  #########\nb %c # %c # %c\n  #########\na %c # %c # %c\n  1   2   3\n", c.c1, c.c2, c.c3, b.c1, b.c2, b.c3, a.c1, a.c2, a.c3);
		// See if any player has winning position, if so: return player as winner
		if ((a.i1 == player && a.i2 == player && a.i3 == player) ||
			(b.i1 == player && b.i2 == player && b.i3 == player) ||
			(c.i1 == player && c.i2 == player && c.i3 == player) ||
			(c.i1 == player && b.i1 == player && a.i1 == player) ||
			(c.i2 == player && b.i2 == player && a.i2 == player) ||
			(c.i3 == player && b.i3 == player && a.i3 == player) ||
			(a.i1 == player && b.i2 == player && c.i3 == player) ||
			(a.i3 == player && b.i2 == player && c.i1 == player))
			return player;
		// If no player is winner, see if all slots on the grid are taken, if so: return as draw
		if (a.i1 != 0 && a.i2 != 0 && a.i3 != 0 && b.i1 != 0 && b.i2 != 0 && b.i3 != 0 && c.i1 != 0 && c.i2 != 0 && c.i3 != 0)
			return 3;
	}
}