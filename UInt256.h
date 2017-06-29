#include <string>
#include <iostream>

class UInt256
{
    private:
        unsigned int parts[8] = {0};
        void addToPart(int p, unsigned int n);
    public:
        UInt256();
        UInt256(const UInt256 &n);
        UInt256(unsigned int n);
        UInt256(std::string n);
        std::string toString();
        friend std::ostream& operator<<(std::ostream& os, const UInt256 &n);
        friend UInt256 operator+(UInt256 n, unsigned int m);
        friend UInt256 operator+(UInt256 n, const UInt256 &m);
        friend UInt256 operator~(UInt256 n);
        friend UInt256 operator-(const UInt256 &n, unsigned int m);
        friend UInt256 operator<<(UInt256 n, int b);
};