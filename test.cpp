#include <iostream>
#include <limits.h>
#include <stdlib.h>
#include "UInt256.h"
#include <deque>

using namespace std;

UInt256 factorial(int n)
{
    UInt256 u(n--);
    while(n >= 1) u = u*n--;
    return u;
}

int main(int argc, char** argv)
{
    UInt256 u = 1, m;
    u = u << 255;
    cout << u << endl;
    cout << u/2 << endl;
    cout << (u/2)*2 << endl;
    cout << u % 5 << endl;
}