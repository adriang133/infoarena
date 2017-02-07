#include <fstream>
#include <vector>
#define MOD 9973
 
using namespace std;
 
int a, b, sol;
vector<int> v;
 
long long fact(int n)
{
    long long p = 1;
    for (int i = 2; i <= n; i++)
    {
        p *= i;
        //p %= MOD;
    }
    return p;
}
 
int comb(int n, int k)
{
    return fact(n) / ((fact(n - k) * fact(k))) % MOD;
}
 
ifstream in("numere6.in");
ofstream out("numere6.out");
 
int C[2][9001];
int inv(int i)
{
    return (i % 2);
}
 
void print(ostream &o, vector<int> v)
{
    for (int i = 0; i < v.size(); i++)
    {
        if (v[i] > 0)
        {
            o << i << "^" << v[i] << " ";
        }
    }
    o << "\n";
}
 
long long mulMod(long long a, long long b)
{
    return ((a%MOD) * (b%MOD) % MOD);
}
 
long long expMod(long long x, int e)
{
    if (e == 0) return 1;
    if (e == 1) return x;
    if (e % 2 == 0)
    {
        return expMod(mulMod(x, x), e / 2) % MOD;
    }
    else
    {
        return mulMod(x,expMod(mulMod(x,x), (e - 1) / 2));
    }
}
 
long long modinv(long long x)
{
    return expMod(x, MOD - 2);
}
 
 
 
 
void back(int level, int currentProduct, int lastDigit)
{
    if (currentProduct == b)
    {
        //count solution
        int total = 0;
        for (int i = 2; i <= 9; i++)
        {
            total += v[i];
        }
        long long tmp = C[inv(a) ^ 1][total] * fact(total);
        for (int i = 2; i <= 9; i++)
        {
            if (v[i] > 1)
            {
                auto modularInverse = modinv(fact(v[i]));
                tmp = mulMod(tmp, modularInverse);
            }
                 
        }
        //out << "add: " << tmp << " ";
        sol = (sol + tmp) % MOD;
        //out << " sol: " << sol << "\n";
        return;
    }
    else if (currentProduct > b)
    {
        return;
    }
    else
    {
        if (level == a + 1)
        {
            return;
        }
        for (int i = lastDigit; i < 10; i++)
        {
            if (b % i != 0)
                continue;
            if (currentProduct * i > b)
                break;
            v[i]++;
            back(level + 1, currentProduct * i, i);
            v[i]--;
        }
    }
}

int main()
{
    in >> a >> b;
    v.resize(10);
    C[0][0] = 1;
    C[0][1] = 1;
    for (int i = 2; i <= 25; i++)
    {
        C[0][i] = 0;
    }
 
    for (int i = 2; i <= a; i++)
    {
        for (int j = 0; j <= 25; j++)
        {
            if (i == j || j == 0)
                C[inv(i) ^ 1][j] = 1 % MOD;
            else
                C[inv(i) ^ 1][j] = ((C[inv(i)][j - 1] % MOD) + (C[inv(i)][j] % MOD)) % MOD;
        }
    }
 
    back(1, 1, 2);
 
    out << sol;
 
    return 0;
}
