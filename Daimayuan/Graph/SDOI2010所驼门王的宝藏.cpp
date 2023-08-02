// http://oj.daimayuan.top/course/23/problem/947
/*
在tarjan中得到的顺序是拓扑序的反序！
*/
#include <bits/stdc++.h>
using namespace std;
int n;
const int N = 5e5;
vector<int> edge[N];
int dfn[N], low[N], bel[N], idx;
bool ins[N]; 
stack<int> stk;
vector< vector<int> >scc;
int cnt;
vector<int> vec[N];
map<pair<int, int>, int> id;
map<int, int> rid, cid;// 表示某一行的新建的节点，这一个节点可以跳转到这一行的所有地方
// 如果这样搞的话，同一行就最多有2*C的边，否则可能会有C^2个边
vector<int> r[N], c[N];//表示这一行，这一列有哪些点
int ty[N];// 表示某一编号的点对应的传送门的类型
pair<int, int> pos[N];// 表示某一个编号的点的x，y坐标
int sz[N];// 连通块中不包含已经增加了的点的点的个数
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
            if(tt <= n) sz[cnt]++;
            vec[cnt].push_back(tt);
            bel[stk.top()] = cnt;
            ins[stk.top()] = false;
            stk.pop();
            if(tt == x) break;
        }
        
    }

}
int main()
{
    int R, C;//在题目中有限制，这里按照无限制来做
    scanf("%d%d%d", &n, &R, &C);
    for(int i = 1; i <= n; i++){
        int x, y, z;
        scanf("%d%d%d", &x, &y, &z);
        r[x].push_back(i);
        c[y].push_back(i);
        id[{x, y}] = i;
        ty[i] = z;
        pos[i] = {x, y};
    }
    int tot = n;// 已经有的编号
    for(int i = 1; i <= n; i++){
        if(ty[i] == 1){
            if(rid.count(pos[i].first) == 0){
                tot++;
                for(int u : r[pos[i].first]){
                    edge[tot].push_back(u);
                }
                rid[pos[i].first] = tot;
            }
            edge[i].push_back(rid[pos[i].first]);
        }
        else if(ty[i] == 2){
            if(cid.count(pos[i].second) == 0){
                tot++;
                for(int u : c[pos[i].second]){
                    edge[tot].push_back(u);
                }
                cid[pos[i].second] = tot;
            }
            edge[i].push_back(cid[pos[i].second]);
        }
        else{
            for(int dx = -1; dx <= 1; dx ++){
                for(int dy = -1; dy <= 1; dy++){
                    if(dx == 0 && dy == 0) continue;
                    if(id.count({pos[i].first + dx, pos[i].second + dy})){
                        edge[i].push_back(id[make_pair(pos[i].first + dx, pos[i].second + dy)]);
                    }
                }
            }
        }
    }
    for(int i = 1; i <= n; i++){
        if(!dfn[i]) tarjan(i);
    }
    static int dp[N];
    static int ans = 0;
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
        dp[i] += sz[i];
        ans = max(ans, dp[i]);
    }
    // for(int i = 1; i <= cnt; i++){
    //     printf("%d %d\t%d\n", vec[i][0], vec[i][1], dp[i]);
    // }
    cout << ans;
    return 0;
}
