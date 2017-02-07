#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
using namespace std;
 
int NumberOfSetBits(int i)
{
    i = i - ((i >> 1) & 0x55555555);
    i = (i & 0x33333333) + ((i >> 2) & 0x33333333);
    return (((i + (i >> 4)) & 0x0F0F0F0F) * 0x01010101) >> 24;
}
 
class BigNumber33554432{
    const int base = 1 << 25;
    void add_value(int v) // 0 <= v < 10
    {
        container[0] += v;
        int i = 0;
        while (container[i] >= base)
        {
            if (container.size() == i + 1)
                container.push_back(0);
            container[i] -= base;
            container[++i] += 1;
        }
    }
    void multiplyBy(int value)
    {
        int carry = 0;
        for (int i = 0; i < container.size(); i++)
        {
            container[i] = container[i] * value + carry;
            carry = 0;
            if (container[i] >= base)
            {
                carry = container[i] / base;
                container[i] %= base;
            }
        }
        while (carry > 0)
        {
            container.push_back(carry % base);
            carry /= base;
        }
    }
public:
    vector<int> container;
    BigNumber33554432(string s)
    {
        container.push_back(0);
        for (int i = 0; i < s.length(); i++)
        {
            multiplyBy(10);
            add_value(s[i] - '0');
        }
    }
 
};
 
int main()
{
    ifstream in("biti2.in");
    ofstream out("biti2.out");
 
    string s;
    int n, x;
    for (in >> n; n; n--)
    {
        in >> s;
        int totalCount = 0;
 
        BigNumber33554432 bn(s);
 
        for (int i = 0; i < bn.container.size(); i++)
        {
            totalCount += NumberOfSetBits(bn.container[i]) % 2;
        }
        if (totalCount % 2)
        {
            out << 1;
        }
        else
        {
            out << 0;
        }
        out << "\n";
    }
 
     
    return 0;
}
