#include <bits/stdc++.h>
using namespace std;

class ComponentsList{
public:
    vector <vector <int> > list;
    int length, max_length;

    ComponentsList(int max_l) {
        max_length = max_l;
        length = 0;
        list.resize(max_length);
    }

    void addComponent(vector <int> &);
    void printComponents();
    int maxComponentSize();    
};

void ComponentsList::addComponent(vector <int> &component) {
    for(int i = 0; i < component.size(); i++) {
        list[length].push_back(component[i]);
    }    

    length++;
}

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

int ComponentsList::maxComponentSize() {
    int max_component = 0;
    for(int i = 0; i < length; i++) {
        max_component = max(max_component, (int)list[i].size());
    }
    return max_component;
}
