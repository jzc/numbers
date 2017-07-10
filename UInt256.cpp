#include "UInt256.h"
#include <string>
#include <iostream>
#include <bitset>

UInt256::UInt256() {}

UInt256::UInt256(const UInt256 &n)
{
    for (int i = 0; i < SIZE; ++i)
    {
        parts[i] = n.parts[i];
    }
}

UInt256::UInt256(unsigned int n)
{
    parts[0] = n;
}

UInt256::UInt256(std::string n)
{
    for (auto c : n)
    {
        *this = (*this) * 10 + c - '0';
    }
}

UInt256::UInt256(const char *n)
{
    for (; (*n) != '\0'; ++n)
    {
        *this = (*this) * 10 + (*n) - '0';
    }
}

void UInt256::addToPart(int p, unsigned int n)
{
    if ((parts[p] + n) < parts[p])
    {
        if (p != SIZE)
        {
            addToPart(p + 1, 1);
        }
    }
    parts[p] += n;
}

std::string UInt256::toString()
{
    return std::to_string(parts[1]) + " " + std::to_string(parts[0]);
}

std::ostream &operator<<(std::ostream &os, const UInt256 &n)
{
    for (int i = SIZE - 1; i >= 0; --i)
    {
        os << std::bitset<LEN>(n.parts[i]) << std::endl;
    }
    return os;
}

UInt256 operator+(UInt256 n, unsigned int m)
{
    n.addToPart(0, m);
    return n;
}

UInt256 &operator+=(UInt256 &n, unsigned int m)
{
    n.addToPart(0, m);
    return n;
}

UInt256 operator+(UInt256 n, const UInt256 &m)
{
    for (int i = 0; i < SIZE; ++i)
    {
        n.addToPart(i, m.parts[i]);
    }
    return n;
}

UInt256 &operator+=(UInt256 &n, const UInt256 &m)
{
    for (int i = 0; i < SIZE; ++i)
    {
        n.addToPart(i, m.parts[i]);
    }
    return n;
}

UInt256 operator~(UInt256 n)
{
    for (auto &p : n.parts)
    {
        p = ~p;
    }
    return n;
}

UInt256 operator&(UInt256 n, const UInt256 &m)
{
    for (int i = 0; i < SIZE; ++i)
    {
        n.parts[i] &= m.parts[i];
    }
}

UInt256 operator^(UInt256 n, const UInt256 &m)
{
    for (int i = 0; i < SIZE; ++i)
    {
        n.parts[i] ^= m.parts[i];
    }
}

UInt256 operator|(UInt256 n, const UInt256 &m)
{
    for (int i = 0; i < SIZE; ++i)
    {
        n.parts[i] |= m.parts[i];
    }
}

UInt256 operator-(const UInt256 &n, unsigned int m)
{
    UInt256 a(m);
    return n + (~a + 1);
}

UInt256 operator-(const UInt256 &n, const UInt256 &m)
{
    return n + (~m + 1);
}

UInt256 operator<<(UInt256 n, int b)
{
    if (b >= SIZE * LEN)
    {
        for (int i = 0; i < SIZE; ++i)
        {
            n.parts[i] = 0;
        }
    }
    else
    {
        //simplify shift to less than 32
        int up = b / LEN;
        if (up >= 1)
        {
            for (int i = SIZE - 1; i >= up; --i)
            {
                n.parts[i] = n.parts[i - up];
            }
            for (int i = 0; i < up; ++i)
            {
                n.parts[i] = 0;
            }
            b %= LEN;
        }
        if (b != 0)
        {
            unsigned int prev, curr;
            prev = n.parts[up] >> (LEN - b);
            n.parts[up] <<= b;
            for (int i = up + 1; i < SIZE; ++i)
            {
                curr = n.parts[i] >> (LEN - b);
                (n.parts[i] <<= b) += prev;
                prev = curr;
            }
        }
    }
    return n;
}

UInt256 operator>>(UInt256 n, int b)
{
    if (b >= LEN * SIZE)
    {
        for (int i = 0; i < SIZE; ++i)
        {
            n.parts[i] = 0;
        }
    }
    else
    {
        int down = b / LEN;
        if (down >= 1)
        {
            for (int i = 0; i < SIZE - down; ++i)
            {
                n.parts[i] = n.parts[i + down];
            }
            for (int i = SIZE - 1; i >= SIZE - down; --i)
            {
                n.parts[i] = 0;
            }
            b %= LEN;
        }
        if (b != 0)
        {
            unsigned int prev, curr;
            prev = n.parts[SIZE - 1] << (LEN - b);
            n.parts[SIZE - 1] >>= b;
            for (int i = SIZE - 2; i >= 0; --i)
            {
                curr = n.parts[i] << (LEN - b);
                (n.parts[i] >>= b) += prev;
                prev = curr;
            }
        }
    }
    return n;
}

UInt256 operator*(const UInt256 &n, unsigned int m)
{
    UInt256 a;
    std::bitset<LEN> bits(m);
    for (int i = 0; i < LEN; ++i)
    {
        if (bits[i])
        {
            a += (n << i);
        }
    }
    return a;
}

UInt256 operator*(const UInt256 &n, const UInt256 &m)
{
    UInt256 a;
    int o = 0;
    for (int i = 0; i < SIZE; ++i)
    {
        std::bitset<LEN> bits(m.parts[i]);
        for (int j = 0; j < LEN; ++j)
        {
            if (bits[j])
            {
                a += (n << (j + o));
            }
        }
        o += LEN;
    }
    return a;
}

bool operator==(const UInt256 &n, const UInt256 &m)
{
    for (int i = 0; i < SIZE; ++i)
    {
        if (n.parts[i] != m.parts[i])
        {
            return false;
        }
    }
    return true;
}

bool operator!=(const UInt256 &n, const UInt256 &m)
{
    for (int i = 0; i < SIZE; ++i)
    {
        if (n.parts[i] == m.parts[i])
        {
            return false;
        }
    }
    return true;
}