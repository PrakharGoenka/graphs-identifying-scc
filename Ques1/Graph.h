#include <bits/stdc++.h>

using namespace std;

//! Represents Data Structure Graph
/*!
    Maintains graph in form of adjacency list.
*/
class Graph {
  public:
    int no_vertex, no_edge;
    vector<vector<int> > adj;
    vector<vector<int> > adjt;
    
    //! Constructor for the graph
    /*!
        Inputs number of vertices and number of edges.
    */
    Graph() {
        // cout << "Number of Vertices: ";
        cin >> no_vertex;
        // cout << "Number of Edges: ";
        cin >> no_edge;
        makeGraph();
    }

    //!Makes Graph
    /*!
        Takes user input and builds the adjacency list
    */
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
