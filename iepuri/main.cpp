#include <fstream>
#include <vector>
#define MOD 666013
 
using namespace std;
 
 
long long mulMod(long long a, long long b, long long mod)
{
    //return ((a % mod) * (b % mod) % mod);
    return (a*b) % mod;
}
 
 
vector<vector<long long>> idvector(long long dim)
{
    vector<vector<long long>> result;
    result.resize(dim);
    for (long long i = 0; i < dim; i++)
    {
        result[i].resize(dim);
        result[i][i] = 1;
    }
    return result;
}
 
vector<vector<long long>> matrixProduct(vector<vector<long long>> m1, vector<vector<long long>> m2)
{
    vector<vector<long long>> result;
    result.resize(m1.size());
    for (vector<vector<long long>>::iterator it = result.begin(); it != result.end(); it++)
    {
        it->resize(m2.size());
    }
    for (size_t i = 0; i < m1.size(); i++)
    {
        for (size_t j = 0; j < m2[0].size(); j++)
        {
            long long sum = 0;
            for (size_t k = 0; k < m2.size(); k++)
            {
                //sum += ((m1[i][k] % MOD) * (m2[k][j] % MOD)) % MOD;
                sum += mulMod(m1[i][k], m2[k][j], MOD);
            }
            result[i][j] = sum;
        }
    }
    return result;
}
 
vector<vector<long long>> matrixPow(vector<vector<long long>> m, long long p)
{
    if (p == 0)
    {
        return idvector(m.size());
    }
    if (p == 1)
    {
        return m;
    }
    if (p % 2 == 0)
    {
        return matrixPow(matrixProduct(m, m), p / 2);
    }
    else
    {
        return matrixProduct(m, matrixPow(matrixProduct(m, m), (p - 1) / 2));
    }
}
 
int main()
{
    long long N, A, B, C, X, Y, Z, T;
    vector<long long> V;
    vector<vector<long long>> M;
    ifstream f("iepuri.in");
    ofstream g("iepuri.out");
    f >> T;
    for (; T; T--)
    {
        f >> X >> Y >> Z >> A >> B >> C >> N;
 
        V.resize(3);
        M.resize(3); M[0].resize(3); M[1].resize(3); M[2].resize(3);
 
        V[0] = X; V[1] = Y; V[2] = Z;
        M[0][0] = 0; M[0][1] = 0; M[0][2] = C;
        M[1][0] = 1; M[1][1] = 0; M[1][2] = B;
        M[2][0] = 0; M[2][1] = 1; M[2][2] = A;
 
        vector<vector<long long>> result = matrixPow(M, N - 2);
 
        long long ans = (mulMod(V[0], result[0][2], MOD) + mulMod(V[1], result[1][2], MOD) + mulMod(V[2], result[2][2], MOD)) % MOD;
        g << ans << "\n";
    }
    f.close();
    g.close();
    return 0;
}
