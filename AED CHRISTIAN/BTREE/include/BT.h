#ifndef BT_H
#define BT_H
#include "list"
#include "vector"
#include "fstream"
#include "queue"
#include "algorithm"

using namespace std;

enum Hermano{IZQUIERDO,DERECHO};
enum EstadosHermano{NO_TIENE_H_IZQUIERDO,NO_TIENE_H_DERECHO};

template<typename T>
class BT
{
    public:
        BT();
        BT(string name, int maxD,bool leer);
        class Key{
            public:
                Key();
                Key(T,int,int);
                T key;
                int nodoAnterior;
                int nodoSiguiente;
        };
        class Nodo{
            public:
                Nodo();
                Nodo(int,int);
                Nodo(int, vector<Key *>& ,int);
                vector<Key *> keys;
                bool findInNodo(T,int&);
                bool estoyLleno();
                bool puedoPrestar();
                bool estoyUnderFlow();
                bool soyHoja();
                int maxDegree;
                void deleteNodo();
                int name;
        };
        Nodo readDisk(int);
        void writeDisk(Nodo &);
        void deleteDisk(int);
        void eliminarArbol();
        void del(T key);
        bool find(T key);
        void insert(T key);
        void print();
        void printDot();
        void split(Nodo *padre, Nodo * hijo,int);
        int altura;
        virtual ~BT();
    protected:
    private:
        string name;
        bool _find(T key,int&, vector<Nodo*>&);
        void delMem(vector<Nodo *>&);
        void actualizarArbol();
        bool _del(Nodo *,Nodo *, T);
        void giroNormal(Nodo *, Nodo *, Nodo *,bool,int);
        void merge(Nodo *, Nodo *,Nodo *,bool,int,int);
        void getArbol();
        int maxDegree;
        int siz;
        int siz_nodo;
        int root;

};

template<typename T>
void BT<T>::delMem(vector<Nodo *>& v){
    for(Nodo * n : v){
        n->deleteNodo();
    }
    v.clear();
}

template<typename T>
void BT<T>::del(T key){
    int pos;
    vector<Nodo*> noditos;
    if(!_find(key,pos,noditos)) return;
    siz--;
    if(noditos.back()->soyHoja()){
        noditos.back()->keys.erase(noditos.back()->keys.begin() + pos);
        auto iter = noditos.end();
        iter--;
        for(iter; iter != noditos.begin();--iter){
            int a = (*iter)->keys.size();
            if((*iter)->estoyUnderFlow()){
                if(_del(*(iter - 1),*iter,key))return;
            }
            else{
                writeDisk(*(*iter));
                return;
            }
        }
    }
    else{
        int posActual = noditos.size() - 1;
        Nodo nodito = readDisk(noditos.back()->keys[pos]->nodoAnterior);
        noditos.push_back(new Nodo(nodito.name,nodito.keys,nodito.maxDegree));
        while(!nodito.soyHoja()){
            nodito = readDisk(nodito.keys.back()->nodoSiguiente);
            noditos.push_back(new Nodo(nodito.name,nodito.keys,nodito.maxDegree));
        }
        noditos[posActual]->keys[pos]->key = noditos.back()->keys.back()->key;
        writeDisk(*(noditos[posActual]));
        noditos.back()->keys.erase(noditos.back()->keys.end() - 1);
        auto iter = noditos.end();
        iter--;
        for(iter; iter != noditos.begin();--iter){
            if((*iter)->estoyUnderFlow()){
                if(_del(*(iter - 1),*iter,key))return;
            }
            else{
                writeDisk(*(*iter));
                return;
            }
        }
    }
    actualizarArbol();
    delMem(noditos);
}

template<typename T>
void BT<T>::merge(Nodo * padre, Nodo * hijo, Nodo * hermano, bool ladoH,int TH, int pos){
    if(ladoH == IZQUIERDO){
        if(TH != NO_TIENE_H_DERECHO){
            padre->keys[pos + 1]->nodoAnterior = padre->keys[pos]->nodoAnterior;
        }
        hermano->keys.push_back(new Key(padre->keys[pos]->key,hermano->keys[hermano->keys.size() - 1]->nodoSiguiente,hijo->keys[0]->nodoAnterior));
        hermano->keys.insert(hermano->keys.end(),hijo->keys.begin(),hijo->keys.end());
    }
    else{
        hermano->keys.insert(hermano->keys.begin(),new Key(padre->keys[pos]->key,hijo->keys[hijo->keys.size() - 1]->nodoSiguiente,hermano->keys[0]->nodoAnterior));
        hermano->keys.insert(hermano->keys.begin(),hijo->keys.begin(),hijo->keys.end());
    }
    writeDisk(*hermano);
    deleteDisk(hijo->name);
    padre->keys.erase(padre->keys.begin() + pos);
    if(padre->keys.empty() and padre->name == root){
        root = hermano->name;
        deleteDisk(padre->name);
    }
    else writeDisk(*padre);

}

template<typename T>
void BT<T>::deleteDisk(int key){
    string comando = "rm " + name + to_string(key) + ".dat";
    system(comando.c_str());
}

template<typename T>
bool BT<T>::Nodo::puedoPrestar(){
    if(keys.size() > maxDegree / 2)return true;
    return false;
}

template<typename T>
bool BT<T>::_del(Nodo * padre, Nodo * hijo, T key){
    int pos;
    padre->findInNodo(key,pos);
    int flag = -1;
    if(pos == 0) flag = NO_TIENE_H_IZQUIERDO;
    else if(pos == padre->keys.size()){
        pos--;
        flag = NO_TIENE_H_DERECHO;
    }
    Nodo der;
    Nodo izq;
    if(flag == NO_TIENE_H_IZQUIERDO){
        der = readDisk(padre->keys[pos]->nodoSiguiente);
        if(der.puedoPrestar()){
            giroNormal(padre,hijo,&der,DERECHO,pos);
            return true;
        }
        merge(padre,hijo,&der,DERECHO,flag,pos);
    }
    else if(flag == NO_TIENE_H_DERECHO){
        izq = readDisk(padre->keys[pos]->nodoAnterior);
        if(izq.puedoPrestar()){
            giroNormal(padre,hijo,&izq,IZQUIERDO,pos);
            return true;
        }
        merge(padre,hijo,&izq,IZQUIERDO,flag,pos);
    }
    else{
        der = readDisk(padre->keys[pos]->nodoSiguiente);
        if(der.puedoPrestar()){
            giroNormal(padre,hijo,&der,DERECHO,pos);
            return true;
        }
        pos--;
        izq = readDisk(padre->keys[pos]->nodoAnterior);
        if(izq.puedoPrestar()){
            giroNormal(padre,hijo,&izq,IZQUIERDO,pos);
            return true;
        }
        merge(padre,hijo,&izq,IZQUIERDO,flag,pos);
    }
    return false;
}

template<typename T>
void BT<T>::printDot(){
    string temp = name;
    auto iter = temp.end();
    iter--;
    temp.erase(iter);
    string file = name + temp + ".dot";
    ofstream archivo(file);
    archivo<<"digraph{graph [];node [fontsize = \"16\"shape = \"record\"];edge [];"<<endl;
    queue<int> noditos;
    if(root != -1)noditos.push(root);
    while(!noditos.empty()){
        Nodo nodito = readDisk(noditos.front());
        noditos.pop();
        archivo<<"nodo"<<to_string(nodito.name)<<" [label = \"<c0> ";
        int c = 1;
        for(Key * key : nodito.keys){
            archivo<<"| <c"<<to_string(c)<<"> "<<key->key<<" | <c"<<to_string(c+1)<<"> ";
            c += 2;
        }
        archivo<<"\"];"<<endl;
        bool flag = true;
        c = 2;
        for(Key * key : nodito.keys){
            if(flag){
                if(key->nodoAnterior != -1){
                    archivo<<"nodo"<<to_string(nodito.name)<<":c0 -> nodo"<<to_string(key->nodoAnterior)<<";"<<endl;
                    noditos.push(key->nodoAnterior);
                }
                flag = false;
            }
            if(key->nodoAnterior != -1){
                archivo<<"nodo"<<to_string(nodito.name)<<":c"<<to_string(c)<<" -> nodo"<<to_string(key->nodoSiguiente)<<";"<<endl;
                noditos.push(key->nodoSiguiente);
            }
            c += 2;
        }
    }
    archivo<<"}";
    archivo.close();
    string comando = "dot -Tpdf " + file + " -o " + name + temp + ".pdf";
    system(comando.c_str());
    string comando2 = "okular " + name + temp + ".pdf";
    system(comando2.c_str());
}



template<typename T>
void BT<T>::giroNormal(Nodo * padre, Nodo * hijo, Nodo * hermano, bool ladoH, int pos){
    if(ladoH == IZQUIERDO){
        hijo->keys.insert(hijo->keys.begin(),new Key(padre->keys[pos]->key,hermano->keys[hermano->keys.size() - 1]->nodoSiguiente,hijo->keys[0]->nodoAnterior));
        padre->keys[pos]->key = hermano->keys[hermano->keys.size() - 1]->key;
        hermano->keys.pop_back();
    }
    else{
        hijo->keys.push_back(new Key(padre->keys[pos]->key,hijo->keys[hijo->keys.size() - 1]->nodoSiguiente,hermano->keys[0]->nodoAnterior));
        padre->keys[pos]->key = hermano->keys[0]->key;
        hermano->keys.erase(hermano->keys.begin());
    }
    writeDisk(*hijo);
    writeDisk(*hermano);
    writeDisk(*padre);
}

template<typename T>
bool BT<T>::Nodo::estoyUnderFlow(){
    if(keys.size() < maxDegree / 2)return true;
    return false;
}

template<typename T>
bool BT<T>::Nodo::soyHoja(){
    if(keys.empty() or keys[0]->nodoAnterior == -1) return true;
    return false;
}

template<typename T>
void BT<T>::eliminarArbol(){
    string comando = "rm -r " + name;
    system(comando.c_str());
}

template<typename T>
void BT<T>::getArbol(){
    string file = name + "root.dat";
    ifstream archivo(file, ios::in | ios::binary);
    if(archivo.fail()){
        cout<<"No existe root"<<endl;
        return;
    }
    archivo.read(reinterpret_cast<char*>(&root),sizeof(int));
    archivo.read(reinterpret_cast<char *>(&siz),sizeof(int));
    archivo.read(reinterpret_cast<char *>(&siz_nodo),sizeof(int));
    archivo.read(reinterpret_cast<char *>(&altura),sizeof(int));
}

template<typename T>
void BT<T>::actualizarArbol(){
    string file = name + "root.dat";
    ofstream archivo(file, ios::out | ios::binary);
    archivo.write(reinterpret_cast<char *>(&root),sizeof(int));
    archivo.write(reinterpret_cast<char *>(&siz),sizeof(int));
    archivo.write(reinterpret_cast<char *>(&siz_nodo),sizeof(int));
    archivo.write(reinterpret_cast<char *>(&altura),sizeof(int));
    archivo.close();
}

template<typename T>
void BT<T>::print(){
    if(root == -1)return;
    queue<int> nodos;
    nodos.push(root);
    while(!nodos.empty()){
        int actual = nodos.front();
        nodos.pop();
        Nodo nodito = readDisk(actual);
        int s = 0;
        for(Key * key : nodito.keys){
            cout<<key->key<<" ";
            if(s == 0){
                if(key->nodoAnterior != - 1) nodos.push(key->nodoAnterior);
                if(key->nodoSiguiente != - 1) nodos.push(key->nodoSiguiente);
            }
            else{
                if(key->nodoSiguiente != -1) nodos.push(key->nodoSiguiente);
            }
            s++;
        }
        cout<<endl;
    }
}

template<typename T>
void BT<T>::insert(T key){
    int actual;
    vector<Nodo *> noditos;
    if(_find(key,actual,noditos))return;
    siz++;
    auto iter = noditos.end();
    iter--;
    (*iter)->keys.insert((*iter)->keys.begin() + actual, new Key(key,-1,-1));
    for(iter; iter != noditos.begin(); --iter){
        if((*iter)->estoyLleno()){
            split(*(iter - 1),*iter,(maxDegree) / 2);
        }
        else{
            writeDisk(*(*iter));
            return;
        }
    }
    if((*iter)->estoyLleno()){
        split(nullptr,*iter,(maxDegree) / 2);
    }
    else{
        writeDisk(*(*iter));
    }
    actualizarArbol();
    delMem(noditos);
}

template<typename T>
bool BT<T>::Nodo::estoyLleno(){
    int a = maxDegree;
    int b = keys.size();
    if(maxDegree < keys.size())return true;
    return false;
}

template<typename T>
bool BT<T>::find(T key){
    if(siz == 0)return false;
    int actual;
    list<Nodo> noditos;
    if(_find(key,actual,noditos)) return true;
    return false;
}

template<typename T>
bool BT<T>::_find(T key, int& actual, vector<Nodo*> & noditos){
    Nodo nodito = readDisk(root);
    for(int i = 0; i < altura; i++){
        noditos.push_back(new Nodo(nodito.name,nodito.keys,nodito.maxDegree));
        if(nodito.findInNodo(key,actual)) return true;
        if(actual == nodito.keys.size()) actual--;
        if(key < nodito.keys[actual]->key) nodito = readDisk(nodito.keys[actual]->nodoAnterior);
        else nodito = readDisk(nodito.keys[actual]->nodoSiguiente);
    }
    noditos.push_back(new Nodo(nodito.name,nodito.keys,nodito.maxDegree));
    if(nodito.findInNodo(key,actual))return true;
    return false;
}

template<typename T>
bool BT<T>::Nodo::findInNodo(T key, int &actual){
    int limInferior = 0;
    int limSuperior = keys.size() - 1;
    actual = 0;
    if(limSuperior == -1)return false;
    int sum = (limSuperior - limInferior) / 2;
    while(sum){
        actual = limInferior + sum;
        if(key == keys[actual]->key) return true;
        if(key > keys[actual]->key) limInferior = actual;
        else limSuperior = actual;
        sum = (limSuperior - limInferior) / 2;
    }
    if(keys[limInferior]->key == key){
        actual = limInferior;
        return true;
    }
    else if(keys[limSuperior]->key == key){
        actual = limSuperior;
        return true;
    }
    if(key < keys[limInferior]->key) actual = limInferior;
    else if(key > keys[limSuperior]->key) actual = limSuperior + 1;
    else if(key > keys[limInferior]->key and key < keys[limSuperior]->key) actual = limSuperior;
    return false;
}

template<typename T>
void BT<T>::split(Nodo * padre, Nodo * hijo, int med){
    auto iter = hijo->keys.begin() + med;
    //vector<Key *> first;
    //vector<Key *> second;
    /*
    for(int i = 0; i < med; i++){
        first.push_back(*iter);
        iter++;
    }
    auto iter3 = iter;
    iter3++;
    for(iter3; iter3 != hijo->keys.end();++iter3){
        second.push_back(*iter3);
    }
    */
    Nodo * nuevo = new Nodo(siz_nodo,maxDegree);
    nuevo->keys = vector<Key *>(hijo->keys.size() - (med + 1));
    move(iter + 1,hijo->keys.end(),nuevo->keys.begin());
    //cout<<"ITER->"<<(*iter)->key<<endl;
    siz_nodo++;
    if(padre){
        int flag = -1;
        int pos;
        padre->findInNodo((*iter)->key,pos);
        auto iter2 = padre->keys.begin() + pos;
        if(iter2 == padre->keys.begin()) flag = 1;
        else if(iter2 == padre->keys.end()) flag = 0;
        padre->keys.insert(iter2,*iter);
        padre->findInNodo((*iter)->key,pos);
        iter2 = padre->keys.begin() + pos;
        (*iter2)->nodoAnterior = hijo->name;
        (*iter2)->nodoSiguiente = nuevo->name;
        iter2++;
        if(flag == 1){
            (*iter2)->nodoAnterior = nuevo->name;
        }
        else if(flag == 0){
            iter2--;
            iter2--;
            (*iter2)->nodoSiguiente = hijo->name;
        }
        else{
            (*iter2)->nodoAnterior = nuevo->name;
            iter2--;
            iter2--;
            (*iter2)->nodoSiguiente = hijo->name;
        }
    }
    else{
        Nodo * nuevoRoot = new Nodo(siz_nodo,maxDegree);
        siz_nodo++;
        (*iter)->nodoAnterior = hijo->name;
        (*iter)->nodoSiguiente = nuevo->name;
        nuevoRoot->keys.push_back(*iter);
        root = nuevoRoot->name;
        altura++;
        writeDisk(*nuevoRoot);
    }
    hijo->keys.erase(iter,hijo->keys.end());
    writeDisk(*hijo);
    writeDisk(*nuevo);
}

template<typename T>
void BT<T>::writeDisk(Nodo& nod){
    string file = this->name + to_string(nod.name) + ".dat";
    ofstream archivo(file, ios::out | ios::binary);
    int n = nod.name;
    archivo.write(reinterpret_cast<char *>(&(n)),sizeof(int));
    int s = nod.keys.size();
    archivo.write(reinterpret_cast<char *>(&(s)),sizeof(int));
    for(Key * k : nod.keys){
        archivo.write(reinterpret_cast<char *>(k),sizeof(Key));
    }
    archivo.close();
}

template<typename T>
typename BT<T>::Nodo BT<T>::readDisk(int name){
    Nodo res;
    int n;
    int k;
    string file = this->name + to_string(name) + ".dat";
    ifstream archivo(file, ios::in | ios::binary);
    archivo.read(reinterpret_cast<char *>(&n),sizeof(int));
    res.name = n;
    archivo.read(reinterpret_cast<char *>(&k),sizeof(int));
    for(int i = 0; i < k; i++){
        Key key;
        archivo.read(reinterpret_cast<char *>(&key),sizeof(Key));
        res.keys.push_back(new Key(key.key, key.nodoAnterior, key.nodoSiguiente));
    }
    archivo.close();
    res.maxDegree = maxDegree;
    return res;
}

template<typename T>
BT<T>::Nodo::Nodo(int name, vector<Key *>& key,int maxD){
    this->name = name;
    this->keys = key;
    this->maxDegree = maxD;
}

template<typename T>
BT<T>::Nodo::Nodo(int name,int maxD){
    this->name = name;
    this->maxDegree = maxD;
}

template<typename T>
BT<T>::Nodo::Nodo(){
    name = -1;
}

template<typename T>
BT<T>::Key::Key(T key, int anterior, int siguiente){
    this->key = key;
    nodoAnterior = anterior;
    nodoSiguiente = siguiente;
}

template<typename T>
BT<T>::Key::Key(){
    nodoAnterior = -1;
    nodoSiguiente = -1;
}

template<typename T>
BT<T>::~BT(){

}

template<typename T>
BT<T>::BT(string name, int maxD,bool leer){
    string file = name + "/";
    this->name = file;
    string comando = "mkdir " + this->name;
    system(comando.c_str());
    maxDegree = maxD;
    siz = 0;
    siz_nodo = 1;
    root = 0;
    altura = 0;
    if(!leer){
        Nodo r(0,maxD);
        writeDisk(r);
        actualizarArbol();
    }
    else{
        getArbol();
    }
}

template<typename T>
void BT<T>::Nodo::deleteNodo(){
    for(Key * key : keys){
        delete(key);
    }
    keys.clear();
    delete this;
}

template<typename T>
BT<T>::BT(){
    name = "BTDefault/";
    string comando = "mkdir " + name;
    system(comando.c_str());
    maxDegree = 0;
    siz = 0;
    siz_nodo = 1;
    root = 0;
    Nodo r(0,0);
    writeDisk(r);
    actualizarArbol();
    altura = 0;
}

#endif // BT_H
