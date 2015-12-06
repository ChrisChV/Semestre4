#include <iostream>
#include "BT.h"

using namespace std;

int main()
{
    cout << "Hello world!" << endl;
    BT<int> arbolito("arbolito",4,false);
    //733;
    for(int i = 0; i < 30; i++){
        arbolito.insert(i);
    }
    /*arbolito.insert(10);
    arbolito.insert(20);
    arbolito.insert(30);
    arbolito.insert(40);
    arbolito.insert(50);
    arbolito.insert(60);
    arbolito.insert(5);
    arbolito.insert(15);
    arbolito.insert(70);
    arbolito.insert(80);
    arbolito.insert(25);
    arbolito.insert(90);
    arbolito.insert(100);
    arbolito.insert(110);
    arbolito.insert(45);
    arbolito.insert(55);
    arbolito.insert(58);
    arbolito.insert(46);
    arbolito.insert(47);
    arbolito.insert(48);
    arbolito.insert(39);
    arbolito.insert(26);
    arbolito.insert(27);
    arbolito.insert(28);
    arbolito.insert(38);
    arbolito.insert(37);
    arbolito.insert(85);
    arbolito.insert(87);
    arbolito.insert(89);
    arbolito.insert(52);
    arbolito.insert(53);
    arbolito.insert(54);
    arbolito.insert(120);
    arbolito.insert(130);
    arbolito.insert(140);
    arbolito.insert(1);
    arbolito.insert(2);
    arbolito.insert(3);
    arbolito.insert(6);
    arbolito.insert(7);
    arbolito.insert(8);
    arbolito.insert(11);
    arbolito.insert(12);
    arbolito.insert(13);
    */
    //arbolito.print();
    cout<<"ALTURA->"<<arbolito.altura<<endl;
    arbolito.del(20);

    arbolito.printDot();
    //arbolito.eliminarArbol();
}
