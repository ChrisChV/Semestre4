#include <iostream>
#include "RedBlack.h"

using namespace std;

int main()
{
    RedBlack<int> arbolito;
    arbolito.insert(10);
    arbolito.insert(15);
    arbolito.insert(20);
    arbolito.insert(8);
    arbolito.insert(9);
    arbolito.print();
    arbolito.insert(45);
    arbolito.insert(50);
    arbolito.insert(51);
    arbolito.insert(52);
    arbolito.insert(53);
    arbolito.insert(14);
    arbolito.insert(11);
    arbolito.insert(21);
    arbolito.insert(22);
    arbolito.insert(23);
    arbolito.insert(24);
    arbolito.insert(25);
    arbolito.insert(19);

    arbolito.del(10);

    arbolito.del(50);

    arbolito.del(51);

    arbolito.del(21);
    arbolito.del(23);






}
