#include <iostream>
#include "BinomialHeap.h"

using namespace std;

int main()
{
    BinomialHeap<int> miHeap("Chris_Heap");
    miHeap.insert(10);
    miHeap.insert(13);
    miHeap.insert(20);
    miHeap.insert(11);
    miHeap.insert(34);
    miHeap.insert(5);
    miHeap.insert(23);
    miHeap.insert(12);
    miHeap.insert(43);
    //miHeap.print("adsa");
    cout<<miHeap.returnMin()<<endl;
    cout<<miHeap.returnMin()<<endl;
    cout<<"WWW->"<<miHeap.getInicio()->contenido->valor<<endl;
    miHeap.deleteMin();
    miHeap.deleteMin();
}
