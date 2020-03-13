#include <bits/stdc++.h>
using namespace std;

#define N 100000	//set max number of nodes


/*!
* Abstracts a set of nodes.
* A class to maintain a set of nodes of a graph.
* It provides methods to
* modify the set,
* find a node in the set,
* perform set operations.
* Uses bitset to implement an ordered set of nodes. 
*/
class NodeSet {
public:
	bitset <N> nodes;

	/*!
	* Method to add a node to the set.
	* \param node - the node to be added to the set
	*/
	void add(int node) {
		nodes.set(node);
	} 


	/*!
	* Method to remove a node from the set.
	* \param node - the node to be removed from the set
	*/
	void remove(int node) {
		nodes.reset(node);
	}


	/*!
	* Method to check if a node is present in the set.
	* \param node - the node whose presence has to be checked
	*/
	bool contains(int node) {
		return nodes.test(node);
	}


	/*!
	* Method to find the first node in the set.
	* Returns number of the first node if exists.
	* Returns -1 otherwise. 
	*/
	int findNode() {    
	    if(nodes.none()) {
	    	return -1;
	    }
	    return nodes._Find_first();
	}


	/*!
	* Static method to get intersection of two nodesets.
	* \param first - the first nodeset
	* \param second - the second nodeset
	* \param result - the nodeset to store the intersection
	*/
	static void intersection(NodeSet &first, NodeSet &second, NodeSet &result) {
		result.nodes = first.nodes & second.nodes;
	}


	/*!
	* Static method to get subtract one nodeset from other.
	* \param first - the first nodeset
	* \param second - the second nodeset
	* \param result - the nodeset to store (first ~ second)
	*/
	static void subtract(NodeSet &first, NodeSet &second, NodeSet &result) {
		result.nodes = first.nodes ^ second.nodes;
	}


	/*!
	* Static method to get union of two nodesets.
	* \param first - the first nodeset
	* \param second - the second nodeset
	* \param result - the nodeset to store the union
	*/
	static void combine(NodeSet &first, NodeSet &second, NodeSet &result) {
		result.nodes = first.nodes | second.nodes;
	}
};
