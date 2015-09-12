#ifndef TABLE_H
#define TABLE_H
#include <list>
#include <fstream>
#include <Record.h>
#include <algorithm>
#include "sad.h"
#include <cstring>

using namespace std;

class Table
{
    public:
        Table();
        Table(const char *file);
        void _print();
        bool find(Key,Campo &);
        bool next(Campo &);
        bool prev(Campo &);
        bool insert(Campo &);
        bool del(Key);
        virtual ~Table();
    protected:
    private:
        list<Record *> m_RecordSet;
        void _index(const char *file);
        bool _find(Key, list<Record *>::iterator &iter, long &);
        bool _find(Key, list<Record *>::iterator &iter);
        void _llenarCampo(Campo &);
        const char * file;
        list<Record *>::iterator recordActual;
};

bool Table::del(Key key){
    list<Record*>::iterator temp;
    long linea;
    if(!this->_find(key,temp,linea))return false;
    char campo[1000];
    ifstream archivo(file);
    ofstream archivoTemp("temp.dat");
    m_RecordSet.erase(temp);
    for(int i = 0; i < linea; i++){
        archivo.getline(campo, 1000);
        archivoTemp<<campo<<'\n';
    }
    archivo.getline(campo,1000);
    while(archivo.getline(campo,1000)){
        archivoTemp<<campo<<'\n';
    }
    archivo.close();
    archivoTemp.close();
    remove(file);
    rename("temp.dat",file);

    return true;
}

bool Table::insert(Campo &lista){
    list<Record*>::iterator temp;
    char key[5];
    for(int i = 0; i < lista.front().size(); i++){
        key[i] = lista.front()[i];
    }
    if(this->_find(key,temp))return false;
    ofstream archivo(file, ios::app);
    Record *nuevo = new Record();
    strcpy(nuevo->key,key);
    nuevo->inicio = archivo.tellp();
    m_RecordSet.push_back(nuevo);
    auto temporal = lista.end();
    temporal--;
    for(auto iter = lista.begin(); iter != lista.end(); ++iter){
        if(iter == temporal)archivo<<*iter<<'\n';
        else archivo<<*iter<<',';
    }
    archivo.close();
    return true;
}

void Table::_llenarCampo(Campo & lista){
    ifstream archivo(file);
    archivo.seekg((*recordActual)->inicio,std::ios::beg);
    char caracter = ' ';
    string campo;
    while(caracter != '\n'){
        archivo.get(caracter);
        if(caracter == ','){
            lista.push_back(campo);
            campo.clear();
        }
        else if(caracter != '\n'){
            campo.insert(campo.end(),caracter);
        }
        else if(caracter == '\n'){
            lista.push_back(campo);
            campo.clear();
        }
    }
}

bool Table::prev(Campo &lista){
    if(recordActual == m_RecordSet.begin())return false;
    recordActual--;
    _llenarCampo(lista);
    return true;
}

bool Table::next(Campo &lista){
    auto temp = m_RecordSet.end();
    temp--;
    if(recordActual == temp)return false;
    recordActual++;
    _llenarCampo(lista);
    return true;
}

bool Table::find(Key key, Campo &lista){
    ifstream archivo(file);
    if(!_find(key, recordActual))return false;
    archivo.seekg((*recordActual)->inicio,std::ios::beg);
    _llenarCampo(lista);
}

bool Table::_find(Key key, list<Record *>::iterator &iter){
    iter = m_RecordSet.begin();
    if(m_RecordSet.empty())return false;
    for(iter; iter != m_RecordSet.end(); ++iter){
        if(!strcmp((*iter)->key, key))return true;
    }
    return false;
}

bool Table::_find(Key key, list<Record *>::iterator &iter, long &contador){
    iter = m_RecordSet.begin();
    contador = 0;
    if(m_RecordSet.empty())return false;
    for(iter; iter != m_RecordSet.end(); ++iter){
        if(!strcmp((*iter)->key, key))return true;
        contador++;
    }
    return false;
}

void Table::_print(){
    for(auto iter = m_RecordSet.begin(); iter != m_RecordSet.end(); ++iter){
        cout<<(*iter)->key<<endl;
    }
}

void Table::_index(const char *file){
    this->file = file;
    ifstream archivo(file);
    char linea[1000];
    char caracter[10];
    long pos = 0;
    long fila = 1;
    while(archivo.good()){
        archivo.getline(caracter,11,',');
        archivo.getline(linea,1000);
        Record *temp = new Record();
        temp->inicio = pos;
        temp->fila = fila;
        strcpy(temp->key,caracter);
        m_RecordSet.push_back(temp);
        pos += strlen(caracter) + strlen(linea) + 3;
        fila++;
    }
    auto iter = m_RecordSet.end();
    iter--;
    m_RecordSet.erase(iter--);
    archivo.close();
}


Table::Table(){

}

Table::Table(const char *file){
    _index(file);
}

Table::~Table(){

}

#endif // TABLE_H
