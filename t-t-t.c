#include <stdio.h>

char board[10][10];
int boardSize;
int playerCount;

void initializeBoard() {
	for (int i = 0; i < boardSize; i++) {
		for (int j = 0; j < boardSize; j++) {
			board[i][j] = ' ';
		}
	}
}

char getCurrentPlayerSymbol(int player) {
	if (playerCount == 2) {
		return (player == 1) ? 'X' : 'O';
	} else {
		return (player == 1) ? 'X' : (player == 2) ? 'O' : '#';
	}
}

void printBoard() {
	printf("\nTic-Tac-Toe Board (%dx%d):\n\n", boardSize, boardSize);
	
	printf("   ");
	for (int col = 0; col < boardSize; col++) {
		printf(" %2d ", col + 1);
	}
	printf("\n");
	
	printf("   +");
	for (int col = 0; col < boardSize; col++) {
		printf("---+");
	}
	printf("\n");
	
	for (int row = 0; row < boardSize; row++) {
		printf("%2d |", row + 1);
		for (int col = 0; col < boardSize; col++) {
			printf(" %c |", board[row][col]);
		}
		printf("\n");
		
		printf("   +");
		for (int col = 0; col < boardSize; col++) {
			printf("---+");
		}
		printf("\n");
		
	}
}

int makeMove(int player) {
	int row, col;
	char playerSymbol;
	
	if (playerCount == 2) {
		playerSymbol = (player == 1) ? 'X' : 'O';
	} else {
		playerSymbol = (player == 1) ? 'X' : (player == 2) ? 'O' : 'Z';
	}
	
	printf("\nPlayer %d (%c)'s turn:\n", player, playerSymbol);
	
	while (1) {
		printf("Enter row and column (Choose from 1, 2 or 3): ");
		scanf("%d %d", &row, &col);
		
		if (row < 1 || row > boardSize || col < 1 || col > boardSize) {
			printf("Invalid position! Please enter numbers between 1 and %d.\n", boardSize);
		} else if (board[row-1][col-1] != ' ') {
			printf("That position is already taken! Choose another.\n");
		} else {
			board[row-1][col-1] = playerSymbol;
			break;
			
		}
	}
	
	return 1;
}

int checkWinner() {
	char current;
	int win;
	
	for (int i = 0; i < boardSize; i++) {
		current = board[i][0];
		if (current != ' ') {
			win = 1;
			for (int j = 1; j < boardSize; j++) {
				if (board[i][j] != current) {
					win = 0;
					break;
				}
			}
			if (win) return 1;
		}
	}
	
	for (int j = 0; j < boardSize; j++) {
		current = board[0][j];
		if (current != ' ') {
			win = 1;
			for (int i = 1; i < boardSize; i++) {
				if (board[i][j] != current) {
					win = 0;
					break;
				}
			}
			if (win) return 1;
		}
	}
	
	current = board[0][0];
	if (current != ' ') {
		win = 1;
		for (int i = 1; i < boardSize; i++) {
			
			if (board[i][i] != current) {
				win = 0;
				break;
			}
		}
		if (win) return 1;
	}
	
	current = board[0][boardSize-1];
	if (current != ' ') {
		win = 1;
		for (int i = 1; i < boardSize; i++) {
			if (board[i][boardSize-1-i] != current) {
				win = 0;
				break;
			}
		}
		if (win) return 1;
	}
	
	return 0;
}

int main() {
	int currentPlayer = 1;
	int moves = 0;
	int totalMoves;
	int winner = 0;

	printf("Tic-Tac-Toe Game\n");
	printf("================\n");			        
	do {
		printf("Enter board size (3-10): ");
		scanf("%d", &boardSize);
		if (boardSize < 3 || boardSize > 10) {
			printf("Please enter a number between 3 and 10.\n");
		}
	} while (boardSize < 3 || boardSize > 10);
	
	do {
		printf("Enter number of players (2 or 3): ");
		scanf("%d", &playerCount);
		if (playerCount < 2 || playerCount > 3) {
			printf("Please enter 2 or 3 players.\n");
		}
	} while (playerCount < 2 || playerCount > 3);
	
	initializeBoard();
	totalMoves = boardSize * boardSize;
	
	printf("\nGame starting! Players:\n");
	if (playerCount == 2) {
		printf("Player 1: X\n");
		printf("Player 2: O\n");
	} else {
		printf("Player 1: X\n");
		printf("Player 2: O\n");
		printf("Player 3: Z\n");
	}
	
	while (moves < totalMoves) {
		printBoard();
		makeMove(currentPlayer);
		moves++;
		
		if (moves >= boardSize * 2 - 1) {
			winner = checkWinner();
			if (winner) {
				printBoard();
				printf("\nPlayer %d (%c) wins!!! Congrats Man!\n", currentPlayer, getCurrentPlayerSymbol(currentPlayer));
				return 0;
			}
		}
		currentPlayer++;
		if (currentPlayer > playerCount) {
			currentPlayer = 1;
		}
	}
	
	printBoard();
	printf("\nSeems like its a Tie Folks! Better luck next time!\n");

	return 0;
}
		

	




	



	



