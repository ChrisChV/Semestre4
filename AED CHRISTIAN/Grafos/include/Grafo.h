
#ifndef GRAFO_H
#define GRAFO_H
#include "map"
#include "list"
#include "fstream"
#include "iostream"
#include "FibonacciHeap.h"

#define INFINITO 1000;

using namespace std;

////////////PROBAR = STRING

class Grafo
{
    public:
        class Relacion{
            public:
                Relacion();
                Relacion(string,string,float);
                string nodos[2];
                string _getDestino(string);
                float peso;
        };
        class Nodo{
            public:
                Nodo();
                Nodo(string);
                list<Relacion *> relaciones;
                bool _existeRelacion(Nodo *,Relacion *&);
                string nombre;
                bool marcado;
        };
        class PesoDTO{
            public:
                PesoDTO(){nodos[0] = nullptr; nodos[1] = nullptr;peso = INFINITO;}
                PesoDTO(float p, Nodo * nodo1, Nodo * nodo2){nodos[0] = nodo1; nodos[1] = nodo2; peso = p;}
                float peso;
                Nodo * nodos[2];
                bool operator<(PesoDTO second){
                    if(peso < second.peso) return true;
                    return false;
                }
                bool operator>(PesoDTO second){
                    if(peso > second.peso) return true;
                    return false;
                }
                bool operator==(PesoDTO second){
                    if(peso == second.peso and nodos[0] == second.nodos[0] and nodos[1] == second.nodos[1])return true;
                    return false;
                }
        };
        Grafo();
        void print();
        void warshall();
        list<float> dijkstra(string i);
        void floid();
        list<Relacion *>& operator[](string);
        bool operator()(string,string,float);
        virtual ~Grafo();
    protected:
    private:
        bool _existeRelacion(Nodo *, Nodo *);
        bool _existeRelacion(Nodo * nodo1, Nodo * nodo2, Relacion *& rel);
        bool _existeNodo(string,Nodo*&);
        bool _crearRelacion(string,string,float);
        void _desmarcar();
        float _getPeso(Nodo * nodo1, Nodo * nodo2);
        float _getPeso(Nodo * nodo1, Nodo * nodo2,Relacion *&);
        bool _llenarHeap(FibonacciHeap<PesoDTO> &, string);
        PesoDTO _getMin(FibonacciHeap<PesoDTO>);
        list<float> _generarLista(FibonacciHeap<PesoDTO>&);
        map<string, Nodo *> grafo;
        list<Relacion *> relaciones;

};

Grafo::PesoDTO Grafo::_getMin(FibonacciHeap<PesoDTO> heap){
    while(!heap.empty()){
        PesoDTO pdto = heap.popMin();
        if(!pdto.nodos[1]->marcado)return pdto;
    }
    return PesoDTO();
}


bool Grafo::_llenarHeap(FibonacciHeap<PesoDTO> &heap, string i){
    Nodo * nodo;
    if(!_existeNodo(i,nodo))return false;
    for(auto iter = grafo.begin(); iter!= grafo.end(); ++iter){
        PesoDTO nuevo(_getPeso(nodo,iter->second),nodo,iter->second);
        cout<<"AAAA->"<<nuevo.peso<<endl;
        heap.insert(nuevo);
    }
    return true;
}

void Grafo::_desmarcar(){
    for(auto iter = grafo.begin(); iter != grafo.end(); ++iter){
        iter->second->marcado = false;
    }
}

list<float> Grafo::_generarLista(FibonacciHeap<PesoDTO> &pesos){
    list<float> resultado;
    for(auto iter = pesos.getRoots().begin(); iter != pesos.getRoots().end(); ++iter){
        resultado.push_back((*iter)->valor.peso);
    }
    return resultado;
}

list<float> Grafo::dijkstra(string i){
    FibonacciHeap<PesoDTO> heap;
    if(!_llenarHeap(heap,i)) return list<float>();
    grafo[i]->marcado = true;
    int contadorDeCeros = grafo.size() - 1;
    cout<<"A"<<endl;
    while(contadorDeCeros > 0){
        PesoDTO pdto =  _getMin(heap);
        int p = pdto.peso;
        pdto.nodos[1]->marcado = true;
        contadorDeCeros--;
        for(auto iter = heap.getRoots().begin(); iter != heap.getRoots().end(); ++iter){
            cout<<"B"<<endl;
            cout<<heap.size()<<endl;
            cout<<(*iter)->valor.peso<<endl;
            if(!(*iter)->valor.nodos[1]->marcado){
                cout<<"C"<<endl;
                (*iter)->valor.peso = min((*iter)->valor.peso, p + _getPeso(pdto.nodos[1],(*iter)->valor.nodos[1]));
            }
        }
    }
    _desmarcar();
    return _generarLista(heap);
}

float Grafo::_getPeso(Nodo * nodo1, Nodo * nodo2,Relacion *&r){
    if(!nodo1 or !nodo2)return INFINITO;
    if(_existeRelacion(nodo1,nodo2,r)){
        return r->peso;
    }
    if(_existeRelacion(nodo2,nodo1,r)){
        return r->peso;
    }
    return INFINITO;
}

float Grafo::_getPeso(Nodo * nodo1, Nodo * nodo2){
    Relacion * r;
    return _getPeso(nodo1,nodo2,r);
}



void Grafo::floid(){
    for(auto i = grafo.begin(); i != grafo.end(); ++i){
        for(auto j = grafo.begin(); j != grafo.end(); ++j){
            for(auto k = grafo.begin(); k != grafo.end(); ++k){
                float a = _getPeso(i->second,k->second);
                float b = _getPeso(k->second,j->second);
                if(_getPeso(i->second,j->second) >  + a + b){
                    _crearRelacion(i->first,j->first, a + b);
                }
            }
        }
    }
}

bool Grafo::_existeRelacion(Nodo * nodo1, Nodo * nodo2){
    Relacion *rel;
    if(nodo1->_existeRelacion(nodo2,rel))return true;
    if(nodo2->_existeRelacion(nodo1,rel))return true;
    rel = nullptr;
    return false;
}

bool Grafo::_existeRelacion(Nodo * nodo1, Nodo * nodo2, Relacion *& rel){
    if(nodo1->_existeRelacion(nodo2,rel))return true;
    if(nodo2->_existeRelacion(nodo1,rel))return true;
    rel = nullptr;
    return false;
}

void Grafo::warshall(){
    for(auto i = grafo.begin(); i != grafo.end(); ++i){
        for(auto j = grafo.begin(); j != grafo.end(); ++j){
            for(auto k = grafo.begin(); k != grafo.end(); ++k){
                if(_existeRelacion(i->second,j->second) or (_existeRelacion(i->second,k->second) and _existeRelacion(k->second,j->second))){
                    _crearRelacion(i->first,j->first,1);
                }
            }
        }
    }
}

void Grafo::print(){
    ofstream archivo("grafo.dot");
    if(archivo.fail()){
        cout<<"El archivo no se pudo abrir"<<endl;
        return;
    }
    archivo<<"graph{"<<endl;
    for(auto rel : relaciones){
        Nodo * nodo1;
        Nodo * nodo2;
        _existeNodo(rel->nodos[0],nodo1) and _existeNodo(rel->nodos[1],nodo2);
        archivo<<nodo1->nombre<<" -- "<<nodo2->nombre<<"[label =\""<<rel->peso<<"\"];";
    }
    archivo<<"}";
    archivo.close();
    system("dot -Tpdf grafo.dot -o grafo.pdf");
}

bool Grafo::_crearRelacion(string nodo1, string nodo2, float peso){
    Nodo * n1;
    Nodo * n2;
    if(!_existeNodo(nodo1,n1) or !_existeNodo(nodo2,n2)){
        return false;
    }
    else{
        Relacion * r;
        Relacion * t;
        if(!n1->_existeRelacion(n2,r) and !n2->_existeRelacion(n2,t)){
            Relacion * rel = new Relacion(n1->nombre,n2->nombre,peso);
            relaciones.push_back(rel);
            n1->relaciones.push_back(rel);
            n2->relaciones.push_back(rel);
            return true;
        }
        if(r){
            r->peso = peso;
            return true;
        }
        if(t){
            t->peso = peso;
            return true;
        }
    }
}

bool Grafo::operator()(string nodo1, string nodo2, float peso){
    return _crearRelacion(nodo1, nodo2, peso);
}

string Grafo::Relacion::_getDestino(string name){
    ///////////PROBAR ACA
    return nodos[nodos[0] == name];
}

list<Grafo::Relacion *>& Grafo::operator[](string name){
    Nodo * nodo;
    if(!_existeNodo(name,nodo)){
        nodo = new Nodo(name);
        grafo[name] = nodo;
    }
    return grafo[name]->relaciones;
}

bool Grafo::Nodo::_existeRelacion(Nodo * nodo, Relacion *&rel){
    for(auto iter_rel : relaciones){
        rel = iter_rel;
        if(rel->_getDestino(nombre) == nodo->nombre)return true;
    }
    rel = nullptr;
    return false;
}

bool Grafo::_existeNodo(string name, Nodo *&nodo){
   auto iter = grafo.find(name);
   if(iter != grafo.end()){
       nodo = iter->second;
       return true;
   }
   return false;
}

Grafo::Nodo::Nodo(){
    nombre = nullptr;
    marcado = true;
}

Grafo::Nodo::Nodo(string name){
    nombre = name;
    marcado = false;
}

Grafo::Relacion::Relacion(string nodo1, string nodo2, float peso){
    nodos[0] = nodo1;
    nodos[1] = nodo2;
    this->peso = peso;
}

Grafo::Relacion::Relacion(){
    nodos[0] = nullptr;
    nodos[1] = nullptr;
    peso = INFINITO;
}


Grafo::Grafo(){

}

Grafo::~Grafo(){
    for(auto iter =grafo.begin(); iter != grafo.end(); ++iter){
        delete(iter->second);
    }
    for(auto rel : relaciones){
        delete(rel);
    }
}

#endif // GRAFO_H
