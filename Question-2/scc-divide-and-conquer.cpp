#include <bits/stdc++.h>
#include "Graph.h"
#include "ComponentsList.h"

using namespace std;

void seperateComponent(NodeList &pred, NodeList &desc, NodeList &subgraph,
  ComponentsList &cl) {
    // initialize new component
    vector <int> component;
    // find nodes that are both, predecessors as well as descendants
    // and add them to the new connected component.
    // mark them invalid, so that these nodes are not further used in the graph.
     
    for(int i = 0; i < cl.max_length; i++) {
        if(pred.contains(i) and desc.contains(i)) {
            component.push_back(i);
            subgraph.remove(i);
        }
    }
    cl.addComponent(component);
}

void divideGraph(NodeList &subgraph, NodeList &sg_pred, NodeList &sg_desc, NodeList &sg_rem,
  NodeList &pred, NodeList &desc) {
    NodeList::intersection(subgraph, pred, sg_pred);
    NodeList::intersection(subgraph, desc, sg_desc);
    NodeList::combine(sg_pred, sg_desc, sg_rem);
    NodeList::subtract(subgraph, sg_rem, sg_rem);
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
void sccDivideAndConquer(Graph &graph, NodeList &subgraph, ComponentsList &cl) {
    int root = subgraph.findNode();
    if(root == -1) { // the subgraph does not contain any node
        return;
    }
    // get predecessors and descendants for the root.
    NodeList pred, desc;
    graph.findPredecessors(root, subgraph, pred);
    graph.findDescendants(root, subgraph, desc);

    seperateComponent(pred, desc, subgraph, cl);
    // seperate list of valid nodes, each corresponding to the set:
    // predecessors, descendants and remainder
    NodeList sg_pred, sg_desc, sg_rem;
    divideGraph(subgraph, sg_pred, sg_desc, sg_rem, pred, desc);

    // recursively call the function for the 3 subgraphs 
    sccDivideAndConquer(graph, sg_pred, cl);
    sccDivideAndConquer(graph, sg_desc, cl);
    sccDivideAndConquer(graph, sg_rem, cl);
}

/*
    Function to return the strongly connected components in the given graph.
    Return value: reference to a vector of vectors of int data type,
    where each row stores a strongly connected component of the given graph.
    Parameters: 1. reference to an object of the Graph class, whose SCCs are to be found.
*/
void getConnectedComponents(Graph &graph, ComponentsList &cl) {
    NodeList original;
    
    for(int i = 0; i < graph.nodes; i++) {
        original.add(i);
    }
    sccDivideAndConquer(graph, original, cl);
}

int main() {

    #ifndef ONLINE_JUDGE
        freopen("input.txt", "r", stdin);
    #endif // ONLINE_JUDGE


    int nodes, edges;
    cin >> nodes >> edges;

    Graph graph(nodes);
    int u, v;
    for(int i = 0; i < edges; i++) {
        cin >> u >> v;
        graph.addEdge(u, v);
    }
    
    ComponentsList cl(graph.nodes);
    getConnectedComponents(graph, cl);
    cl.printComponents();
    cout << "Maximum number of nodes in a component " << cl.maxComponentSize() << endl ;

    return 0;
}
