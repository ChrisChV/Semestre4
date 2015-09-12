#include <iostream>
#include "fstream"
#include "list"

using namespace std;

int main()
{
    list<int> my;
    for(int i = 0; i< 10; i++){
        my.push_back(i);
    }
    auto iter = my.end();
    cout<<*iter<<endl;
}
