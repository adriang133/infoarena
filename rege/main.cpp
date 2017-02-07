#include <fstream>
#include <algorithm>
#include <vector>
#include <queue>
#define MOD 666013
#define INF 1 << 30
using namespace std;
int m, n, startx, starty, endx, endy;
vector < vector< pair<int, int> > >  V;
 
int sum(int i, int j, int level)
{
    if (i == startx && j == starty)
    {
        return 1;
    }
    int res = 0;
    for (int di = -1; di <= 1; di++)
    {
        for (int dj = -1; dj <= 1; dj++)
        {
            if (i + di >= 1 && i + di <= m && j + dj >= 1 && j + dj <= n)
            {
                if (V[i + di][j + dj].second < level)
                {
                    res = (res + V[i + di][j + dj].first) % MOD;
                     
                }
            }
             
        }
    }
    return res;
}
 
void calculate(int cx, int cy, int dx, int dy, int level)
{
    queue<pair<int, pair<int, int>>> q;
    q.push(make_pair(level, make_pair(cx, cy)));
 
    while (!q.empty())
    {
        level = q.front().first;
        cx = q.front().second.first;
        cy = q.front().second.second;
        q.pop();
        V[cx][cy].first = sum(cx, cy, level);
        if (cx == dx && cy == dy)
        {
            return;
        }
        for (int di = -1; di <= 1; di++)
        {
            for (int dj = -1; dj <= 1; dj++)
            {
                if (di != 0 || dj != 0)
                {
                    if (cx + di >= 1 && cx + di <= m && cy + dj >= 1 && cy + dj <= n)
                    {
                        if (V[cx + di][cy + dj].second == -1)
                        {
                            q.push(make_pair(level + 1, make_pair(cx + di, cy + dj)));
                            V[cx + di][cy + dj].second = level + 1;
                        }
                    }
                }
            }
        }
    }
}
 
 
 
int main()
{
 
    ifstream in("rege.in");
     
    in >> m >> n >> startx >> starty >> endx >> endy;
    in.close();
 
    V.resize(m + 1);
    for (int i = 0; i <= m; i++)
    {
        V[i].resize(n + 1, make_pair(0, -1));
    }
 
    V[startx][starty] = make_pair(1, 0);
 
    calculate(startx, starty, endx, endy, 1);
 
    ofstream out("rege.out");
    out << V[endx][endy].first;
    out.close();
    return 0;
}
