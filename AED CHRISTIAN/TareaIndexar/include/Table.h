#ifndef TABLE_H
#define TABLE_H
#include <list>
#include <fstream>
#include <Record.h>

using namespace std;

class Table
{
    public:
        Table();
        Table(const char *file);
        void _print();
        virtual ~Table();

    protected:
    private:
        list<Record *> m_RecordSet;

        void _index(const char *file);
        const char * file;
};

void Table::_print(){
    for(auto iter = m_RecordSet.begin(); iter != m_RecordSet.end(); iter++){
        cout<<(*iter)->key<<endl;
    }
}

void Table::_index(const char *file){
    this->file = file;
    ifstream archivo(file);
    char linea[128];
    while(!archivo.eof()){
        auto ini = archivo.tellg();
        archivo.getline(linea,128);
        auto fin = archivo.tellg();
        char caracter;
        string key;
        for(int i = 0; i < 4; i++){
            caracter = linea[i];
            if(caracter == ',')break;
            key.insert(key.end(),caracter);
        }
        m_RecordSet.push_back(new Record(key, ini, fin));
    }

}


Table::Table(){

}

Table::Table(const char *file){
    _index(file);
}

Table::~Table(){

}

#endif // TABLE_H
