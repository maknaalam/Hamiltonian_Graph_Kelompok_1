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
