#include <bits/stdc++.h>

using namespace std;


class Graph {
  public:
    int no_vertex, no_edge;
    vector<vector<int> > adj;
    vector<vector<int> > adjt;

    Graph() {
        cout << "Number of Vertices: ";
        cin >> no_vertex;
        cout << "Number of Edges: ";
        cin >> no_edge;
        makeGraph();
    }

    void makeGraph();
};

void Graph:: makeGraph() {
    adj.resize(no_vertex + 1);
    adjt.resize(no_vertex + 1);
    for (int i = 0; i < no_edge; i++) {
        int x, y;
        cin >> x >> y;
        adj[x].push_back(y);
        adjt[y].push_back(x);
    }
}
