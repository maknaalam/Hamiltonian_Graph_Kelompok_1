#include <bits/stdc++.h>
using namespace std;

// Struktur untuk merepresentasikan satu edge
struct Edge {
    int id;      // ID edge (misal: 0, 1, 2, 3)
    int to;      // node tujuan dari node asal
    int cost;    // bobot (biaya) edge
};

struct Graph {
    int totalNodes;
    vector<vector<Edge>> adjacency;  // adjacency list: adjacency[u] menyimpan daftar edge dari node u

    void init(int nodeCount) {
        totalNodes = nodeCount;
        adjacency.assign(nodeCount + 1, {});
    }

    void addEdge(int edgeId, int fromNode, int toNode, int weight) {
        adjacency[fromNode].push_back({edgeId, toNode, weight});
        adjacency[toNode].push_back({edgeId, fromNode, weight});
    }

    // Variabel untuk menyimpan hasil terbaik
    int bestTotalCost;
    vector<int> bestEdgeRoute;

    // DFS rekursif untuk mencari semua kombinasi jalur
    void dfs(
        int currentNode,
        int startNode,
        vector<bool>& visitedNode,
        int currentCost,
        vector<int>& currentEdgeRoute
    ) {
        // Cek apakah semua node sudah dikunjungi
        bool allVisited = true;
        for (int i = 1; i <= totalNodes; i++) {
            if (!visitedNode[i]) {
                allVisited = false;
                break;
            }
        }

        // Jika semua sudah dikunjungi, coba kembali ke startNode
        if (allVisited) {
            for (const auto& edge : adjacency[currentNode]) {
                if (edge.to == startNode) {
                    int totalCost = currentCost + edge.cost;
                    if (totalCost < bestTotalCost) {
                        bestTotalCost = totalCost;
                        bestEdgeRoute = currentEdgeRoute;
                        bestEdgeRoute.push_back(edge.id);  // tambahkan edge terakhir (kembali ke awal)
                    }
                }
            }
            return;
        }

        // Jelajahi semua tetangga yang belum dikunjungi
        for (const auto& edge : adjacency[currentNode]) {
            int nextNode = edge.to;
            int edgeId = edge.id;
            int edgeCost = edge.cost;

            if (!visitedNode[nextNode]) {
                visitedNode[nextNode] = true;
                currentEdgeRoute.push_back(edgeId);

                dfs(nextNode, startNode, visitedNode, currentCost + edgeCost, currentEdgeRoute);

                currentEdgeRoute.pop_back();      // backtrack: hapus edge terakhir
                visitedNode[nextNode] = false;    // tandai belum dikunjungi
            }
        }
    }

    // Fungsi utama untuk menyelesaikan TSP
    void solveTSP(int startNode) {
        bestTotalCost = INT_MAX;
        bestEdgeRoute.clear();

        vector<bool> visitedNode(totalNodes + 1, false);
        visitedNode[startNode] = true;

        vector<int> currentEdgeRoute;
        dfs(startNode, startNode, visitedNode, 0, currentEdgeRoute);

        if (bestTotalCost == INT_MAX) {
            cout << "No solution found." << endl;
        } else {
            cout << "Cost: " << bestTotalCost << endl;
            cout << "Route: ";
            for (size_t i = 0; i < bestEdgeRoute.size(); i++) {
                cout << bestEdgeRoute[i];
                if (i < bestEdgeRoute.size() - 1) cout << ", ";
            }
            cout << endl;
        }
    }
};

int main() {
    int nodeCount, edgeCount;
    cin >> nodeCount >> edgeCount;

    Graph g;
    g.init(nodeCount);

    for (int i = 0; i < edgeCount; i++) {
        int edgeId, from, to, cost;
        cin >> edgeId >> from >> to >> cost;
        g.addEdge(edgeId, from, to, cost);
    }

    int startNode;
    cin >> startNode;
    /*
    3          ← jumlah node
    4          ← jumlah edge
    0 1 2 10   ← edgeId, from, to, cost
    1 2 3 5
    2 3 1 7
    3 3 1 2
    1          ← start node
    */
    // main() → Graph.solveTSP() → Graph.dfs()
    g.solveTSP(startNode);
    return 0;
}
