#include <iostream>
#include <limits.h>
#include "UInt256.h"

using namespace std;

int main()
{
    UInt256 u(UINT_MAX);
    cout << u*u*u*u << endl;
}