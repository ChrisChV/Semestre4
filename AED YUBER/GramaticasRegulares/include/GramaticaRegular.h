#ifndef GRAMATICAREGULAR_H
#define GRAMATICAREGULAR_H
#include <fstream>
#include <iostream>
#include <map>

using namespace std;

class GramaticaRegular
{
    public:
        GramaticaRegular();
        GramaticaRegular(string file);
        virtual ~GramaticaRegular();
    protected:
    private:
     map<char,<char,char>> tablaDeTransiciones;
     char estadoInicial;
};

GramaticaRegular::GramaticaRegular(string file){
    ifstream archivo(file);
    char caracter;
    int estado = 0;
    while(archivo.get(caracter)){
        bool ini = false;
        switch(estado){
            case 0:
                if(caracter == 'T'){
                    archivo.get(caracter);
                    if(caracter == ':') estado = 1;
                    else{
                        cout<<"ERROR en el caracter "<<caracter<<" ABORTANDO"<<endl;
                        return;
                    }
                }
                else{
                    cout<<"ERROR en el caracter "<<caracter<<" ABORTANDO"<<endl;
                    return;
                }
                break;
            case 1:
                if(caracter == ';'){
                    estado = 2;
                    archivo.get(caracter);
                    tablaDeTransiciones['%'];
                }
                else if(caracter != ' ' or caracter != ','){
                    tablaDeTransiciones[caracter];
                }
                break;
            case 2:
                if(caracter == 'N'){
                    archivo.get(caracter);
                    if(caracter == ':') estado = 3;
                    else{
                        cout<<"ERROR en el caracter "<<caracter<<" ABORTANDO"<<endl;
                        return;
                    }
                }
                else{
                    cout<<"ERROR en el caracter "<<caracter<<" ABORTANDO"<<endl;
                    return;
                }
                break;
            case 3:
                if(caracter == ';'){
                    estado = 4;
                    archivo.get(caracter);
                }
                else if(caracter != ' ' or caracter != ','){
                    if(tablaDeTransiciones.find(caracter) != tablaDeTransiciones.end()){
                        cout<<"ERROR El caracter "<<caracter<<" ya existe en la lista de terminales. ABORTANDO"<<endl;
                        return;
                    }
                    for(auto iter = tablaDeTransiciones.begin(); iter != tablaDeTransiciones.end(); ++iter){
                        iter->second[caracter] = '#';
                    }
                    if(!ini){
                        estadoInicial = caracter;
                        ini = true;
                    }
                }
                break;
            case 4:
                if(caracter == 'N'){
                    archivo.get(caracter);
                    if(caracter == ':') estado = 3;
                    else{
                        cout<<"ERROR en el caracter "<<caracter<<" ABORTANDO"<<endl;
                        return;
                    }
                }
                else{
                    cout<<"ERROR en el caracter "<<caracter<<" ABORTANDO"<<endl;
                    return;
                }
                break;
        }
    }
}

#endif // GRAMATICAREGULAR_H
