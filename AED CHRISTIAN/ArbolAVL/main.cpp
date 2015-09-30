#include <iostream>
#include "AVL.h"

using namespace std;

int main()
{
    AVL<int> arbolito;
    arbolito.add(10);
    arbolito.add(5);
    arbolito.add(50);
    arbolito.add(40);
    arbolito.add(60);
    arbolito.add(70);
    arbolito.add(55);
    arbolito.add(80);
    arbolito.add(65);
    arbolito.add(75);
    arbolito.printNiveles();


}
