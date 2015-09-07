#include <iostream>
#include <Pila.h>

using namespace std;

int main()
{
    Pila<int> memoria;
    string expresion;
    cin>>expresion;
    for(int i = 0; i < expresion.size(); i++){
        if(expresion[i] >= 48 and expresion[i] <= 57){
            memoria.agregar(expresion[i] - 48);
        }
        else if(expresion[i] == '+'){
            memoria.agregar(memoria.desapilar() + memoria.desapilar());
        }
        else if(expresion[i] == '-'){
            int a = memoria.desapilar();
            int b = memoria.desapilar();
            memoria.agregar(b - a);
        }
        else if(expresion[i] == '*'){
            memoria.agregar(memoria.desapilar() * memoria.desapilar());
        }
        else if(expresion[i] == '/'){
            int a = memoria.desapilar();
            int b = memoria.desapilar();
            memoria.agregar(b / a);
        }
    }
    cout<<memoria.desapilar();
}
