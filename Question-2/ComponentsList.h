#include <bits/stdc++.h>
using namespace std;


/*!
* Abstracts a list of the strongly connected components of the graph.
* An instance of this class represents the SCCs of the graph as a list
* of nodes that each component contains.
* Has methods to edit and print the list, and to tell max sized SCC.
*/
class ComponentsList{
public:
    vector <vector <int> > list;
    int length; /*!< current length of the list */
    int max_length; /*!< maximum possible length of the list */

    /*!
    * Constructor.
    * \param max_l - maximum number of components possible
      (total number of nodes)
    */
    ComponentsList(int max_l) {
        max_length = max_l;
        length = 0;
        list.resize(max_length); // initialize 
    }

    void addComponent(vector <int> &);
    void printComponents();
    int maxComponentSize();    
};


/*!
* Method to add a new component to the list.
* \param component - a vector of nodes that the new component contains.
*/
void ComponentsList::addComponent(vector <int> &component) {
    for(int i = 0; i < component.size(); i++) {
        list[length].push_back(component[i]);
    }    

    length++;
}


/*!
* Method to print all the strongly connected components of the graph.
* On the first line, it prints the total number of components.
* 2 * length lines follow, two for each component. On the first
 it prints the component number.
* And on the second it prints the nodes of the component.
*/
void ComponentsList::printComponents() {
    cout << "Total number of components are: "  << length << endl;    

    for(int i = 0; i < length; i++) {
        cout << "Component Number " << i+1 << endl;
        for(int j = 0; j < list[i].size(); j++) {
            cout << list[i][j] << " ";
        }
        cout << endl;
    }
}


/*!
* Method to find the size of the component with most nodes.
*/
int ComponentsList::maxComponentSize() {
    int max_component = 0;
    for(int i = 0; i < length; i++) {
        max_component = max(max_component, (int)list[i].size());
    }
    return max_component;
}
