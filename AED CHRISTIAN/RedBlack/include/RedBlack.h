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
        int find(T, Nodo **&, Nodo *&);
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
            archivo<<(*iter)->valor<<" [color="<<color<<"]"<<endl;
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
    Nodo *padre;
    auto flag = this->find(valor,nodo,padre);
    if(flag == 1)return;
    *nodo = new Nodo(valor);
    (*nodo)->padre = padre;
    if(flag == -1){
        root->color = NEGRO;
    }
    Nodo * iter = *nodo;
    while(iter->padre){
        if(iter->padre->color == NEGRO)break;
        if(iter == root)break;
        if(iter->padre->color == ROJO){
            if(!iter->padre->padre->hijos[iter->padre->valor < iter->padre->padre->valor] or iter->padre->padre->hijos[iter->padre->valor < iter->padre->padre->valor]->color == NEGRO){
                if(iter->valor > iter->padre->valor){
                    if(iter->padre->valor > iter->padre->padre->valor) rotacionSImple(iter->padre->padre, DERECHA);
                    else rotacionCompleja(iter->padre->padre, IZQUIERDA);
                    print();
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
int RedBlack<T>::find(T valor, Nodo **&nodo, Nodo *&iter){
    iter = nullptr;
    nodo = &(root);
    if(!root)return -1;
    while(*nodo){
        if((*nodo)->valor == valor)return 1;
        if(!iter) iter = root;
        else iter = *nodo;
        nodo = &((*nodo)->hijos[(*nodo)->valor < valor]);
    }
    return 0;
}

template <typename T>
void RedBlack<T>::rotacionCompleja(Nodo *&padre, bool flag){
    Nodo * hijo = padre->hijos[flag];
    Nodo * nieto = hijo->hijos[!flag];
    Nodo * abuelo = padre->padre;
    nieto->color = NEGRO;
    padre->color = ROJO;
    padre->hijos[flag] = nieto->hijos[!flag];
    if(nieto->hijos[!flag])
        nieto->hijos[!flag]->padre = padre;
    hijo->hijos[!flag] = nieto->hijos[flag];
    if(nieto->hijos[flag])
        nieto->hijos[flag]->padre = hijo;
    nieto->hijos[!flag] = padre;
    padre->padre = nieto;
    nieto->hijos[flag] = hijo;
    hijo->padre = nieto;
    if(padre == root){
        root = nieto;
    }
    else{
        abuelo->hijos[abuelo->valor < padre->valor] = nieto;
        nieto->padre = abuelo;
    }
}

template <typename T>
void RedBlack<T>::rotacionSImple(Nodo *& padre, bool flag){
    Nodo * hijo = padre->hijos[flag];
    Nodo * abuelo = padre->padre;
    padre->hijos[flag] = hijo->hijos[!flag];
    if(padre->hijos[flag]){
        padre->hijos[flag]->padre = padre;
    }
    hijo->hijos[!flag] = padre;
    padre->padre = hijo;
    padre->color = ROJO;
    hijo->color = NEGRO;
    print();
    if(padre == root){
        root = hijo;
    }
    else{
        abuelo->hijos[abuelo->valor < padre->valor] = hijo;
        hijo->padre = abuelo;
    }
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
