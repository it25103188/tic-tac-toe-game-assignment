#include <stdio.h>
#include <stdlib.h>

void computerMove(char board[10][10], int boardSize) {
	int emptySpots = 0;
	for (int i = 0; i < boardSize; i++) {
		for (int j = 0; j < boardSize; j++) {
			if (board[i][j] == ' ') {
				emptySpots++;
			}
		}
	}
	
	if (emptySpots == 0) return;
	
	int target = rand() % emptySpots;
	int count = 0;
	
	for (int i = 0; i < boardSize; i++) {
		for (int j = 0; j < boardSize; j++) {
			if (board[i][j] == ' ') {
				if (count == target) {
					board[i][j] = 'O';
					printf("\nComputer (O) plays at position %d %d\n", i + 1, j + 1);
					return;
				}
				count++;
			}
		}
	}
}

