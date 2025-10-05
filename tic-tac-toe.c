#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

char** createBoard(int size);
void displayBoard(char** board, int size);
bool makeMove(char** board, int size, int row, int col, char symbol);
bool checkWin(char** board, int size, char symbol);
bool checkDraw(char** board, int size);
void logBoard(FILE* file, char** board, int size);
void freeBoard(char** board, int size);

int main() {
	int n;
	printf("Enter board size (3 - 10): ");
	scanf("%d", &n);
	
	if (n < 3 || n > 10) {
		printf("Invalid size!\n");
		return 1;
	}
	
	char** board = createBoard(n);
	FILE* logFile = fopen("game_log.txt", "w");
	
	char players[2] = {'X', 'O'};
	int currentPlayer = 0;
	int row, col;
	
	while (true) {
		displayBoard(board, n);
		printf("Player %c, enter row and column (0-%d): ", players[currentPlayer], n - 1);
		scanf("%d %d", &row, &col);
		
		if (!makeMove(board, n, row, col, players[currentPlayer])) {
			printf("Invalid move, try again!\n");
			continue;
		}
		
		logBoard(logFile, board, n);
		
		if (checkWin(board, n, players[currentPlayer])) {
			displayBoard(board, n);
			printf("Player %c wins!\n", players[currentPlayer]);
			break;
		}
		
		if (checkDraw(board, n)) {
			displayBoard(board, n);
			printf("It's a draw!\n");
			break;
		}
		
		currentPlayer = 1 - currentPlayer;
	}
	
	fclose(logFile);
	freeBoard(board, n);
	return 0;
}

char** createBoard(int size) {
	char** board = (char**)malloc(size * sizeof(char*));
	for (int i = 0; i < size; i++) {
		board[i] = (char*)malloc(size * sizeof(char));
		for (int j = 0; j < size; j++) {
			board[i][j] = ' ';
		}
	}
	return board;
}

void displayBoard(char** board, int size) {
	printf("\n");
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			printf(" %c ", board[i][j]);
			if (j < size - 1) printf("|");
		}
		printf("\n");
		if (i < size - 1) {
			for (int j = 0; j < size; j++) printf("---");
			printf("\n");
		}
	}
	printf("\n");
}

bool makeMove(char** board, int size, int row, int col, char symbol) {
	if (row < 0 || row >= size || col < 0 || col >= size) return false;
	if (board[row][col] != ' ') return false;
	board[row][col] = symbol;
	return true;
}

bool checkWin(char** board, int size, char symbol) {
	for (int i = 0; i < size; i++) {
		bool rowWin = true;
		for (int j = 0; j < size; j++)
			if (board[i][j] != symbol) rowWin = false;
		if (rowWin) return true;
	}
	for (int j = 0; j < size; j++) {
		bool colWin = true;
		for (int i = 0; i < size; i++)
			if (board[i][j] != symbol) colWin = false;
		if (colWin) return true;
	}
	bool diag1 = true;
	for (int i = 0; i < size; i++)
		if (board[i][i] != symbol) diag1 = false;
	if (diag1) return true;
	
	bool diag2 = true;
	for (int i = 0; i < size; i++)
		if (board[i][size - i - 1] != symbol) diag2 = false;
	if (diag2) return true;
	
	return false;
}

bool checkDraw(char** board, int size) {
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
			if (board[i][j] == ' ') return false;
	return true;
}

void logBoard(FILE* file, char** board, int size) {
	fprintf(file, "\nCurrent Board:\n");
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
			fprintf(file, "%c ", board[i][j]);
		fprintf(file, "\n");
	}
	fprintf(file, "----------------------\n");
	fflush(file);
}

void freeBoard(char** board, int size) {
	for (int i = 0; i < size; i++) free(board[i]);
	free(board);
}

