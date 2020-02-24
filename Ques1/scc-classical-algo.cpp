#include <bits/stdc++.h>
#include "Graph.h"

typedef long long int;

using namespace std;

// global variables start
vector<bool> visited;
vector<int> order, component;
// global variables end

//! Performs dfs on graph.
/*!
    \param g - Graph data structure 
    \param v - root vertex from which dfs starts
*/
void dfsOnGraph(Graph &g, int v) {
    visited[v] = true;
    for (auto node: g.adj[v]) {
        if (!visited[node]) {
            dfsOnGraph(g, node);
        }
    }
    order.push_back(v);
}

//! Performs dfs on transposed graph.
/*!
    \param g - Graph data structure.
    \param v - root vertex from which dfs starts.
*/
void dfsOnTgraph(Graph &g, int v) {
    visited[v] = true;
    component.push_back(v);
    for (auto node: g.adjt[v]) {
        if (!visited[node]) {
            dfsOnTgraph(g, node);
        }
    }
}

//! Prints all the connected components.
/*!
    \param g - graph data structure passed as reference.
*/
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

    int ns = 0;

    for (auto component: ans) {
        ns = max(ns, (int) component.size());
        for (auto node: component) {
            cout << node << " ";
        }
        cout << "\n";
    }
    cout << "Number of nodes in largest component " << ns << endl;
}

signed main() {
    #ifndef ONLINE_JUDGE
        // freopen("input.txt", "r", stdin);
        // freopen("output.txt", "w", stdout);
    #endif // ONLINE_JUDGE
    Graph graph;
    getConnectedComponents(graph);
    return 0;
}
