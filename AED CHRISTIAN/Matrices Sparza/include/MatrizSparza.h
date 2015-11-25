#ifndef MATRIZSPARZA_H
#define MATRIZSPARZA_H
#include "RedBlack.h"

template <typename T>
class MatrizSparza
{
    public:
        MatrizSparza();
        MatrizSparza(int,int,T);
        int fil_siz;
        int col_siz;
        T valorNulo;
        void print();
        RedBlack<int,T> & operator[](int);
        virtual ~MatrizSparza();
    protected:
    private:
        RedBlack<int,RedBlack<int, T>> matriz;
};

template <typename T>
void MatrizSparza<T>::print(){
    for(int i = 0; i < fil_siz; i++){
        RedBlack<int, T> temp;
        if(matriz.find(i,temp)){
            for(int j = 0; j < col_siz; j++){
                T caracter = valorNulo;
                temp.find(j,caracter);
                cout<<caracter;
            }
        }
        cout<<endl;
    }
}

template <typename T>
RedBlack<int,T> & MatrizSparza<T>::operator[](int fil){
    return matriz[fil];
}

template <typename T>
MatrizSparza<T>::MatrizSparza(){
    fil_siz = 0;
    col_siz = 0;
}

template <typename T>
MatrizSparza<T>::MatrizSparza(int fil, int col, T nul){
    fil_siz = fil;
    col_siz = col;
    valorNulo = nul;
}

template <typename T>
MatrizSparza<T>::~MatrizSparza(){

}

#endif // MATRIZSPARZA_H
