#include <bits/stdc++.h>
using namespace std;
const int N = 4.1e5;
const int M = 4.1e5;
int n, m;
vector<int> edge[N];
int dfn[N], low[N], idx;
vector<int > ss[N];
int cnt = 0;
stack<int> stk;
bool cut[N];
void dfs(int x, int fa)
{
    //cout << x << "  ";
    stk.push(x);
    int ch = 0;// 表示子儿子的个数
    dfn[x] = low[x] = ++idx;
    for(int y : edge[x]){
        if(!dfn[y]){
            dfs(y, x);
            ch ++;
            low[x] = min(low[x], low[y]);
            if(low[y] >= dfn[x]) { // low的判断条件
                cut[x] = true;
                cnt ++;
                ss[cnt].clear();
                ss[cnt].push_back(x);
                while(1){
                    int tt = stk.top();
                    stk.pop();
                    ss[cnt].push_back(tt);
                    if(tt == y) {
                        
                        break;
                    }
                }
            }
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
    int T = 0;
    while(true){
        scanf("%d", &m);
        if(m == 0) break;
        for(int i = 1; i <= n; i++) {
            edge[i].clear();
            dfn[i] = 0;
            low[i] = 0;
            cut[i] = false;
        }
        idx = 0;
        cnt = 0;
        {
            stack<int> tmp;
            tmp.swap(stk);
        }
        n = 0;
        for(int i = 1; i <= m; i++){
            int x, y;
            scanf("%d%d", &x, &y);
            edge[x].push_back(y);
            edge[y].push_back(x);
            n = max({n, x, y});
        }

        dfs(1, 0);
        typedef unsigned long long ull;
        ull ans1 = 0, ans2 = 1;
        for(int i = 1; i <= cnt; i++){
            int tt = 0;// 计算这一个点双连通分量缩点之后是不是叶子
            for(int u : ss[i]){
                if(cut[u]) tt++;
            }
            if(tt == 1){
                ans1 ++;
                ans2 *= (ull)(ss[i].size() - 1);
            }
        }
        std::printf("Case %d: ", ++T);

    

        if(cnt == 1){
            cout << 2 << " " << (ull)n * (n - 1)/2;
        }
        else{
            cout << ans1 << ' ' << ans2;
        }
        puts("");
    }
    
    return 0;
}