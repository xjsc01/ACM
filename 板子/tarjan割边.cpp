#include <bits/stdc++.h>
using namespace std;
int n, m;
const int N = 1.1e5;
const int M = 2.1e5;
vector<pair<int, int>>edge[N];//无向边
bool bridge[M];
int dfn[N], low[N], idx;
int theNumOfBridge = 0;
// 在边双中，dfs树仅仅有树边以及返祖边
void dfs(int x, int id1){// idx1表示的是边的编号（为了解决重边）
    //cout << x << "  ";
    dfn[x] = low[x] = ++idx;
    for(auto [y, id2] : edge[x]){
        if(!dfn[y]){
            dfs(y, id2);
            low[x] = min(low[x], low[y]);
            if(low[y] == dfn[y]) {
                bridge[id2] = true;
                theNumOfBridge++;
            }
        }
        else{
            if(id2 != id1){
                low[x] = min(low[x], low[y]);
            }
        }
    }
}
int main()
{
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= m; i++){
        int x, y;
        scanf("%d%d", &x, &y);
        edge[x].push_back({y, i});
        edge[y].push_back({x, i});
    }
    dfs(1, -1);
    printf("%d\n", theNumOfBridge);
    for(int i = 1; i <= m; i++){
        if(bridge[i]) printf("%d ", i);
    }
    return 0;
}
