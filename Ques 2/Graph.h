#include <bits/stdc++.h>

using namespace std;


class Graph {
  public:
    long long int no_vertex, no_edge;
    vector<vector<long long int> > adj;
    vector<vector<long long int> > adjt;

    Graph() {
        cout << "Number of Vertices: ";
        cin >> no_vertex;
        cout << "Number of Edges: ";
        cin >> no_edge;
        makeGraph();
    }

    void makeGraph();
    void findPredecessors(long long int, vector <long long int>&, vector <long long int>&);
    void findDescendants(long long int, vector <long long int>&, vector <long long int>&);
    void dfs(long long int, vector <long long int>&, vector <long long int>&);
    void dfsTranspose(long long int, vector <long long int>&, vector <long long int>&);
};

void Graph :: makeGraph() {
    adj.resize(no_vertex + 1);
    adjt.resize(no_vertex + 1);
    for (long long int i = 0; i < no_edge; i++) {
        long long int x, y;
        cin >> x >> y;
        adj[x].push_back(y);
        adjt[y].push_back(x);
    }
}

/*
    Function to find the predecessors of the given node in the given graph.
    Return value: reference to vector of long long int data type, vector[i] == 1, iff
    the i'th node is a predecessor of the given root node
    Parameters:
    1. reference to an object of the Graph class, on which the traversal needs to be done.
    2. number of the root node whose predecessors need to be found.
    3. reference to a vector that marks if a given node belongs to the current subgraph.
*/
void Graph :: findPredecessors(long long int root, vector <long long int> &valid, vector <long long int> &pred) {
    dfsTranspose(root, valid, pred);
}

/*  TODO :EDIT THE COMMENTS
    Function to find the descendants of the given node in the given graph.
    Return value: reference to vector of long long int data type, vector[i] == 1, iff
    the i'th node is a predecessor of the given root node
    Parameters:
    1. reference to an object of the Graph class, on which the traversal needs to be done.
    2. number of the root node whose descendants need to be found.
    3. reference to a vector that marks if a given node belongs to the current subgraph.
*/
void Graph :: findDescendants(long long int root, vector <long long int> &valid, vector <long long int> &desc) {
    dfs(root, valid, desc);
}

void Graph:: dfs(long long int root, vector <long long int> &valid, vector <long long int> &visited) {
    visited[root] = 1;
    for(long long int i = 0; i < adj[root].size(); i++) {
        long long int neighbour = adj[root][i];
        if(valid[neighbour] and !visited[neighbour]) {
            dfs(neighbour, valid, visited);
        }
    }
}

void Graph:: dfsTranspose(long long int root, vector <long long int> &valid, vector <long long int> &visited) {
    visited[root] = 1;
    for(long long int i = 0; i < adjt[root].size(); i++) {
        long long int neighbour = adjt[root][i];
        if(valid[neighbour] and !visited[neighbour]) {
            dfsTranspose(neighbour, valid, visited);
        }
    }
}
