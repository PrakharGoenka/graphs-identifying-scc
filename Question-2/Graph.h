#include <bits/stdc++.h>
#include "NodeList.h"

using namespace std;


class Graph {
public:
    int nodes, edges;
    vector<vector<int> > adj;
    vector<vector<int> > adj_transpose;

    Graph(int node_count) {
        nodes = node_count;
        adj.resize(nodes);
        adj_transpose.resize(nodes);
    }

    void addEdge(int, int);
    void findPredecessors(int, NodeList &, NodeList &);
    void findDescendants(int, NodeList &, NodeList &);
    void dfs(int, NodeList &, NodeList &);
    void dfsTranspose(int, NodeList &, NodeList &);
};

void Graph::addEdge(int u, int v) {
    adj[u].push_back(v);
    adj_transpose[v].push_back(u);
}

/*
    Function to find the predecessors of the given node in the given graph.
    Return value: reference to vector of int data type, vector[i] == 1, iff
    the i'th node is a predecessor of the given root node
    Parameters:
    1. reference to an object of the Graph class, on which the traversal needs to be done.
    2. number of the root node whose predecessors need to be found.
    3. reference to a vector that marks if a given node belongs to the current subgraph.
*/
void Graph::findPredecessors(int root, NodeList &subgraph, NodeList &pred) {
    dfsTranspose(root, subgraph, pred);
}

/*  TODO :EDIT THE COMMENTS
    Function to find the descendants of the given node in the given graph.
    Return value: reference to vector of int data type, vector[i] == 1, iff
    the i'th node is a predecessor of the given root node
    Parameters:
    1. reference to an object of the Graph class, on which the traversal needs to be done.
    2. number of the root node whose descendants need to be found.
    3. reference to a vector that marks if a given node belongs to the current subgraph.
*/

void Graph::findDescendants(int root, NodeList &subgraph, NodeList &desc) {
    dfs(root, subgraph, desc);
}

void Graph::dfs(int root, NodeList &subgraph, NodeList &visited) {
    visited.add(root);
    for(int i = 0; i < adj[root].size(); i++) {
        int neighbour = adj[root][i];
        if(subgraph.contains(neighbour) and !visited.contains(neighbour)) {
            dfs(neighbour, subgraph, visited);
        }
    }
}

void Graph::dfsTranspose(int root, NodeList &subgraph, NodeList &visited) {
    visited.add(root);
    for(int i = 0; i < adj_transpose[root].size(); i++) {
        int neighbour = adj_transpose[root][i];
        if(subgraph.contains(neighbour) and !visited.contains(neighbour)) {
            dfsTranspose(neighbour, subgraph, visited);
        }
    }
}
