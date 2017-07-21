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
    cout << factorial(50) << endl;
}