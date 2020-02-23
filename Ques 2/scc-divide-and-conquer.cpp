#include <bits/stdc++.h>
#include "Graph.h"

using namespace std;

/* 
    Function to mark all reachable nodes from the given node of the graph using DFS.
    Return type: void
    Parameters:
    1. reference to the adjacency list of the graph on which the traversal needs to be done.
    2. number of node from which the dfs needs to be started.
    3. reference to a vector that marks if a given node belongs to the current subgraph.
    4. reference to a vector that marks if a given node has been visited in this traversal.
*/ 
void dfs(vector <vector <int>> adj, int root, vector <int> &valid, vector <int> &visited) {
    visited[root] = 1;
    for(int i = 0; i < adj[root].size(); i++) {
        int neighbour = adj[root][i];
        if(valid[neighbour] and !visited[neighbour]) {
            dfs(adj, neighbour, valid, visited);
        }
    }
}

/*
    Function to return the predecessors of the given node in the given graph.
    Return value: reference to vector of int data type, vector[i] == 1, iff
    the i'th node is a predecessor of the given root node
    Parameters:
    1. reference to an object of the Graph class, on which the traversal needs to be done.
    2. number of the root node whose predecessors need to be found.
    3. reference to a vector that marks if a given node belongs to the current subgraph.
*/
void findPred(Graph &graph, int root, vector <int> &valid, vector <int> &pred) {
    dfs(graph.adjt, root, valid, pred);
}

/*
    Function to return the descendants of the given node in the given graph.
    Return value: reference to vector of int data type, vector[i] == 1, iff
    the i'th node is a predecessor of the given root node
    Parameters:
    1. reference to an object of the Graph class, on which the traversal needs to be done.
    2. number of the root node whose descendants need to be found.
    3. reference to a vector that marks if a given node belongs to the current subgraph.
*/
void findDesc(Graph &graph, int root, vector <int> &valid, vector <int> &desc) {
    dfs(graph.adj, root, valid, desc);
}

/* 
    A (recursive) function to find the strongly connected component
    for the first valid vertex of the given graph, and add it to the list of connected components.
    Return value: void
    Parameters:
    1. reference to an object of the Graph class, on which the traversal needs to be done.
    2. reference to a vector that marks if a given node belongs to the current subgraph.
    3. reference to a vector of vectors of int data type, where each row stores a
    strongly connected component of the given graph.
*/
void sccDivideAndConquer(Graph &graph, vector <int> &valid, vector <vector<int>> &connected_components, int *length) {
    int no_vertex = graph.no_vertex;

    // initialize the root node to -1
    int root = -1;

    // find a node that is part of the subgraph
    for(int i = 0; i < no_vertex; i++) {
        if(valid[i]) {
            root = i;
            break;
        }
    }

    if(root == -1) { // no valid node is left, i.e. all nodes have already been considered in some SCC.
        return;
    }

    // get predecessors and descendants for the root.
    vector <int> pred(no_vertex), desc(no_vertex);
    findPred(graph, root, valid, pred);
    findDesc(graph, root, valid, desc);

    *length = *length + 1;
    // push a new row to the connected components

    // find nodes that are both, predecessors as well as descendants
    // and add them to the new connected component.
    // mark them invalid, so that these nodes are not further used in the graph.
    for(int i = 0; i < no_vertex; i++) {
        if(pred[i] and desc[i]) {
            connected_components[*length - 1].push_back(i);
            valid[i] = 0;
        }
    }

    // seperate list of valid nodes, each corresponding to the set:
    // predecessors, descendants and remainder
    vector <int> valid_pred(valid), valid_desc(valid), valid_rem(valid);
    for(int i = 0; i < no_vertex; i++) {
        valid_pred[i] *= pred[i];
        valid_desc[i] *= desc[i];
        valid_rem[i] *= (1-pred[i])*(1-desc[i]);
    }

    // recursively call the function for the 3 subgraphs 
    sccDivideAndConquer(graph, valid_pred, connected_components, length);
    sccDivideAndConquer(graph, valid_desc, connected_components, length);
    sccDivideAndConquer(graph, valid_rem, connected_components, length);
}

/*
    Function to return the strongly connected components in the given graph.
    Return value: reference to a vector of vectors of int data type,
    where each row stores a strongly connected component of the given graph.
    Parameters: 1. reference to an object of the Graph class, whose SCCs are to be found.
*/
void getConnectedComponents(Graph &graph, vector <vector <int> >& connected_components, int *length) {
    vector <int> valid(graph.no_vertex, 1);
    sccDivideAndConquer(graph, valid, connected_components, length);
}

/*
    Function to print connected components. 
    Return type: Void
    Parameters: 1. reference to a vector of vector of int type, where each row is an scc.
*/
void printConnectedComponents(vector <vector <int> > &connected_components, int length) {
    // get number of components
    int components = connected_components.size();
    cout << "The graph has "  << components << " components\n";
    
    for(int i = 0; i < length; i++) {
        cout << "Component Number " << i+1 << endl;
        for(int j = 0; j < connected_components[i].size(); j++) {
            cout << connected_components[i][j] << " ";
        }
        cout << endl;
    }
}

int main() {
    Graph graph;
    vector <vector <int> > connected_components(graph.no_vertex);
    int length = 0;
    getConnectedComponents(graph, connected_components, &length);
    printConnectedComponents(connected_components, length);
}
