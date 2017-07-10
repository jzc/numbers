#include <iostream>
#include <limits.h>
#include "UInt256.h"

using namespace std;

int main(int argc, char** argv)
{
    UInt256 u(UINT_MAX);
    u = u << 32*2;
    cout << u << endl;
    cout << (u >> 32) << endl;
    cout << (u >> 64) << endl;
    cout << (u >> 66) << endl;
}