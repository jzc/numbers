#include <iostream>
#include <limits.h>
#include <stdlib.h>
#include "UInt256.h"

using namespace std;

UInt256 factorial(int n)
{
    UInt256 u(n--);
    while(n >= 1) u = u*n--;
    return u;
}

int main(int argc, char** argv)
{
    UInt256 u = 1;
    u = u << 255;
    UInt256 d = 2;
    cout << u << endl;
    UInt256 ans, rem;
    divMod(u, d, ans, rem);
    cout << ans << endl << rem << endl;
}