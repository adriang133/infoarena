#include <fstream>
#include <vector>
#include <algorithm>
#include <stdint.h>
#define INF 0x7fffffff
using namespace std;
 
class Edge
{
public:
    int child, length, cost;
    Edge(int c, int l, int cst)
    {
        child = c;
        length = l;
        cost = cst;
    }
};
 
vector<vector<Edge>> Tree;
vector<uint64_t> minCost;
uint64_t maxDistance = 0;
uint64_t cost = 0;
 
void preCompute(int node, uint64_t dist)
{
    int currentDistance = dist;
    if (currentDistance > maxDistance)
    {
        maxDistance = currentDistance;
    }
    if (Tree[node].size() == 0)
    {
        minCost[node] = INF;
        return;
    }
    int sumOfChildrenCosts = 0;
    for (vector<Edge>::iterator it = Tree[node].begin(); it != Tree[node].end(); it++)
    {
        preCompute(it->child, dist + it->length);
        minCost[it->child] = min(minCost[it->child], (uint64_t)it->cost);
        sumOfChildrenCosts += minCost[it->child];
    }
    minCost[node] = sumOfChildrenCosts;
}
 
int dfs(int node, uint64_t distance, uint64_t parentCost)
{
    vector<int> children;
    children.resize(Tree[node].size() + 1);
    if (Tree[node].size() == 0) // leaf
    {
        int needed = maxDistance - distance;
        return needed;
    }
    int maxPush = INF;
    for (int i = 0; i < Tree[node].size(); i++)
    {
        children[i] = dfs(Tree[node][i].child, distance + Tree[node][i].length, Tree[node][i].cost);
        maxPush = min(children[i], maxPush);
    }
    for (int i = 0; i < Tree[node].size(); i++)
    {
        if (children[i] - maxPush > 0)
        {
            cost += (children[i] - maxPush) * minCost[Tree[node][i].child];
        }
    }
    return maxPush;
}
 
int main()
{
    int n, i, a, b, c, d;
 
    ifstream f("arb2.in");
    f.tie(NULL);
    ios_base::sync_with_stdio(false);
    f >> n;
    Tree.resize(n + 1);
    minCost.resize(n + 1);
    for (i = 1; i <= n - 1; i++)
    {
        f >> a >> b >> c >> d;
        Tree[a].push_back(Edge(b, c, d));
    }
 
    preCompute(1, 0);
    dfs(1, 0, 0);
    ofstream g("arb2.out");
    g << cost;
    return 0;
}
