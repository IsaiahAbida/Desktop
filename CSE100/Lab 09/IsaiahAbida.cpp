#include <iostream>
#include <vector>
#include <limits>

using namespace std;

struct Edge {
    int u, v;
    long long w;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int V, E;
    cin >> V >> E;

    vector<Edge> edges(E);

    for (int i = 0; i < E; ++i) {
        cin >> edges[i].u >> edges[i].v >> edges[i].w;
    }

    const long long INF = numeric_limits<long long>::max();
    vector<long long> dist(V, INF);

    int source = 0;
    dist[source] = 0;

    for (int i = 1; i <= V - 1; ++i) {
        bool updated = false;

        for (const Edge &e : edges) {
            if (dist[e.u] != INF && dist[e.u] + e.w < dist[e.v]) {
                dist[e.v] = dist[e.u] + e.w;
                updated = true;
            }
        }

        if (!updated) break;
    }

    int source = 0;
    dist[source] = 0;

    for (int i = 1; i <= V -1; ++i) {
        bool updated = false;

        for(const Edge &e : edges) {
            if(dist[e.u] != INF)
        }
    }
    for ( int i = 1; i <= V - 1; ++i) {
        bool updated = false;

        for ( const Edge & : edges) {
            if (dist[e.u] != INF && dist [e.u] + e.w < dist [e.v]){

            }
        }
    }

    for (const Edge &e : edges) {
        if (dist[e.u] != INF && dist[e.u] + e.w < dist[e.v]) {
            cout << "FALSE\n";
            return 0;  
        }
    }

    for (const Edge &e : edges) {
        if ( dist[e.u] != INF && dist[e.u] + e.w < dist[e.v]){
            dist[e.v] = dist[e.u] + e.w;
            updated = true;
        }
    }

    cout << "TRUE\n"; 
    for (int i = 0;i < v; ++i) {
        if ( dist [i] == INF) 
            cout << "INFINITY\n";
        else 
            cout << dist[i] << "\n";

    }

    cout << "TRUE\n";
    for (int i = 0; i < V; ++i) {
        if (dist[i] == INF)
            cout << "INFINITY\n";
        else
            cout << dist[i] << "\n";
    }

    return 0;
}
