#include <iostream>
#include "IntervalTree.h"

using namespace std;

int main()
{
    IntervalTree<int> arbolito;
    arbolito.insert(5,20);
    arbolito.insert(17,19);
    arbolito.insert(30,40);
    arbolito.insert(10,30);
    arbolito.insert(15,20);
    arbolito.insert(12,15);
    arbolito.print();
    auto node = arbolito.find(6,7);
    if(node){
        cout<<"RESULT->["<<node->low<<","<<node->high<<"]"<<endl;
    }
    else{
        cout<<"NO EXISTE"<<endl;
    }
}
