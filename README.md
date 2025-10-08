# Hamiltonian_Graph_Kelompok_1

Group Number: 1 

Group Members:
-	Alif Muflih Jauhary (5025241003)
-	Rayen Yeriel Mangiwa (5025241262)
-	Makna Alam Pratama (5025241077)

## Problem for TSP & CPP

![1](hamiltonian.png)<br />

Note on input <br />
first two lines defines the number of nodes n and number of edges e respectively <br />
next e lines consists of set of number denoting: name of edge, two edges that it connects, and its cost <br />
last line denotes the starting point (and finishing point) of the TSP/CPP solution. <br />

### Travelling Salesman Problem (TSP)

```

```

### Chinese Postman Problem (CPP)

```
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_NODES 50
#define MAX_EDGES 100
#define INF INT_MAX

typedef struct {
    int to;
    int cost;
} Edge;

int n, e;
int graph[MAX_NODES][MAX_NODES];
int dist[MAX_NODES][MAX_NODES];
int next_node[MAX_NODES][MAX_NODES];
Edge adj[MAX_NODES][MAX_EDGES * 2];
int adj_count[MAX_NODES] = {0};
int degree[MAX_NODES] = {0};

void remove_edge(int u, int v, int cost) {
    for (int i = 0; i < adj_count[u]; i++) {
        if (adj[u][i].to == v && adj[u][i].cost == cost) {
            adj[u][i] = adj[u][adj_count[u] - 1];
            adj_count[u]--;
            return;
        }
    }
}

void floyd_warshall() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            dist[i][j] = graph[i][j];
            if (i != j && graph[i][j] != INF) {
                next_node[i][j] = j;
            } else {
                next_node[i][j] = -1;
            }
        }
    }

    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (dist[i][k] != INF && dist[k][j] != INF && dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                    next_node[i][j] = next_node[i][k];
                }
            }
        }
    }
}

int main() {
    printf("Masukkan input untuk Chinese Postman Problem:\n");

    scanf("%d %d", &n, &e);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) graph[i][j] = 0;
            else graph[i][j] = INF;
        }
    }

    long long total_edge_cost = 0;
    int edge_name, u, v, cost;

    for (int i = 0; i < e; i++) {
        scanf("%d %d %d %d", &edge_name, &u, &v, &cost);
        u--; 
        v--;

        total_edge_cost += cost;
        degree[u]++;
        degree[v]++;

        adj[u][adj_count[u]++] = (Edge){v, cost};
        adj[v][adj_count[v]++] = (Edge){u, cost};

        if (cost < graph[u][v]) {
            graph[u][v] = cost;
            graph[v][u] = cost;
        }
    }

    int start_node;
    scanf("%d", &start_node);
    start_node--;

    int odd_nodes[MAX_NODES];
    int odd_count = 0;
    for (int i = 0; i < n; i++) {
        if (degree[i] % 2 != 0) {
            odd_nodes[odd_count++] = i;
        }
    }

    floyd_warshall();

    long long pairing_cost = 0;
    if (odd_count > 0) {
        int node1 = odd_nodes[0];
        int node2 = odd_nodes[1];
        pairing_cost += dist[node1][node2];

        int path[MAX_NODES];
        int path_len = 0;
        int curr = node1;
        while (curr != node2) {
            path[path_len++] = curr;
            curr = next_node[curr][node2];
        }
        path[path_len++] = node2;

        for (int i = 0; i < path_len - 1; i++) {
            int path_u = path[i];
            int path_v = path[i+1];
            int path_cost = graph[path_u][path_v];
            adj[path_u][adj_count[path_u]++] = (Edge){path_v, path_cost};
            adj[path_v][adj_count[path_v]++] = (Edge){path_u, path_cost};
        }
    }
    
    long long cpp_cost = total_edge_cost + pairing_cost;
    int stack[MAX_EDGES * 2];
    int top = -1;
    int circuit[MAX_EDGES * 2];
    int circuit_len = 0;

    stack[++top] = start_node;

    while (top != -1) {
        int u_curr = stack[top];
        if (adj_count[u_curr] > 0) {
            Edge next_edge = adj[u_curr][--adj_count[u_curr]];
            int v_next = next_edge.to;
            
            remove_edge(v_next, u_curr, next_edge.cost);
            
            stack[++top] = v_next;
        } else {
            circuit[circuit_len++] = stack[top--];
        }
    }

    printf("\n--- HASIL ---\n");
    printf("Cost: %lld\n", cpp_cost);
    printf("Route: ");
    for (int i = circuit_len - 1; i >= 0; i--) {
        printf("%d", circuit[i] + 1);
        if (i > 0) {
            printf(", ");
        }
    }
    printf("\n");

    return 0;
}
```
To use the program, start by entering the number of nodes and the number of edges on the first line, separated by a space, and then press Enter. Next, on the following lines, input the details for each edge by typing four numbers—representing the edge's name, the two nodes it connects, and its cost—each separated by a space. After all the edges have been entered, type the single number for the starting node on the final line and press Enter again. The program will then automatically run and display the result. <br />

Input #1 <br />
```
4 5 
0 1 2 10
1 2 3 5
2 3 4 8
3 4 1 6
4 1 3 12
1
```
Output #1:<br />

Cost: 53 <br />
Route: 1, 2, 3, 4, 1, 3, 1 <br />

Input #2 <br />
```
5 6
0 1 2 3
1 2 3 5
2 3 4 4
3 4 1 2
4 1 5 6
5 2 5 7
1
```
Output #2: <br />

Cost: 30 <br />
Route: 1, 4, 3, 2, 5, 1, 2, 1 <br />

### The Knight's Tour

| | | | | |
| --- | --- | --- | --- | --- |
| 0,0  | 1,0 | 2,0  | 3,0  | 4,0  |
| 0,1  | 1,1 | 2,1  | 3,1  | 4,1  |
| 0,2  | 1,2 | 2,2  | 3,2  | 4,2  |
| 0,3  | 1,3 | 2,3  | 3,3  | 4,3  |
| 0,4  | 1,4 | 2,4  | 3,4  | 4,4  |

Note on input <br />
first line defines the size of the chessboard <br />
second line defines the starting position of the knight (coordinate) <br />
<br /> <br />
Note on output <br />
It will be the coordinates the knight will go until it visit all squares in the chessboard <br />
<br /> <br />
Code:
```
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
```
How to use: <br />
enter 2(two) numbers separated by space(spacebar) on the first line, that initiates size of chessboard; <br />
click enter to begin new line; <br />
enter another 2(two) numbers separated by space(spacebar) on the next line, this initiates the starting point (X,Y); <br />
run the program. <br />
Sample Inputs and Outputs: <br />
Input #0 <br />
```
5 5 
2 2
```
Output: <br />
2 2 <br />
4 1 <br />
2 0 <br />
0 1 <br />
1 3 <br />
3 4 <br />
4 2 <br />
3 0 <br />
1 1 <br />
0 3 <br />
2 4 <br />
4 3 <br />
3 1 <br />
1 0 <br />
0 2 <br />
1 4 <br />
3 3 <br />
2 1 <br />
4 0 <br />
3 2 <br />
4 4 <br />
2 3 <br />
0 4 <br />
1 2 <br />
0 0 <br />

other inputs example <br />
Input #1 <br />
```
6 6
0 0
```
Output: <br />
0 0 <br />
1 2 <br />
3 1 <br />
5 0 <br />
4 2 <br />
3 0 <br />
1 1 <br />
0 3 <br />
2 2 <br />
4 1 <br />
2 0 <br />
0 1 <br />
1 3 <br />
0 5 <br />
2 4 <br />
4 5 <br />
5 3 <br />
3 2 <br />
5 1 <br />
4 3 <br />
5 5 <br />
3 4 <br />
1 5 <br />
2 3 <br />
0 4 <br />
2 5 <br />
4 4 <br />
5 2 <br />
4 0 <br />
2 1 <br />
3 3 <br />
5 4 <br />
3 5 <br />
1 4 <br />
0 2 <br />
1 0 <br />

Input #2 <br />
```
3 3
0 0
```
Output: <br />
No solution found. <br />

