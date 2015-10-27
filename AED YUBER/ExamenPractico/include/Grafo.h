#ifndef GRAFO_H
#define GRAFO_H
#include "vector"

using namespace std;

class Grafo
{
    public:
        Grafo();
        Grafo(vector<vector<int>>);
        int size();
        vector<int> operator [] (int);
        virtual ~Grafo();
    protected:
    private:
        vector<vector<int>> matriz;
        int siz;
};

int Grafo::size(){
    return this->siz;
}

vector<int> Grafo::operator[] (int index){
    return matriz[index];
}

Grafo::Grafo(vector<vector<int>> m){
    matriz = m;
    siz = matriz.size();
}

Grafo::Grafo(){

}

Grafo::~Grafo(){

}

#endif // GRAFO_H
