#include <iostream>
#include "BinomialHeap.h"
#include "stdlib.h"
#include "time.h"

using namespace std;

int main()
{
    srand(time(NULL));
    BinomialHeap<int> miHeap("Chris_Heap");
    int number = 0;
    for(int i = 0; i < 10000; i++){
        number = rand() % 10000;
        miHeap.insert(number);
    }
    miHeap.print("mensaje");




}
