#include <stdio.h> //allows standard input and output operations
#include <stdlib.h> //allows dynamic memory allocations
/*
possible moves for a knight in chess
X being horizontal, right = positive, left = negative
Y being vertical, up = positive, down = negative
like in cartesian coordinate system
*/
int moveX[8] = { 2,  1, -1, -2, -2, -1,  1,  2};
int moveY[8] = {-1, -2, -2, -1,  1,  2,  2,  1};
//to check if a move is valid
int isValid(int x, int y, int n, int **visited) {
	return (x >= 0 && x < n && y >= 0 && y < n && !visited[y][x]);
}

int solveKnightTour(int x, int y, int moveCount, int n, int **visited, int *pathX, int *pathY) {
	if (moveCount == n * n) { //naturally, if move count = the number of squares, then it's a solution
		for (int i = 0; i < n * n; i++)
			printf("%d %d\n", pathX[i], pathY[i]);
		return 1;
	}
//to determine the next x and y positions
	for (int i = 0; i < 8; i++) {
		int nextX = x + moveX[i];
		int nextY = y + moveY[i];
//just to keep track and determine if a move is valid or not
		if (isValid(nextX, nextY, n, visited)) {
			visited[nextY][nextX] = 1;
			pathX[moveCount] = nextX;
			pathY[moveCount] = nextY;

			if (solveKnightTour(nextX, nextY, moveCount + 1, n, visited, pathX, pathY))
				return 1;
//if backtrack happens, unmark the visited
			visited[nextY][nextX] = 0;
		}
	}
	return 0;
}

int main() {
	int n;
	int startX, startY;

	scanf("%d %d", &n, &n);
	scanf("%d %d", &startX, &startY);
// for dynamic 2D array
	int **visited = (int **)malloc(n * sizeof(int *));
	for (int i = 0; i < n; i++) {
		visited[i] = (int *)calloc(n, sizeof(int));
	}

	int *pathX = (int *)malloc(n * n * sizeof(int));
	int *pathY = (int *)malloc(n * n * sizeof(int));
//flags the starting point as visited already
	visited[startY][startX] = 1;
	pathX[0] = startX;
	pathY[0] = startY;
//if no full path found
	if (!solveKnightTour(startX, startY, 1, n, visited, pathX, pathY))
		printf("No solution found.\n");

//after the recursion is done
	for (int i = 0; i < n; i++)
		free(visited[i]);
	free(visited);
	free(pathX);
	free(pathY);

	return 0;
}
