#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 6e5;
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
        d[i] = -5;
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
signed  main()
{
    scanf("%lld%lld", &n, &m);
    for(int i = 1; i <= m; i ++){
        int x, a, b;
        scanf("%lld%lld%lld", &x, &a, &b);
        switch(x){
        case 1:
            edge[a].push_back({b, 0});
            edge[b].push_back({a, 0});
            break;
        case 2:
            edge[a].push_back({b, 1});
            break;
        case 3:
            edge[b].push_back({a, 0});
            break;
        case 4:
            edge[b].push_back({a, 1});
            break;
        case 5:
            edge[a].push_back({b, 0});
            break;
        }
        
    }
    for(int i = 1; i <= n; i++){
        edge[0].push_back({i, 1});
    }
    if(spfa(0))
    {
        int ans = 0;
        for(int i = 1; i <= n; i++){
            ans += d[i] - d[0];
        }
        // for(int i = 1; i <= n; i++){
        //     printf("%d  ", d[i] - d[0]);
        // }
        // puts("");
        cout << ans << "\n";
    }
    else{
        puts("-1");
    }
    return 0;
}