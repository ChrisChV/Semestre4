#include <iostream>
#include "BinomialHeap.h"

using namespace std;

int main()
{
    BinomialHeap<int> miHeap("Chris_Heap",true);
    miHeap.insert(34);
    miHeap.insert(10);
    miHeap.insert(4);
    miHeap.insert(17);
    miHeap.insert(12);
    miHeap.insert(3);
    miHeap.insert(18);
    miHeap.insert(65);
    miHeap.insert(21);
    miHeap.insert(1);
    miHeap.insert(15);
    miHeap.deleteNodo(18);
    miHeap.deleteNodo(21);
    miHeap.deleteNodo(10);




}
