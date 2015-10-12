#include <iostream>
#include "AVL.h"

using namespace std;

int main()
{
    AVL<int> arbolito;
    arbolito.add(20);
    arbolito.add(10);
    arbolito.add(15);
    arbolito.add(3);
    arbolito.add(14);
    arbolito.add(16);
    arbolito.add(30);
    arbolito.add(35);
    arbolito.add(40);


    arbolito.del(15);
    arbolito.del(14);


    arbolito.add(50);
    arbolito.del(30);

    arbolito.del(10);

    arbolito.add(33);
    arbolito.add(34);

    arbolito.del(40);
    arbolito.del(35);
    arbolito.del(20);

    arbolito.del(3);
    arbolito.del(50);
    arbolito.del(16);
    arbolito.del(34);
    arbolito.del(33);
    arbolito.print();






}
