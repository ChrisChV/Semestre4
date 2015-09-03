#include <iostream>

using namespace std;

bool propioIdentificador(){
    string frase;
    cin>>frase;
    int estado = 0;
    for(int i = 0; i < frase.size(); i++){
        switch(estado){
            case 0:
                if(frase[i] == 99){
                    estado = 1;
                }
                else{
                    estado = 7;
                    i = frase.size() + 1;
                }
                break;
            case 1:
                if(frase[i] == 111){
                    estado = 2;
                }
                else{
                    estado = 7;
                    i = frase.size() + 1;
                }
                break;
            case 2:
                if(frase[i] == 100){
                    estado = 3;
                }
                else{
                    estado = 7;
                    i = frase.size() + 1;
                }
                break;
            case 3:
                if(frase[i] == 101){
                    estado = 4;
                }
                else{
                    estado = 7;
                    i = frase.size() + 1;
                }
                break;
            case 4:
                if(frase[i] == 99){
                    estado = 5;
                }
                else if((frase[i] >= 65 and frase[i] <= 90) or (frase[i] >= 97 and frase[i] <= 122) or (frase[i] >= 48 and frase[i] <= 57)){
                    estado = 4;
                }
                else{
                    estado = 7;
                    i = frase.size() + 1;
                }
                break;
            case 5:
                if(frase[i] == 104){
                    estado = 6;
                }
                else if(frase[i] == 99){
                    estado = 5;
                }
                else if((frase[i] >= 65 and frase[i] <= 90) or (frase[i] >= 97 and frase[i] <= 122) or (frase[i] >= 48 and frase[i] <= 57)){
                    estado = 4;
                }
                else{
                    estado = 7;
                    i = frase.size() + 1;
                }
                break;
            case 6:
                if((frase[i] >= 65 and frase[i] <= 90) or (frase[i] >= 97 and frase[i] <= 122) or (frase[i] >= 48 and frase[i] <= 57)){
                    estado = 4;
                }
                else{
                    estado = 7;
                    i = frase.size() + 1;
                }
                break;
        }
    }
    if(estado == 6){
        cout<<"El identificador esta correcto"<<endl;
        return true;
    }
    cout<<"ERROR"<<endl;
    return false;
}

bool numeroFloat(){
    string frase;
    cin>>frase;
    int estado = 0;
    for(int i = 0; i < frase.size(); i++){
        switch(estado){
            case 0:
                if(frase[i] >= 48 and frase[i] <= 57){
                    estado = 1;
                }
                else{
                    estado = 3;
                    i = frase.size() + 1;
                }
                break;
            case 1:
                if(frase[i] >= 48 and frase[i] <= 57){
                    estado = 1;
                }
                else if(frase[i] == 46){
                    estado = 2;
                }
                else{
                    estado = 3;
                    i = frase.size() + 1;
                }
                break;
            case 2:
                if(frase[i] >= 48 and frase[i] <= 57){
                    estado = 4;
                }
                else{
                    estado = 3;
                    i = frase.size() + 1;
                }
                break;
            case 4:
                if(frase[i] >= 48 and frase[i] <= 57){
                    estado = 4;
                }
                else{
                    estado = 3;
                    i = frase.size() + 1;
                }
                break;
        }
    }
    if(estado == 1 or estado == 4){
        cout<<"El identificador esta correcto"<<endl;
        return true;
    }
    cout<<"ERROR"<<endl;
    return false;
}

int main()
{
    numeroFloat();
}
