#include <iostream>
#include "Grafo.h"
#include "list"

using namespace std;

void print(Grafo grafo){
    for(int i = 0; i < grafo.size(); i++){
        for(int j = 0; j < grafo.size(); j++){
            cout<<grafo[i][j]<<" ";
        }
        cout<<endl;
    }
}

bool ciclos(Grafo grafo, int index){
    if(index >= grafo.size()) return false;

}

bool conexo(Grafo grafo){
    for(int i = 0; i < grafo.size(); i++){
        for(int j = i + 1; j < grafo.size(); j++){
            if(grafo[i][j] == 0 and grafo[j][i] == 0){
                return false;
            }
        }
    }
    return true;
}



int main()
{
    vector<vector<int>> m;
    vector<int> temp;
    temp.push_back(0);
    temp.push_back(1);
    temp.push_back(0);
    m.push_back(temp);
    temp.clear();
    temp.push_back(0);
    temp.push_back(0);
    temp.push_back(1);
    m.push_back(temp);
    temp.clear();
    temp.push_back(1);
    temp.push_back(0);
    temp.push_back(0);
    m.push_back(temp);
    Grafo grafo(m);
    print(grafo);
    cout<<conexo(grafo)<<endl;
}
