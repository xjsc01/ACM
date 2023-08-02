#include <bits/stdc++.h>
using namespace std;
const int N = 1.1e5;
const int M = 2.1e5;
int n, m;
vector<int> edge[N];
int dfn[N], low[N], idx;
bool cut[N];
void dfs(int x, int fa)
{
    //cout << x << "  ";
    int ch = 0;// 表示子儿子的个数
    dfn[x] = low[x] = ++idx;
    for(int y : edge[x]){
        if(!dfn[y]){
            dfs(y, x);
            ch ++;
            low[x] = min(low[x], low[y]);
            if(low[y] >= dfn[x]) // low的判断条件
                cut[x] = true;
        }
        else{
            if(y != fa){
                low[x] = min(low[x], dfn[y]);// 点的更新方式不一样
            }
        }
    }
    if(x == 1 && ch <= 1) cut[x] = 0;// 特判一下根节点的情况

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
    int sz = 0;
    for(int i = 1; i <= n; i++){
        if(cut[i]) sz++;
    }
    printf("%d\n", sz);
    for(int i = 1; i <= n; i++){
        if(cut[i]){
            printf("%d ", i);
        }
    }
    return 0;
}
