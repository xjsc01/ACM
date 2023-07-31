// Red and Blue and Green
// https://ac.nowcoder.com/acm/contest/57359/E
#include <bits/stdc++.h>
using namespace std;
int n, m;
const int N = 1.2e3;
array<int, 3> que[N * 2];
vector<int> edge[N*2];
int ans[N * 2];

struct BIT{
    int c[N];
    inline void add(int x, int d){
        for(; x <= n; x += x & (-x)){
            c[x] += d;
        }
    }
    inline int query(int x){
        int ans = 0;
        for(; x; x -= x & -x){
            ans += c[x];
        }
        return ans;
    }
    inline void clear(){
        for(int i = 0; i <= n; i++){
            c[i] = 0;
        }
    }
};
BIT b;
void dfs(int u){
    for(int v : edge[u]){
        dfs(v);
    }
    if(u == m + 1) return ;
    b.clear();
    int num = 0;
    int l = que[u][0], r = que[u][1];
    for(int i = r; i >= l; i--){
        num += b.query(ans[i] - 1);
        b.add(ans[i], 1);
    }
    if((num & 1) == que[u][2]) return ;
//     if(edge[u].size() <= 1) {
//         puts("-1");
//         exit(0);
//     }
    int son1 = edge[u][0];
    int son2 = edge[u][1];
    int p1 = que[son1][0];
    int p2 = que[son2][0];

    for(int i = que[son1][0]; i <= que[son1][1]; i++){
        if(ans[i] > ans[p1]) p1 = i;
    }
    for(int i = que[son2][0]; i <= que[son2][1]; i++){
        if(ans[i] < ans[p2]) p2 = i;
    }

    swap(ans[p1], ans[p2]);
}
signed main()
{
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= m; i++){
        int l, r, w;
        scanf("%d%d%d", &que[i][0], &que[i][1], &que[i][2]);
        if(que[i][0] == que[i][1] && que[i][2] == 1){
            puts("-1");
            exit(0);
        }
    }
    for(int i = 1; i <= n; i++){
        que[++m] = {i, i, 0};
    }
    sort(que + 1, que + 1 + m, 
        [&](const array<int, 3>&a, const array<int, 3>&b){
            if(a[0] ^ b[0]) return a[0] < b[0];
            return a[1] > b[1];
        }
    );
    que[m+1] = {1, n, 0};
    stack<int> st;
    st.push(m + 1);
    for(int i = 1; i <= m; i++){
        while(!st.empty() && que[i][1] > que[st.top()][1]) st.pop();
        edge[st.top()].push_back(i);
        st.push(i);
    }
    for(int i = 1; i <= n; i ++){
        ans[i] = i;
    }
    dfs(m + 1);
    for(int i = 1; i <= n; i ++){
        printf("%d ", ans[i]);
    }
    return 0;
}
