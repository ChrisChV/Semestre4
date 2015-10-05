#ifndef BINOMIALHEAP_H
#define BINOMIALHEAP_H
#include "fstream"
#include "iostream"

using namespace std;

template <typename T>
class BinomialHeap
{
    public:
        class Nodo{
            public:
                Nodo();
                Nodo(T);
                T valor;
                Nodo * padre;
                Nodo * hijo;
                Nodo * hermano;
                void destruirme();
                int _grado();
        };
        class Root{
            public:
                Root();
                Root(Nodo *);
                Nodo * contenido;
                Nodo * siguiente;
                int grado();
                void destruirme();s
        };
        BinomialHeap();
        BinomialHeap(bool);
        Root *getInicio();
        void print(string);
        void uni(Root *&);
        virtual ~BinomialHeap();
    protected:
    private:
        Root * inicio;
        bool animation;
        void _merge(Root *&);
        void _print()
};

void BinomialHeap::print(string mensaje){
    ofstream archivo("BH.dot");
    if(archivo.fail()){
        cout<<"ERROR->EL archivo no se pudo abrir"<<endl;
        return;
    }
    cout<<mensaje<<endl;
    archivo<<"digrapth{"<<endl;
    Root * iter = inicio;
}

void BinomialHeap::_merge(Root *&secondInicio){
    Root ** firstIter = this->inicio;
    Root ** secondIter = secondInicio;
    while(*secondIter){
        if(*firstIter == nullptr){
            *firstIter = *secondIter;
            (*firstIter)->siguiente = nullptr;
            firstIter = &((*firstIter)->siguiente);
            secondIter = &((*secondIter)->seguiente);
        }
        else if(*firstIter->grado() == *secondIter->grado()){
            auto temp = (*firstIter)->siguiente;
            (*firstIter)->siguiente = *secondIter;
            (*secondIter)->siguiente = temp;
            firstIter = &((*firstIter)->siguiente);
            secondIter = &((*secondIter)->siguiente);
        }
        else if(*firstIter->grado() > *secondIter->grado()){
            auto temp = (*firstIter);
            *firstIter = *secondIter;
            (*firstIter)->siguiente = temp->siguiente;
            firstIter = &((*firstIter)->siguiente->siguiente);
            secondIter = &((*secondIter)->siguiente);
        }
    }
}

void BinomialHeap::uni(Root *&secondInicio){
    if(!secondInicio())return;
    _merge(secondInicio);
}

int BinomialHeap::Nodo::_grado(){
    if(this->hijo)return this->hijo->_grado() + 1;
    return 0;
}

int BinomialHeap::Root::grado(){
    if(this->contenido->hijo)return this->contenido->hijo->_grado() + 1;
    return 0;
}

void BinomialHeap::Root::destruirme(){
    if(this->contenido->hijo)this->contenido->hijo->destruirme();
    if(this->siguiente)this->siguiente->destruirme();
    delete this;
}

void BinomialHeap::Nodo::destruirme(){
    if(this->hermano)this->hermano.destruirme();
    if(this->hijo)this->hijo.destruirme();
    delete this;
}

BinomialHeap::Root * BinomialHeap::getInicio(){return this->inicio;}

BinomialHeap::Root::Root(Nodo *contenido){
    this->contenido = contenido;
    siguiente = nullptr;
}

BinomialHeap::Root::Root(){
    contenido = nullptr;
    siguiente = nullptr;
}

BinomialHeap::Nodo::Nodo(T valor){
    this->valor = valor;
    padre = nullptr;
    hijo = nullptr;
    hermano = nullptr;
}

BinomialHeap::Nodo::Nodo(){
    padre = nullptr;
    hijo = nullptr;
    hermano = nullptr;
}

BinomialHeap::BinomialHeap(bool animation){
    this->animation = animation;
    inicio = nullptr;
}

BinomialHeap::BinomialHeap(){
    inicio = nullptr;
    animation = false;
}

BinomialHeap::~BinomialHeap(){
    inicio->destruirme();
}
#endif // BINOMIALHEAP_H
