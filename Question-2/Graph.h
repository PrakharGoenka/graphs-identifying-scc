#include <bits/stdc++.h>
#include "NodeSet.h"

using namespace std;


/*!
* Abstracts a graph object.
* A class whose instance represents a graph. It has members to
* store the adjacency list of the graph
* store the adjacency list of the transpose of the graph
* manipulate the graph etc.
*/
class Graph {
public:
    int nodes, edges;
    vector<vector<int> > adj; /*!< stores adjacency list of the graph*/
    vector<vector<int> > adj_transpose; /*!< stores adjacency list of the 
    transpose of the graph*/

    /*!
    * Constructor of the class.
    * \param node_count - the number of nodes present in the graph
    */
    Graph(int node_count) {
        nodes = node_count;
        adj.resize(nodes); //resize empty list to the number of nodes 
        adj_transpose.resize(nodes); //resize empty list to the number of nodes
    }

    void addEdge(int, int);
    void findPredecessors(int, NodeSet &, NodeSet &);
    void findDescendants(int, NodeSet &, NodeSet &);
    void dfs(int, NodeSet &, NodeSet &);
    void dfsTranspose(int, NodeSet &, NodeSet &);
};


/*!
* Method to add an edge to the graph.
* \param u - the source vertex of the new edge
* \param u - the destination vertex of the new edge
*/
void Graph::addEdge(int u, int v) {
    adj[u].push_back(v); // add edge to the original graph
    adj_transpose[v].push_back(u); // add reversed edge to the transposed graph
}


/*!
* Method to find the predecessors of the given node in the given graph.
* \param root - node whose predecessors are to be found.
* \param subgraph - ref to the nodeset of nodes in the remaining subgraph. 
* \param pred - ref to a nodeset that stores the resulting nodes.
*/
void Graph::findPredecessors(int root, NodeSet &subgraph, NodeSet &pred) {
    dfsTranspose(root, subgraph, pred);
}


/*!
* Method to find the descendants of the given node in the given graph.
* \param root - node whose sudescendants are to be found.
* \param subgraph - ref to the nodeset of nodes in the remaining subgraph. 
* \param desc - ref to a nodeset that stores the resulting nodes.
*/
void Graph::findDescendants(int root, NodeSet &subgraph, NodeSet &desc) {
    dfs(root, subgraph, desc);
}


/*!
* Method to implement depth first search from a node on a given subgraph.
* \param root - node from which the search needs to be done.
* \param subgraph - ref to a nodeset that represents the subgraph on 
  which the search needs to be done.
* \param visited - ref to a nodeset that represents the set of nodes
  that have already been visited.
*/
void Graph::dfs(int root, NodeSet &subgraph, NodeSet &visited) {
    visited.add(root);
    for(int i = 0; i < adj[root].size(); i++) {
        int neighbour = adj[root][i];
        if(subgraph.contains(neighbour) and !visited.contains(neighbour)) {
            dfs(neighbour, subgraph, visited);
        }
    }
}


/*!
* Method to implement depth first search from a node on the 
  transpose of a given subgraph.
* \param root - node from which the search needs to be done.
* \param subgraph - ref to a nodeset that represents the subgraph on 
  which the search needs to be done.
* \param visited - ref to a nodeset that represents the set of nodes
  that have already been visited.
*/
void Graph::dfsTranspose(int root, NodeSet &subgraph, NodeSet &visited) {
    visited.add(root);
    for(int i = 0; i < adj_transpose[root].size(); i++) {
        int neighbour = adj_transpose[root][i];
        if(subgraph.contains(neighbour) and !visited.contains(neighbour)) {
            dfsTranspose(neighbour, subgraph, visited);
        }
    }
}
