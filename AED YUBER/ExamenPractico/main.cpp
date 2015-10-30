#include <iostream>
#include "list"
#include "map"
#include "algorithm"
#include "vector"


using namespace std;
typedef map<int, map<int,float>> Grafo;

bool esGrafo(Grafo, vector<int>&);
bool hayCamino(Grafo,int,int,vector<int>&);

void print(Grafo grafo){
    for(int i = 0; i < grafo.size(); i++){
        for(int j = 0; j < grafo.size(); j++){
            cout<<grafo[i][j]<<" ";
        }
        cout<<endl;
    }
}

bool ciclos(Grafo grafo){
    for(auto iter = grafo.begin(); iter != grafo.end(); ++iter){
        if(iter->second.find(iter->first) != iter->second.end()) return true;
    }
    return false;
}

bool conexoFuerte(Grafo grafo){
    vector<int> valores;
    if(!esGrafo(grafo,valores)) return false;
    for(int i = 0; i < valores.size(); i++){
        vector<int> valTemp = valores;
        int temp = valores[i];
        valTemp.erase(valTemp.begin() + i);
        for(int j = 0; j < valTemp.size(); j++){
            vector<int> visitado;
            if(!hayCamino(grafo,valores[i],valTemp[j],visitado))return false;
        }
    }
    return true;
}

bool esGrafo(Grafo grafo, vector<int> &valores){
    int siz = grafo.size();
    for(auto iter = grafo.begin(); iter != grafo.end(); ++iter){
        if(iter->second.size() > siz) return false;
        valores.push_back(iter->first);
    }
    for(auto iter = grafo.begin(); iter != grafo.end(); ++iter){
        for(auto iter2 = iter->second.begin(); iter2 != iter->second.end(); ++iter2){
            if(find(valores.begin(), valores.end(), iter2->first) == valores.end())return false;
        }
    }
    return true;
}

bool hayCamino(Grafo grafo, int a, int b, vector<int>& visitado){
    if(find(visitado.begin(), visitado.end(),a) != visitado.end())return false;
    visitado.push_back(a);
    if(grafo[a].find(b) != grafo[a].end())return true;
    for(auto iter = grafo[a].begin(); iter != grafo[a].end(); ++iter){
        if(hayCamino(grafo,iter->first,b,visitado)) return true;
    }
    return false;
}

int main()
{
    Grafo g;
    g[0][1] = 1;
    g[1][2] = 2;
    g[2][1] = 3;
    g[1][0] = 5;
    g[2][2] = 3;
    vector<int> v;
    cout<<ciclos(g)<<endl;



}
