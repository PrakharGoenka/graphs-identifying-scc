#include <bits/stdc++.h>
#include "Graph.h"

using namespace std;

// global variables start
vector<bool> visited;
vector<int> order, component;
// global variables end

void dfsOnGraph(Graph &g, int v) {
    visited[v] = true;
    for (size_t i = 0; i < g.adj[v].size(); i++) {
        if (!visited[g.adj[v][i]]) {
            dfsOnGraph(g, g.adj[v][i]);
        }
    }
    order.push_back(v);
}

void dfsOnTgraph(Graph &g, int v) {
    visited[v] = true;
    component.push_back(v);
    for (size_t i = 0; i < g.adjt[v].size(); i++) {
        if (!visited[g.adjt[v][i]]) {
            dfsOnTgraph(g, g.adjt[v][i]);
        }
    }
}
 
void getConnectedComponents(Graph &g) {
    vector<vector<int> > ans;
    int n = g.no_vertex;
    visited.assign(n, false);
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            dfsOnGraph(g, i);
        }
    }
    visited.assign(n, false);
    for (int i = 0; i < n; i++) {
        int v = order[n - 1 - i];
        if (!visited[v]) {
            dfsOnTgraph(g, v);
            ans.push_back(component);
            component.clear();
        }
    }

    for (auto component: ans) {
        for (auto node: component) {
            cout << node << " ";
        }
        cout << "\n";
    }
}

int main() {
    Graph graph;
    getConnectedComponents(graph);
    return 0;
}
