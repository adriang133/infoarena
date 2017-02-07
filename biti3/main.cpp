#include <fstream>
#include <bitset>
 
using namespace std;
 
 
 
int main()
{
    int C[1668][4], n, m, i, j, dual, sol[1668], k;
    bitset<1666> bits;
    ifstream f("biti3.in");
    f >> n >> m;
    f.close();
    k = 3;
    //generate combinations
    for (i = 0; i <= n; i++)
    {
        for (j = 0; j <= k; j++)
        {
            if (i == 0)
            {
                C[i][j] = 0;
            }
            else if (j == 0 || i == j)
            {
                C[i][j] = 1;
            }
            else
            {
                C[i][j] = C[i - 1][j - 1] + C[i - 1][j];
            }
        }
    }
 
    for (i = n - 1; i >= 0 && bits.count() < 3; i--)
    {
        if (m <= C[i][k])
        {
            bits.reset(i);
        }
        else
        {
            bits.set(i);
            m = m - C[i][k];
            k--;
        }
    }
 
    ofstream g("biti3.out");
    for (i = n - 1; i >= 0; i--)
    {
        g << bits[i];
    }
    g.close();
 
    return 0;
}
