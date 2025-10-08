#include <bits/stdc++.h>
using namespace std;

struct graph {
    int n;
    vector<vector<pair<int,int>>> adj;
    map<pair<int,int>, int> edgeName;

    void init(int v) {
        n = v;
        adj.assign(v+1, {});
    }

    void add_edge(int name, int u, int v, int w) {
    adj[u].push_back({v, w});
    adj[v].push_back({u, w});
    edgeName[{u, v}] = name;
    edgeName[{v, u}] = name; // tambahkan ini!
}


    void tsp(int start) {
        int bestCost = INT_MAX;
        vector<int> bestPath;

        queue<pair<vector<int>, int>> q;
        q.push(make_pair(vector<int>{start}, 0));

        while (!q.empty()) {
            pair<vector<int>, int> frontPair = q.front();
            vector<int> path = frontPair.first;
            int cost = frontPair.second;
            q.pop();

            if ((int)path.size() == n) {
                int last = path.back();
                for (size_t i = 0; i < adj[last].size(); i++) {
                    int v = adj[last][i].first;
                    int w = adj[last][i].second;
                    if (v == start) {
                        int total = cost + w;
                        if (total < bestCost) {
                        bestCost = total;
                        bestPath = path;
                        bestPath.push_back(start);
                    }
                    }
                }
                continue;
            }

            int current = path.back();
            vector<pair<int,int>> neighbors = adj[current];
            sort(neighbors.begin(), neighbors.end(), [](const pair<int,int> &a, const pair<int,int> &b){
                return a.second < b.second;
            });

            int limit = min((int)neighbors.size(), 2);
            for (int i = 0; i < limit; i++) {
                int next = neighbors[i].first;
                int weight = neighbors[i].second;

                if (find(path.begin(), path.end(), next) == path.end() && next != start) {
                    vector<int> newPath = path;
                    newPath.push_back(next);
                    q.push(make_pair(newPath, cost + weight));
                }
            }
        }
        cout << "Cost: " << bestCost << endl;

        // Pastikan path terbaik dimulai dari 'start'
        if (!bestPath.empty()) {
    // temukan posisi start dalam path
            auto it = find(bestPath.begin(), bestPath.end(), start);
            if (it != bestPath.end())
                rotate(bestPath.begin(), it, bestPath.end());
        }

        cout << "Route: ";
        for (int i = 0; i < (int)bestPath.size() - 1; i++) {
            int u = bestPath[i];
            int v = bestPath[i + 1];

            // kalau arah (u,v) tidak ditemukan, coba arah sebaliknya
            if (edgeName.find(make_pair(u, v)) != edgeName.end())
                cout << edgeName[make_pair(u, v)];
            else
                cout << edgeName[make_pair(v, u)];

            if (i < (int)bestPath.size() - 2) cout << ", ";
        }
        cout << endl;
    }
};

int main() {
    int n, e;
    cin >> n >> e;

    graph g;
    g.init(n);

    for (int i = 0; i < e; i++) {
        int name, u, v, w;
        cin >> name >> u >> v >> w;
        g.add_edge(name, u, v, w);
    }

    int start;
    cin >> start;

    g.tsp(start);
}
