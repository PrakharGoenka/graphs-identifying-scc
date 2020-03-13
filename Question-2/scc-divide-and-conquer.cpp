#include <bits/stdc++.h>
#include "Graph.h"
#include "ComponentsList.h"

using namespace std;


/*!
* Function to seperate out a new SCC from the subgraph.
* The function seperates the common nodes of pred and desc from subgraph
* and creates a new component of them, which is added to the list of
 connected components.
* \param pred - set of nodes that are predecessors
* \param desc - set of nodes that are descendants
* \param subgraph - set of nodes in the existing subgraph
* \param cl - list of the discovered connected components 
*/
void seperateComponent(NodeSet &pred, NodeSet &desc, NodeSet &subgraph,
  ComponentsList &cl) {
    vector <int> component; // initialize new component

    /* find nodes that are both, predecessors as well as descendants
     and add them to the new connected component.
     remove them from the existing subgraph. */    
    for(int i = 0; i < cl.max_length; i++) {
        if(pred.contains(i) and desc.contains(i)) {
            component.push_back(i);
            subgraph.remove(i);
        }
    }
    cl.addComponent(component);
}


/*! 
* Function to divide the existing subgraph into 3 parts.
* The subgraph is divided, along with edges, according to
* 1. nodes that are predecessors of the current node, but don't overlap
* 2. nodes that are descendants of the current node, but don't overlap
* 3. remaining nodes of the subgraph
* \param subgraph - reference to the nodeset of the existing subgraph
* \param sg_pred - ref to the new set of nodes that are predecessors
* \param sg_desc - ref to the new set of nodes that are descendants
* \param sg_rem - ref to the new set of the remaining nodes
* \param pred - ref to the nodeset of the predecessors of the current node
* \param desc - ref to the nodeset of the descendants of the current node
*/
void divideGraph(NodeSet &subgraph, NodeSet &sg_pred, NodeSet &sg_desc, NodeSet &sg_rem,
  NodeSet &pred, NodeSet &desc) {
    NodeSet::intersection(subgraph, pred, sg_pred);
    NodeSet::intersection(subgraph, desc, sg_desc);
    NodeSet::combine(sg_pred, sg_desc, sg_rem);
    NodeSet::subtract(subgraph, sg_rem, sg_rem);
}


/*!
* A (recursive) function to find the strongly connected component for the
 first valid vertex of the given graph, and add it to the list of 
 connected components.
* \param graph - reference to the graph whose components are to be found.
* \param subgraph - reference to the nodeset of nodes in the existing subgraph
* \param cl - reference to the ComponentList of the graph
*/
void sccDivideAndConquer(Graph &graph, NodeSet &subgraph, ComponentsList &cl) {
    int root = subgraph.findNode();
    if(root == -1) { // the subgraph does not contain any node
        return;
    }
    /* get predecessors and descendants for the root. */
    NodeSet pred, desc;
    graph.findPredecessors(root, subgraph, pred);
    graph.findDescendants(root, subgraph, desc);

    seperateComponent(pred, desc, subgraph, cl);
    /* seperate list of valid nodes, each corresponding to the set:
     predecessors, descendants and remainder */
    NodeSet sg_pred, sg_desc, sg_rem;
    divideGraph(subgraph, sg_pred, sg_desc, sg_rem, pred, desc);

    /* recursively call the function for the 3 subgraphs */
    sccDivideAndConquer(graph, sg_pred, cl);
    sccDivideAndConquer(graph, sg_desc, cl);
    sccDivideAndConquer(graph, sg_rem, cl);
}


/*!
* Function to return the strongly connected components in the given graph.
* \param graph - reference to the graph whose components are to be found.
* \param cl - reference to the ComponentList of the graph
*/
void getConnectedComponents(Graph &graph, ComponentsList &cl) {
    NodeSet original;
    
    for(int i = 0; i < graph.nodes; i++) {
        original.add(i);
    }
    sccDivideAndConquer(graph, original, cl);
}


/*!
* The main function.
* It receives user input for the graph's nodes and edges. It prints
* the strongly connected components the graph,
* the maximum nodes contained in a component.
*/
int main() {
    /* change input stream to file I/O */
    #ifndef ONLINE_JUDGE
        freopen("input.txt", "r", stdin);
    #endif

    int nodes; /*!< number of nodes in the graph*/
    int edges; /*!< number of edges in the graph*/
    cin >> nodes >> edges;

    Graph graph(nodes); // initialize graph with given number of nodes
    int u, v;
    for(int i = 0; i < edges; i++) { // add edges to the graph
        cin >> u >> v;
        graph.addEdge(u, v);
    }
    
    ComponentsList cl(graph.nodes); // initialize with number of nodes in the graph
    getConnectedComponents(graph, cl); // store connected components in cl
    cl.printComponents(); // print connected components of the graph
    cout << "Maximum number of nodes in a component ";
    cout << cl.maxComponentSize(); // print max size of a component

    return 0;
}
