#include "UInt256.h"
#include <string>
#include <iostream>
#include <bitset>
#include <sstream>
#include <algorithm>

UInt256::UInt256() {}

UInt256::UInt256(const UInt256 &n)
{
    for (int i = 0; i < SIZE; ++i)
    {
        parts[i] = n.parts[i];
    }
}

UInt256::UInt256(const unsigned int n)
{
    parts[0] = n;
}

UInt256::UInt256(const std::string n)
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

std::string UInt256::toString() const
{
    std::ostringstream os;
    if (*this == 0)
    {
        os << "0";
        return os.str();
    }
    UInt256 c = *this, rem;
    while (c != 0)
    {
        divMod(c, TEN, c, rem);
        os << (char)(rem.parts[0] + '0');
    }
    std::string temp = os.str();
    std::reverse(temp.begin(), temp.end());
    return temp;
}

std::ostream &operator<<(std::ostream &os, const UInt256 &n)
{
    // for (int i = SIZE - 1; i >= 0; --i)
    // {
    //     os << std::bitset<LEN>(n.parts[i]) << std::endl;
    // }
    os << n.toString();
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
    return n;
}

UInt256 operator^(UInt256 n, const UInt256 &m)
{
    for (int i = 0; i < SIZE; ++i)
    {
        n.parts[i] ^= m.parts[i];
    }
    return n;
}

UInt256 operator|(UInt256 n, const UInt256 &m)
{
    for (int i = 0; i < SIZE; ++i)
    {
        n.parts[i] |= m.parts[i];
    }
    return n;
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

UInt256 &UInt256::operator=(const unsigned int n)
{
    parts[0] = n;
    for (int i = 1; i < SIZE; ++i)
    {
        parts[i] = 0;
    }
    return *this;
}

bool operator==(const UInt256 &n, const unsigned int m)
{
    for (int i = SIZE-1; i >= 1; --i)
    {
        if (n.parts[i] != 0)
        {
            return false;
        }
    }
    return n.parts[0] == m;
}

bool operator!=(const UInt256 &n, const unsigned int m)
{
    for (int i = SIZE-1; i >= 1; --i)
    {
        if (n.parts[i] != 0)
        {
            return true;
        }
    }
    return n.parts[0] != m;
}

//template these?
bool operator>(const UInt256 &n, const UInt256 &m)
{
    for(int i = SIZE-1; i >= 0; --i)
    {
        if (n.parts[i] != m.parts[i])
        {
            return n.parts[i] > m.parts[i];
        }
    }
    return false;
}

bool operator<(const UInt256 &n, const UInt256 &m)
{
    for(int i = SIZE-1; i >= 0; --i)
    {
        if (n.parts[i] != m.parts[i])
        {
            return n.parts[i] < m.parts[i];
        }
    }
    return false;
}

bool operator>=(const UInt256 &n, const UInt256 &m)
{
    for(int i = SIZE-1; i >= 0; --i)
    {
        if (n.parts[i] != m.parts[i])
        {
            return n.parts[i] >= m.parts[i];
        }
    }
    return true;
}

bool operator<=(const UInt256 &n, const UInt256 &m)
{
    for(int i = SIZE-1; i >= 0; --i)
    {
        if (n.parts[i] != m.parts[i])
        {
            return n.parts[i] <= m.parts[i];
        }
    }
    return true;
}

void divMod(UInt256 n, UInt256 m, UInt256 &ans, UInt256 &rem)
{
    if (n == 0)
    {
        return;
    }
    if (m > n)
    {
        ans = 0;
        rem = n;
        return;
    }
    if (n == m)
    {
        ans = 1;
        rem = 0;
        return;
    }

    UInt256 c = 1;
    ans = 0;
    //todo: check for overflow
    while (m <= n)
    {
        m = m << 1;
        c = c << 1;
    }
    m = m >> 1;
    c = c >> 1;
    while (c != 0)
    {
        if (n >= m)
        {
            n = n - m;
            ans = ans | c;
        }
        c = c >> 1;
        m = m >> 1;
    }
    rem = n;
}