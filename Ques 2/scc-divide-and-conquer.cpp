#include <bits/stdc++.h>
#include "Graph.h"
#include "ComponentsList.h"

using namespace std;

long long int findNextValid(vector <long long int> &valid) {    
    // initialize the root node to -1
    long long int root = -1;

    // find a node that is part of the subgraph
    for(long long int i = 0; i < valid.size(); i++) {
        if(valid[i]) {
            root = i;
            break;
        }
    }

    return root;
}

void seperateComponent(vector <long long int> &pred, vector <long long int> &desc, vector <long long int> &valid,
  ComponentsList &cl) {
    // initialize new component
    vector <long long int> component;
    // find nodes that are both, predecessors as well as descendants
    // and add them to the new connected component.
    // mark them invalid, so that these nodes are not further used in the graph.

    for(long long int i = 0; i < valid.size(); i++) {
        if(pred[i] and desc[i]) {
            component.push_back(i);
            valid[i] = 0;
        }
    }
    cl.addComponent(component);
}

void divideGraph(vector <long long int> &valid_pred, vector <long long int> &valid_desc, vector <long long int> valid_rem,
  vector <long long int> &pred, vector <long long int> &desc) {
    for(long long int i = 0; i < valid_pred.size(); i++) {
        valid_pred[i] *= pred[i];
        valid_desc[i] *= desc[i];
        valid_rem[i] *= (1-pred[i])*(1-desc[i]);
    }
}

/* 
    A (recursive) function to find the strongly connected component
    for the first valid vertex of the given graph, and add it to the list of connected components.
    Return value: void
    Parameters:
    1. reference to an object of the Graph class, on which the traversal needs to be done.
    2. reference to a vector that marks if a given node belongs to the current subgraph.
    3. reference to a vector of vectors of long long int data type, where each row stores a
    strongly connected component of the given graph.
*/
void sccDivideAndConquer(Graph &graph, vector <long long int> &valid, ComponentsList &cl) {
    long long int root = findNextValid(valid);
    if(root == -1) { // no valid node is left, i.e. all nodes have already been considered in some SCC.
        return;
    }

    // get predecessors and descendants for the root.
    vector <long long int> pred(graph.no_vertex), desc(graph.no_vertex);
    graph.findPredecessors(root, valid, pred);
    graph.findDescendants(root, valid, desc);

    seperateComponent(pred, desc, valid, cl);

    // seperate list of valid nodes, each corresponding to the set:
    // predecessors, descendants and remainder
    vector <long long int> valid_pred(valid), valid_desc(valid), valid_rem(valid);
    divideGraph(valid_pred, valid_desc, valid_rem, pred, desc);

    // recursively call the function for the 3 subgraphs 
    sccDivideAndConquer(graph, valid_pred, cl);
    sccDivideAndConquer(graph, valid_desc, cl);
    sccDivideAndConquer(graph, valid_rem, cl);
}

/*
    Function to return the strongly connected components in the given graph.
    Return value: reference to a vector of vectors of long long int data type,
    where each row stores a strongly connected component of the given graph.
    Parameters: 1. reference to an object of the Graph class, whose SCCs are to be found.
*/
void getConnectedComponents(Graph &graph, ComponentsList &cl) {
    vector <long long int> valid(graph.no_vertex, 1);
    sccDivideAndConquer(graph, valid, cl);
}

int main() {
    Graph graph;
    ComponentsList cl(graph.no_vertex);
    getConnectedComponents(graph, cl);
    cl.printComponents();

    return 0;
}
