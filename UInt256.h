#include <string>
#include <iostream>
#define SIZE 8
#define LEN 32

class UInt256
{
    private:
        unsigned int parts[SIZE] = {0};
        void addToPart(int p, unsigned int n);
    public:
        UInt256();
        UInt256(const UInt256 &n);
        UInt256(unsigned int n);
        UInt256(std::string n);
        UInt256(const char* n);
        std::string toString();
        friend std::ostream& operator<<(std::ostream& os, const UInt256 &n);
        friend UInt256  operator+ (UInt256 n, unsigned int m);
        friend UInt256& operator+=(UInt256& n, unsigned int m);
        friend UInt256  operator+ (UInt256 n, const UInt256 &m);
        friend UInt256& operator+=(UInt256& n, const UInt256 &m);
        friend UInt256  operator~ (UInt256 n);
        friend UInt256  operator& (UInt256 n, const UInt256 &m);
        friend UInt256  operator^ (UInt256 n, const UInt256 &m);
        friend UInt256  operator| (UInt256 n, const UInt256 &m);
        friend UInt256  operator- (const UInt256 &n, unsigned int m);
        friend UInt256  operator- (const UInt256 &n, const UInt256 &m);
        friend UInt256  operator<<(UInt256 n, int b);
        friend UInt256  operator>>(UInt256 n, int b);
        friend UInt256  operator* (const UInt256 &n, unsigned int m);
        friend UInt256  operator* (const UInt256 &n, const UInt256 &m);
        friend bool operator==(const UInt256 &n, const UInt256 &m);
        friend bool operator!=(const UInt256 &n, const UInt256 &m);
};