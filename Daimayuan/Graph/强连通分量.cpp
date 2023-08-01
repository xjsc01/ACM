#include <bits/stdc++.h>
using namespace std;
int n, m;
const int N = 10;
//2e5;
vector<int> edge[N];
int dfn[N], low[N], bel[N], idx;
bool ins[N]; 
stack<int> stk;
vector< vector<int> >scc;
int cnt;
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
        vector<int> c;
        ++cnt;
        while(true){
            int tt = stk.top();
            c.push_back(stk.top());
            bel[stk.top()] = cnt;
            ins[stk.top()] = false;
            stk.pop();
            if(tt == x) break;
        }
        sort(c.begin(), c.end());//if need sort
        scc.push_back(c);
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
    for(int i = 1; i <= n; i++){
        if(!dfn[i]){
            tarjan(i);
        }
    }
    sort(scc.begin(), scc.end());
    for(auto a : scc){
        for(int b : a){
            printf("%d ", b);
        }
        puts("");
    }
    return 0;
}
