#ifndef RECORD_H
#define RECORD_H
#include "iostream"

using namespace std;

class Record
{
    public:
        Record();
        Record(string, long, long);
        string key;
        long inicio;
        long fin;
};

Record::Record(string key1, long inicio, long fin)
{
    this->key = key1;
    this->inicio = inicio;
    this->fin = fin;
}

Record::Record()
{
    inicio = 0;
    fin = 0;
}

#endif // RECORD_H

