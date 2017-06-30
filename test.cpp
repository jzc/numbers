#include <iostream>
#include <limits.h>
#include "UInt256.h"

using namespace std;

int main()
{
    UInt256 u(123456789);
    cout << u << endl;
    cout << (u << 64) << endl;
    cout << (u << 65) << endl;
    cout << (u << 66) << endl;
}