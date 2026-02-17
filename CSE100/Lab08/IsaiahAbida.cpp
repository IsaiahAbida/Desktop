#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;

void dfs1(int v, vector<vector<int>>& adj, vector<bool>& visited, stack<int>& order) {
    visited[v] = true;
    for (int u : adj[v]) {
        if (!visited[u])
            dfs1(u, adj, visited, order);
    }
    order.push(v);
}

void dfs2(int v, vector<vector<int>>& adjT, vector<bool>& visited, vector<int>& component) {
    visited[v] = true;
    component.push_back(v);
    for (int u : adjT[v]) {
        if (!visited[u])
            dfs2(u, adjT, visited, component);
    }
}

int main() {
    int V, E;
    cin >> V >> E;

    vector<vector<int>> adj(V), adjT(V);

    // Read edges
    for (int i = 0; i < E; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adjT[v].push_back(u); // Transpose edge
    }

    vector<bool> visited(V, false);
    stack<int> order;

    // Step 1: Order vertices by finish time in original graph
    for (int i = 0; i < V; ++i) {
        if (!visited[i])
            dfs1(i, adj, visited, order);
    }

    // Step 2: Process nodes in reverse finishing order on transposed graph
    fill(visited.begin(), visited.end(), false);
    vector<int> scc_id(V);

    while (!order.empty()) {
        int v = order.top();
        order.pop();

        if (!visited[v]) {
            vector<int> component;
            dfs2(v, adjT, visited, component);

            int id = *min_element(component.begin(), component.end());
            for (int u : component)
                scc_id[u] = id;
        }
    }

    // Step 3: Output SCC ID for each vertex 0...V-1
    for (int i = 0; i < V; ++i)
        cout << scc_id[i] << "\n";

    return 0;
}
