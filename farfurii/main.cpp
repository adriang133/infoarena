#include <fstream>
#include <queue>
#define NMAX 100005
 
using namespace std;
 
long long sol[NMAX];
 
int main()
{
    //vector<long long> sol, V;
    long long N, K, i, sum, V[NMAX], max, pIndex, element;

 
    ifstream f("farfurii.in");
    f >> N >> K;
    f.close();
    //sol.resize(N + 1);
    //V.resize(N + 1);
    i = 1;
    sum = 0;
    V[N] = 0;
 
    while (sum + i <= K)
    {
        sum += V[N - i] = i;
        i++;
    }
    max = i;
    pIndex = N - i;
    element = N;
    if (pIndex < 0)
    {
        pIndex++;
    }
    for (i = pIndex + 1; i <= N; i++)
    {
        if ((K - sum != 0) && V[i - 1] == K - sum)
        {
                sol[i] = element - 1;
                sol[pIndex] = element;
                element -= 2;
        }
        else
        {
            sol[i] = element--;
        }
    }
 
    element = 1;
 
    ofstream g("farfurii.out");
    long long startIndex = 1, endIndex = N;
 
    for (i = startIndex; i <= N; i++)
    {
        if (sol[i] == 0)
        {
            g << element++ << " ";
        }
        else
        {
            g << sol[i] << " ";
        }
    }
    g.close();
 
    return 0;
}
