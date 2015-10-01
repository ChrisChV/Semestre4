#ifndef MONTICULO_H
#define MONTICULO_H
#include "vector"
#include "algorithm"

using namespace std;

int _izquierda(int);
int _derecha(int);
template <typename T>
void minheapFy(vector<T> &, int);
template <typename T>
void maxheapFy(vector <T> &, int);
template <typename T>
bool esHoja(vector<T> &, int);
template <typename T>
void makeMinHeap(vector<T> &);
template <typename T>
void makeMaxHeap(vector<T> &);
template <typename T>
void heapSort(vector<T> &);

template <typename T>
void heapSort(vector<T> &vec){
    makeMaxHeap(vec);
    auto b = vec.size();
    auto s = vec.size() - 1;
    for(int i = 0; i < b; i++){
        swap(vec[0], s);
        s--;
        maxheapFy(vec,0);
    }
}

template <typename T>
void makeMaxHeap(vector<T> &vec){
    for(int i = vec.size() / 2; i >= 0; i--){
        maxheapFy(vec, i);
    }
}

template <typename T>
void makeMinHeap(vector<T> &vec){
    for(int i = vec.size() / 2; i >= 0; i--){
        minheapFy(vec,i);
    }
}


template <typename T>
bool esHoja(vector <T> &vec, int index){
    auto b = vec.size() - 1;
    if(vec[_derecha(index)] > b and vec[_izquierda(index)] > b)return true;
    return false;
}

int _derecha(int index){
    return 2 * index + 2;
}

int _izquierda(int index){
    return 2 * index + 1;
}

template <typename T>
void minheapFy(vector<T> &vec, int index){
    if(esHoja(vec,index))return;
    int menor = index;
    if(vec[_izquierda(index)] > vec[menor])menor = _izquierda(index);
    if(vec[_derecha(index)] > vec[menor])menor = _derecha(index);
    if(menor == index)return;
    swap(vec[index], vec[menor]);
    minheapFy(vec, menor);

}

template <typename T>
void maxheapFy(vector<T> &vec, int index){
    if(esHoja(vec,index))return;
    int menor = index;
    if(vec[_izquierda(index)] < vec[menor])menor = _izquierda(index);
    if(vec[_derecha(index)] < vec[menor])menor = _derecha(index);
    if(menor == index)return;
    swap(vec[index], vec[menor]);
    maxheapFy(vec, menor);
}



#endif // MONTICULO_H
