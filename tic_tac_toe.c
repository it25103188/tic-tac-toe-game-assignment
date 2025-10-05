#include <stdio.h>
#include <stdlib.h>
#include "computer_logic.h"

char board[10][10];
int boardSize;
int gameMode;
FILE *logFile;

void initializeBoard() {
	for (int i = 0; i < boardSize; i++) {
		for (int j = 0; j < boardSize; j++) {
			board[i][j] = ' ';
		}
	}
}

char getCurrentPlayerSymbol(int player) {
	if (gameMode == 1) {
		return (player == 1) ? 'X' : 'O';
	} else if (gameMode == 2) {
		return (player == 1) ? 'X' : (player == 2) ? 'O' : 'Z';
	} else {
		return (player == 1) ? 'X' : 'O';
	}
}

void logMove(int player, int row, int col, char symbol) {
	fprintf(logFile, "Player %d (%c) -> %d,%d\n", player, symbol, row, col);
	fflush(logFile);
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
	char playerSymbol = getCurrentPlayerSymbol(player);
	
	if (gameMode == 3 && player == 2) {
		computerMove(board, boardSize);
		for (int i = 0; i < boardSize; i++) {
			for (int j = 0; j < boardSize; j++) {
				if (board[i][j] == 'O') {
					int found = 0;
					for (int x = 0; x < boardSize; x++) {
						for (int y = 0; y < boardSize; y++) {
							if (x == i && y == j) continue;
							if (board[x][y] == 'O') found = 1;
						}
					}
					if (!found) {
						logMove(player, i + 1, j + 1, 'O');
						return 1;
					}
				}
			}
		}
		return 1;
	}
	
	if (gameMode == 3) {
		printf("\nYour turn (X):\n");
	} else {
		printf("\nPlayer %d (%c)'s turn:\n", player, playerSymbol);
	}
	
	while (1) {
		printf("Enter row and column (Choose from 1 to %d): ", boardSize);
		scanf("%d %d", &row, &col);
		
		if (row < 1 || row > boardSize || col < 1 || col > boardSize) {
			printf("Invalid position! Please enter numbers between 1 and %d.\n", boardSize);
		} else if (board[row-1][col-1] != ' ') {
			printf("That position is already taken! Choose another.\n");
		} else {
			board[row-1][col-1] = playerSymbol;
			logMove(player, row, col, playerSymbol);
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
	
	srand(12345);
	
	logFile = fopen("tictactoe_log.txt", "w");
	if (logFile == NULL) {
		printf("Cannot create log file. Game will continue without logging.\n");
	} else {
		fprintf(logFile, "Tic-Tac-Toe Game Log\n");
		fprintf(logFile, "====================\n");
		fprintf(logFile, "Board Size: %dx%d\n", boardSize, boardSize);
	}
	
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
		printf("Select game mode:\n");
		printf("1 - 2 Players\n");
		printf("2 - 3 Players\n");
		printf("3 - Play against Computer\n");
		printf("Enter choice (1-3): ");
		scanf("%d", &gameMode);
		if (gameMode < 1 || gameMode > 3) {
			printf("Please enter 1, 2, or 3.\n");
		}
	} while (gameMode < 1 || gameMode > 3);
	
	if (logFile != NULL) {
		fprintf(logFile, "Game Mode: ");
		
		if (gameMode == 1) fprintf(logFile, "2 Players\n");
		else if (gameMode == 2) fprintf(logFile, "3 Players\n");
		else fprintf(logFile, "Vs Computer\n");
		fprintf(logFile, "Moves:\n");
	}
	
	initializeBoard();
	totalMoves = boardSize * boardSize;
	
	printf("\nGame starting!\n");
	if (gameMode == 1) {
		printf("Player 1: X\n");
		printf("Player 2: O\n");
	} else if (gameMode == 2) {
		printf("Player 1: X\n");
		printf("Player 2: O\n");
		printf("Player 3: Z\n");
	} else {
		printf("You: X\n");
		printf("Computer: O\n");
	}
	
	while (moves < totalMoves) {
		printBoard();
		makeMove(currentPlayer);
		moves++;
		
		if (moves >= boardSize * 2 - 1) {
			winner = checkWinner();
			if (winner) {
				printBoard();
				if (logFile != NULL) {
					if (gameMode == 3 && currentPlayer == 1) {
						fprintf(logFile, "Result: You win!\n");
					} else if (gameMode == 3 && currentPlayer == 2) {
						fprintf(logFile, "Result: Computer wins!\n");
					} else {
						fprintf(logFile, "Result: Player %d wins!\n", currentPlayer);
					}
				}
				if (gameMode == 3 && currentPlayer == 1) {
					printf("\nYou win! Congratulations!\n");
				} else if (gameMode == 3 && currentPlayer == 2) {
					printf("\nComputer wins! Better luck next time!\n");
				} else {
					printf("\nPlayer %d (%c) wins!!! Congrats Man!\n", currentPlayer, getCurrentPlayerSymbol(currentPlayer));
				}
				if (logFile != NULL) fclose(logFile);
				return 0;
			}
		}
		currentPlayer++;
		if (currentPlayer > (gameMode == 2 ? 3 : 2)) {
			currentPlayer = 1;
		}
	}
	
	printBoard();
	printf("\nSeems like its a Tie Folks! Better luck next time!\n");
	if (logFile != NULL) {
		fprintf(logFile, "Result: Tie game\n");
		fclose(logFile);
	}
	
	return 0;\
}
