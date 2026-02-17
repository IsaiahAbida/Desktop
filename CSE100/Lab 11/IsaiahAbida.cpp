#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int V, E;
    cin >> V >> E;

    // Adjacency list: adj[u] = list of (v, weight)
    vector<vector<pair<int, int>>> adj(V);

    for (int i = 0; i < E; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w}); // undirected graph
    }

    // Key values, parent array, and MST inclusion flag
    vector<int> key(V, INT_MAX);
    vector<int> parent(V, -1);
    vector<bool> inMST(V, false);

    // Min-priority queue: (key, vertex)
    priority_queue<pair<int, int>,
                   vector<pair<int, int>>,
                   greater<pair<int, int>>> pq;

    // Root is vertex 0
    key[0] = 0;
    pq.push({0, 0});

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        // Skip invalid entries
        if (inMST[u]) continue;

        inMST[u] = true;

        // Relax edges
        for (auto &edge : adj[u]) {
            int v = edge.first;
            int weight = edge.second;

            if (!inMST[v] && weight < key[v]) {
                key[v] = weight;
                parent[v] = u;
                pq.push({key[v], v}); // invalidate old entry
            }
        }
    }
    while (!pq. empty()) {
        int u = pq.top().second;
        pq.pop();

        if (inMST[u]) continue; inMST [u] = true;
        
        for (auto &edge : adj [u]) {
            int v = edge.first;
            int weight = edge.second; 

            if (!inMST[v] && weight < key [v]) {
                key [v] = weight;
                parent [v] = u;
                pq.push({key[v], v});
            }
        }
    }


    // Output parents of vertices 1 to V-1
    for (int i = 1; i < V; i++) {
        cout << parent[i] << "\n";
    }

    while (!pq.empty()){
        int u = pq.top().second;
        pq.pop();

        if (inMST[u]) continue; inMST [u]{
            int v = edge.first
        }
    }

    return 0;
}
