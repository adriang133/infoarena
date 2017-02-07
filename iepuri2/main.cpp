#include <fstream>
#include <vector>
 
#define MOD 30011
using namespace std;
 
int N, K, x, y, head;
vector<vector<int>> cnt;
vector<vector<int>> G;
vector<bool> in;
 
void dfs(int nod, int level, int parent)
{
 
    if (G[nod].size() == 0)
    {
        //leaf
        for (int i = level; i <= K; i++)
        {
            cnt[nod][i] = 1;
        }
        cnt[parent][K] = -1;
    }
    else
    {
        for (vector<int>::iterator it = G[nod].begin(); it != G[nod].end(); it++)
        {
            dfs(*it, level + 1, nod);
        }
        int i;
        for (i = level; cnt[nod][i] != -1; i++)
        {
            cnt[nod][i] = 1;
            for (vector<int>::iterator it = G[nod].begin(); it != G[nod].end(); it++)
            {
                int sum = 0;
                for (int j = i + 1; j <= K && cnt[*it][j] != -1; j++)
                {
                    sum = (sum + cnt[*it][j]) % MOD;
                }
                cnt[nod][i] = (cnt[nod][i] * sum) % MOD;
            }
        }
        if (parent != -1)
            cnt[parent][i - 1] = -1;
    }
}
 
int main()
{
 
 
    ifstream f("iepuri2.in");
    f >> N >> K;
    G.resize(N + 1);
    in.resize(N + 1);
    cnt.resize(N + 1);
 
    for (int i = 1; i < N; i++)
    {
        f >> x >> y;
        G[x].push_back(y);
        cnt[i].resize(K + 1);
        in[y] = true;
    }
    cnt[N].resize(K + 1);
    f.close();
 
    for (int i = 1; i <= N; i++)
    {
        if (!in[i])
        {
            head = i;
            break;
        }
    }
 
    ofstream g("iepuri2.out");
    dfs(head, 1, -1);
    int sum = 0;
    int i = 1;
    while (cnt[head][i] > 0)
    {
        sum = (sum + cnt[head][i++]) % MOD;
    }
    g << sum;
    g.close();
    return 0;
}
