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
        UInt256(const unsigned int n);
        UInt256(const std::string n);
        UInt256(const char* n);
        UInt256& operator=(const unsigned int n);
        std::string toString() const; // why is this const?
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
        friend bool operator==(const UInt256 &n, const unsigned int m);
        friend bool operator!=(const UInt256 &n, const UInt256 &m);
        friend bool operator!=(const UInt256 &n, const unsigned int m);
        friend bool operator> (const UInt256 &n, const UInt256 &m);
        friend bool operator< (const UInt256 &n, const UInt256 &m);
        friend bool operator>=(const UInt256 &n, const UInt256 &m);
        friend bool operator<=(const UInt256 &n, const UInt256 &m);
};

static const UInt256 TEN = 10;

void divMod(UInt256 n, UInt256 m, UInt256 &ans, UInt256 &rem);