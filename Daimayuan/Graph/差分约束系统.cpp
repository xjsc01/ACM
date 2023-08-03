#include <bits/stdc++.h>
using namespace std;
const int N = 6e3;
vector<pair<int, int> > edge[N];
int n, m;
queue<int> q;
int inq[N];
int cnt[N]; // 记录是否有负环
int d[N];
bool spfa(int yhy){
    while(q.size()) q.pop();
    for(int i = 1; i <= n; i++){
        inq[i] = 0;
        cnt[i] = 0;
        d[i] = -1;
    }
    q.push(yhy);
    inq[yhy];
    while(q.size()){
        int x = q.front();
        q.pop();
        inq[x] = false;
        for(auto[y, w] : edge[x]){
            if(d[y] < d[x] + w){
                d[y] = d[x] + w;
                cnt[y]++;
                if(cnt[y] > n + 1) //由于有超级原点
                    return false;
                if(!inq[y]){
                    inq[y] = true;
                    q.push(y);
                }
            }
        }
    }
    return true;
}
int main()
{
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= m; i ++){
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        edge[u].push_back({v, -w});
    }
    for(int i = 1; i <= n; i++){
        edge[0].push_back({i, 0});
    }
    if(spfa(0))
    {
        for(int i = 1; i <= n; i++){
            printf("%d ", d[i] - d[0]);
        }
    }
    else{
        puts("-1");
    }
    return 0;
}