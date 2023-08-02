#include <bits/stdc++.h>
using namespace std;
int n, m;
const int N = 2e5;
vector<int> edge[N];
int dfn[N], low[N], bel[N], idx;
bool ins[N];
stack<int> stk;
vector<int> vec[N]; // 保存强连通子图中的所有点
int cnt;
int dp[N], way[N];
int mod;
void tarjan(int x)
{
    dfn[x] = low[x] = ++idx;
    ins[x] = true;
    stk.push(x);
    for (int y : edge[x])
    {
        if (!dfn[y])
            tarjan(y);
        if (ins[y])
        {
            low[x] = min(low[x], low[y]);
        }
    }
    if (low[x] == dfn[x])
    {
        ++cnt;
        while (true)
        {
            int tt = stk.top();
            bel[stk.top()] = cnt;
            vec[cnt].push_back(tt);
            ins[stk.top()] = false;
            stk.pop();
            if (tt == x)
                break;
        }
    }
}
int main()
{
    scanf("%d%d%d", &n, &m, &mod);
    for (int i = 1; i <= m; i++)
    {
        int x, y;
        scanf("%d%d", &x, &y);
        edge[x].push_back(y);
    }
    for (int i = 1; i <= n; i++)
    {
        if (!dfn[i])
        {
            tarjan(i);
        }
    }

    int w = 0, ans = 0;
    // w表示方法，ans表示最大半连通子图的个数
    for (int i = 1; i <= cnt; i++)
    {
        static bool vis[N];
        // 要注意重边, 因为重边会影响到方案数
        dp[i] = 0, way[i] = 1;
        for (int u : vec[i])
        {
            for (int v : edge[u])
            {
                if(vis[bel[v]]) continue;
                if (bel[u] != bel[v])
                {
                    vis[bel[v]] = true;
                    if(dp[bel[v]] > dp[i]) dp[i] = dp[bel[v]], way[i] = 0;
                    if(dp[bel[v]] == dp[i]) way[i] = (way[i] + way[bel[v]]) % mod;
                }
            }
        }
        dp[i] = dp[i] + vec[i].size();
        if(dp[i] > ans) 
            ans = dp[i], w = 0;
        if(dp[i] == ans) 
            w = (w + way[i]) % mod;
        for (int u : vec[i])
        {
            for (int v : edge[u])
            {
               vis[bel[v]] = 0;
            }
        }
    }
    printf("%d\n%d", ans, w);
    return 0;
}
