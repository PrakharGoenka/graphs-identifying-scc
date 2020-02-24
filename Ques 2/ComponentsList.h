#include <bits/stdc++.h>
using namespace std;

class ComponentsList{
public:
    vector <vector <long long int> > list;
    long long int length;

    ComponentsList(long long int max_length) {
        length = 0;
        list.resize(max_length);
    }

    void addComponent(vector <long long int> &);
    void printComponents();
    long long int maxComponentSize();    
};

void ComponentsList :: addComponent(vector <long long int> &component) {
    for(long long int i = 0; i < component.size(); i++) {
        list[length].push_back(component[i]);
    }

    length++;
}

void ComponentsList :: printComponents() {
    cout << "Total number of components are: "  << length << endl;    

    for(long long int i = 0; i < length; i++) {
        cout << "Component Number " << i+1 << endl;
        for(long long int j = 0; j < list[i].size(); j++) {
            cout << list[i][j] << " ";
        }
        cout << endl;
    }
}

long long int ComponentsList :: maxComponentSize() {
    long long int max_component = 0;
    for(long long int i = 0; i < length; i++) {
        max_component = max(max_component, (long long int)list[i].size());
    }
    return max_component;
}
