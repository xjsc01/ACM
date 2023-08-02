/*
在tarjan中得到的顺序是拓扑序的反序！
*/
#include <bits/stdc++.h>
using namespace std;
int n, m;
typedef long long ll;
const int N = 6e5;
vector<int> edge[N];
int dfn[N], low[N], bel[N], idx;
bool ins[N]; 
stack<int> stk;
vector<int>vec[N];
bool isBar[N];// 表示SCC是否为酒吧
int cnt;
int a[N];
int S, P;
ll val[N];// 连通块的价值
ll dp[N];// 连通块以及其子块的价值
void tarjan(int x){
    dfn[x] = low[x] = ++idx;
    ins[x] = true;
    stk.push(x);
    for(int y : edge[x]){
        if(!dfn[y]) tarjan(y);
        if(ins[y]){
            low[x] = min(low[x], low[y]);
        }
    }
    if(low[x] == dfn[x]){
        ++cnt;
        while(true){
            int tt = stk.top();
            vec[cnt].push_back(tt);
            bel[stk.top()] = cnt;
            ins[stk.top()] = false;
            val[cnt] += a[tt];
            stk.pop();
            if(tt == x) break;
        }
    }

}
int main()
{
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= m; i++){
        int x, y;
        scanf("%d%d", &x, &y);
        edge[x].push_back(y);
    }
    for(int i = 1; i <= n; i++)
        scanf("%d", a + i);
    scanf("%d%d", &S, &P);

    for(int i = 1; i <= n; i++){
        if(!dfn[i]){
            tarjan(i);
        }
    }
    for(int i = 1; i <= P; i++){
        int x;
        scanf("%d", &x);
        isBar[bel[x]] = true;
    }
    for(int i = 1; i <= cnt; i++){
        // 这里无需在意重边
        dp[i] = 0;
        for(int u : vec[i]){
            for(int v : edge[u]){
                if(bel[v] != i){
                    dp[i] = max(dp[i], dp[bel[v]]);
                }
            }
        }

        if( ! isBar[i]){
            if(dp[i]) dp[i] += val[i];
        } 
        else{
            dp[i] += val[i];
        }
    }
    // for(int i = 1; i <= cnt; i++){
    //     printf("%d  %lld", vec[i][0], dp[i]);
    // }
    printf("%lld", dp[bel[S]]);
    return 0;
}
