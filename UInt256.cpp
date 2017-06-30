#include "UInt256.h"
#include <string>
#include <iostream>
#include <bitset>

UInt256::UInt256() { }

UInt256::UInt256(const UInt256 &n)
{
    for (int i = 0; i < 8; ++i)
    {
        parts[i] = n.parts[i];
    }
}

UInt256::UInt256(unsigned int n)
{
    parts[0] = n;
}

void UInt256::addToPart(int p, unsigned int n)
{
    if ((parts[p] + n) < parts[p])
    {
        if (p != 8)
        {
            addToPart(p+1, 1);
        }
    }
    parts[p] += n;
}

std::string UInt256::toString()
{
    return std::to_string(parts[1]) + " " + std::to_string(parts[0]);
}

std::ostream& operator<<(std::ostream& os, const UInt256 &n)
{
    for (int i = 7; i >= 0; --i)
    {
        os << std::bitset<32>(n.parts[i]) << std::endl;
    }
    return os;
}

UInt256 operator+(UInt256 n, unsigned int m)
{
    n.addToPart(0,m);
    return n;
}

UInt256 operator+(UInt256 n, const UInt256 &m)
{
    for (int i = 0; i < 8; ++i)
    {
        n.addToPart(i, m.parts[i]);
    }
    return n;
}

UInt256 operator~(UInt256 n)
{
    for (int i = 0; i < 8; ++i)
    {
        n.parts[i] = ~n.parts[i];
    }
    return n;
}

UInt256 operator-(const UInt256 &n, unsigned int m)
{
    UInt256 a(m);
    return n + (~a+1);
}

UInt256 operator<<(UInt256 n, int b)
{
    unsigned int prev, curr;
    int up = b/32;
    if (up >= 1)
    {
        for (int i = 8; i >= up; --i)
        {
            n.parts[i] = n.parts[i-up];
        }
        for (int i = 0; i < up; ++i)
        {
            n.parts[i] = 0;
        }
        b %= 32;
    }
    if (b != 0)
    {
        prev = n.parts[up] >> (32-b);
        n.parts[up] <<= b;
        for (int i = up+1; i < 7; ++i)
        {
            curr = n.parts[i] >> (32-b);
            (n.parts[i] <<= b) += prev;
            prev = curr;
        }
        (n.parts[7] <<= b) += prev;
    }
    return n;
}