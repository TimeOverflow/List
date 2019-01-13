#include <iostream>
#include "List.h"
#include "List.cpp"

using namespace std;

// this  is to test for github..
int main()
{
    List<int> L;
    L.insertAsLast(5);
    L.insertAsFirst(8);
    cout << L;
    cout << L[0] << endl;  //overload operator[]
    List<int> L2(L);       //copy constructor
    cout << L2;
    //L2.clear();
    cout << L2;

    L.insertAsLast(7);
    L.insertAsLast(1);
    L.insertAsLast(4);
    cout << "--------------------------------" << endl;
    cout << "Sort:" << endl;
    cout << L;
    L.sort();
    cout << L;

    List<int >L3;
    cout << L3;
    L3.sort();
    cout << L3;

    L.reverse();
    cout << L;

    L3.reverse();
    cout << L3;


    return 0;
}