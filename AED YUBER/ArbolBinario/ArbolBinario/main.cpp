#include <iostream>
#include "ArbolBinario.h"

using namespace std;

int main()
{
    ArbolBinario arbolito;
    arbolito.insert(10);
    arbolito.insert(5);
    arbolito.insert(15);
    arbolito.preordenInverso();
}
