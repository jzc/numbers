#include <iostream>
#include <limits.h>
#include "UInt256.h"

using namespace std;

int main(int argc, char** argv)
{
    cout << UInt256("12345") << endl;
    cout << UInt256(12345)+1 << endl;
}