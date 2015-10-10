#ifndef REDBLACK_H
#define REDBLACK_H
#include "iostream"
#include "fstream"
#include "list"

using namespace std;

enum Colores{NEGRO, ROJO};
enum Rotaciones{IZQUIERDA, DERECHA};
template <typename T>
class RedBlack
{
    public:
        class Nodo{
            public:
                Nodo();
                Nodo(T);
                T valor;
                bool color;
                Nodo * hijos[2];
                Nodo * padre;
                void destruirme();
        };
        RedBlack();
        void rotacionSImple(Nodo *&, bool);
        void print();
        void insert(T);
        void rotacionCompleja(Nodo *&, bool);
        virtual ~RedBlack();
    protected:
    private:
        Nodo * root;
        int find(T, Nodo **&);
        bool tipoHijo(Nodo *);
};

template <typename T>
void RedBlack<T>::print(){
    ofstream archivo("eje.dot");
    if(archivo.fail()){
        cout<<"No se puede abrir el archivo"<<endl;
        return;
    }
    archivo<<"digraph{"<<endl;
    list<Nodo *> result;
    if(root)result.push_back(root);
    while(!result.empty()){
        list<Nodo *> temp;
        for(auto iter = result.begin(); iter != result.end(); ++iter){
            string color;
            if((*iter)->color) color = "red";
            else color = "black";
            archivo<<(*iter)->valor<<" [fillcolor='"<<color<<"']"<<endl;
            if((*iter)->hijos[0]){
                archivo<<(*iter)->valor<<"->"<<(*iter)->hijos[0]->valor<<endl;
                temp.push_back((*iter)->hijos[0]);
            }
            if((*iter)->hijos[1]){
                archivo<<(*iter)->valor<<"->"<<(*iter)->hijos[1]->valor<<endl;
                temp.push_back((*iter)->hijos[1]);
            }
        }
        result = temp;
    }
    archivo<<"}";
    archivo.close();
    system("dot -Tpdf eje.dot -o eje.pdf");
}

template <typename T>
void RedBlack<T>::insert(T valor){
    Nodo ** nodo;
    auto flag = this->find(valor,nodo);
    if(flag == 1)return;
    *nodo = new Nodo(valor);
    if(flag == -1){
        root->color = NEGRO;
    }
    Nodo * iter = *nodo;
    while(iter->padre){
        if(iter->padre->color == NEGRO)break;
        if(iter->padre->color == ROJO){
            if(iter->padre->padre->hijos[iter->padre->valor < iter->padre->padre->valor]->color == NEGRO){
                if(iter->valor > iter->padre->valor){
                    if(iter->padre->valor > iter->padre->padre->valor) rotacionSImple(iter->padre->padre, DERECHA);
                    else rotacionCompleja(iter->padre->padre, IZQUIERDA);
                }
                else{
                    if(iter->padre->valor > iter->padre->padre->valor) rotacionCompleja(iter->padre->padre, DERECHA);
                    else rotacionSImple(iter->padre->padre, IZQUIERDA);
                }
                break;
            }
            else{
                iter->padre->padre->color = ROJO;
                iter->padre->padre->hijos[0]->color = NEGRO;
                iter->padre->padre->hijos[1]->color = NEGRO;
                iter = iter->padre->padre;
            }
        }
    }
    if(root->color == ROJO) root->color = NEGRO;
}

template <typename T>
int RedBlack<T>::find(T valor, Nodo **&nodo){
    nodo = &(root);
    if(!root)return -1;
    while(*nodo){
        if((*nodo)->valor == valor)return 1;
        nodo = &((*nodo)->hijos[(*nodo)->valor < valor]);
    }
    return 0;
}

template <typename T>
void RedBlack<T>::rotacionCompleja(Nodo *&padre, bool flag){
    Nodo * hijo = padre->hijos[flag];
    Nodo * nieto = hijo->hijos[!flag];
    padre->hijos[flag] = nieto->hijos[!flag];
    hijo->hijos[!flag] = nieto->hijos[flag];
    nieto->hijos[!flag] = padre;
    nieto->hijos[flag] = hijo;
    nieto->color = NEGRO;
    padre->color = ROJO;
    padre = nieto;
}

template <typename T>
void RedBlack<T>::rotacionSImple(Nodo *& padre, bool flag){
    Nodo * hijo = padre->hijos[flag];
    padre->hijos[flag] = hijo->hijos[!flag];
    hijo->hijos[!flag] = padre;
    padre->color = ROJO;
    hijo->color = NEGRO;
    padre = hijo;
}

template <typename T>
RedBlack<T>::Nodo::Nodo(){
    hijos[0] = nullptr;
    hijos[1] = nullptr;
    padre = nullptr;
    color = ROJO;
}

template <typename T>
RedBlack<T>::Nodo::Nodo(T valor){
    this->valor = valor;
    hijos[0] = nullptr;
    hijos[1] = nullptr;
    padre = nullptr;
    color = ROJO;
}

template <typename T>
void RedBlack<T>::Nodo::destruirme(){
    if(this->hijos[0])this->hijos[0]->destruirme();
    if(this->hijos[1])this->hijos[1]->destruirme();
    delete this;
}

template <typename T>
RedBlack<T>::RedBlack(){
    root = nullptr;
}

template <typename T>
RedBlack<T>::~RedBlack(){
    root->destruirme();
}


#endif // REDBLACK_H
