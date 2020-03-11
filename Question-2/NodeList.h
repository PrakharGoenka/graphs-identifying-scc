#include <bits/stdc++.h>
using namespace std;

#define N 100000

class NodeList {
public:
	bitset <N> subgraph;

	void add(int node) {
		subgraph.set(node);
	} 

	bool contains(int node) {
		return subgraph.test(node);
	}

	void remove(int node) {
		subgraph.reset(node);
	}

	int findNode() {    
	    if(subgraph.none()) {
	    	return -1;
	    }
	    return subgraph._Find_first();
	}

	static void intersection(NodeList &first, NodeList &second, NodeList &result) {
		result.subgraph = first.subgraph & second.subgraph;
	}

	static void subtract(NodeList &first, NodeList &second, NodeList &result) {
		result.subgraph = first.subgraph ^ second.subgraph;
	}

	static void combine(NodeList &first, NodeList &second, NodeList &result) {
		result.subgraph = first.subgraph | second.subgraph;
	}
};
