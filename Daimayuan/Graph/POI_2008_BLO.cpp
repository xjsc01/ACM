#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1.1e5;
const int M = 2.1e5;
int n, m;
vector<int> edge[N];
int dfn[N], low[N], idx;
bool cut[N];
ll ans[N];
int remain[N];
int sz[N];
void dfs(int x, int fa)
{
    int ch = 0;// 表示子儿子的个数
    remain[x] = n - 1;
    ans[x] = n - 1;// 表示某一个点的父节点以及没有砍去的点的个数
    dfn[x] = low[x] = ++idx;
    for(int y : edge[x]){
        if(!dfn[y]){
            dfs(y, x);
            sz[x] += sz[y];
            ch ++;
            low[x] = min(low[x], low[y]);
            if(low[y] >= dfn[x]) { // low的判断条件
                cut[x] = true;
                remain[x] -= sz[y];
                ans[x] += (ll) sz[y] * (n - sz[y]);
            }
        }
        else{
            if(y != fa){
                low[x] = min(low[x], dfn[y]);// 点的更新方式不一样
            }
        }
    }
    ans[x] += (ll) remain[x] * (n - remain[x]);
    sz[x] += 1;

    if(x == 1 && ch <= 1) {
        cut[x] = 0;// 特判一下根节点的情况
        ans[x] = 2LL * (n - 1);
    }
}
int main()
{
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= m; i++){
        int x, y;
        scanf("%d%d", &x, &y);
        edge[x].push_back(y);
        edge[y].push_back(x);
    }
    dfs(1, 0);
    for(int i = 1; i <= n; i++){
        printf("%lld\n", ans[i]);
    }
    return 0;
}