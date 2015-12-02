#ifndef BT_H
#define BT_H
#include "list"
#include "fstream"

using namespace std;

template<typename T>
class BT
{
    public:
        BT();
        BT(string name, int maxD);
        class Key{
            public:
                Key();
                Key(T,int,int);
                T key;
                int nodoAnteriror;
                int nodoSiguiente;
        };
        class Nodo{
            public:
                Nodo();
                Nodo(int);
                list<Key *> keys;
                int name;
        }
        Nodo readDisk(int);
        void writeDisk(Nodo &);
        virtual ~BT();
    protected:
    private:
        string name;
        int maxDegree;
        int siz;
        int siz_nodo;
        int root;
};

void BT::writeDisk(Nodo& nod){
    string file = this->name + to_string(nod.name) + ".dat";
    ofstream archivo(file, ios::out | ios::binary);
    archivo.write(reinterpret_cast<char *>(&(nod.name)),sizeof(int));
    archivo.write(reinterpret_cast<char *>(&(nod.keys.size()),sizeof(int));
    for(Key * k : nod.keys){
        archivo.write(reinterpret_cast<char *>(k),sizeof(Key));
    }
    archivo.close();
}

BT::Nodo BT::readDisk(int name){
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
    return res;
}

BT::Nodo::Nodo(int name){
    this->name = name;
}

BT::Nodo::Nodo(){
    name = -1;
}

BT::Key::Key(T key, int anterior, int siguiente){
    this->key = key;
    nodoAnteriror = anterior;
    nodoSiguiente = siguiente;
}

BT::Key::Key(){
    nodoAnteriror = -1;
    nodoSiguiente = -1;
}


BT::~BT(){

}

BT::BT(string name, int maxD){
    string file = name + "/";
    this->name = file;
    string comando = "mkdir " + this->name;
    system(comando.c_str());
    maxDegree = maxD;
    siz = 0;
    siz_nodo = 0;
    root = 0;
}

BT::BT(){
    name = "BTDefault/";
    string comando = "mkdir " + name;
    system(comando.c_str());
    maxDegree = 0;
    siz = 0;
    siz_nodo = 0;
    root = 0;
}

#endif // BT_H
