#include <iostream>
#include "Tree.h"

using namespace std;

int main()
{
    Tree<int> arbolito;
    arbolito.insert(10);
    arbolito.insert(5);
    arbolito.insert(15);
    arbolito.insert(20);
    arbolito.insert(7);
    arbolito.insert(30);
    arbolito.insert(31);
    arbolito.insert(8);
    arbolito.printN();
}
