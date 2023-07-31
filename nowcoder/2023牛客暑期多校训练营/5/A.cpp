#include <bits/stdc++.h>
using namespace std;
#define int long long 
int n, m;
const int N = 6e5;
array<int, 3> que[N];
int a[N];
int now = 0;
int s[N];
int val[N];
int tot[N];
int ans[N];

template<class T>
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
};
BIT<int> b;
signed main()
{
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= n; i++){
        scanf("%d", a + i);
    }
    for(int i  = 1; i <= n; i++){
        val[i] = b.query(a[i] - 1);
        b.add(a[i], 1);
    }
    for(int i = 1; i <= m; i++){
        scanf("%d%d", &que[i][0], &que[i][1]);
        que[i][2] = i;
    }
    const int B = sqrt(n);
    sort(que+1, que + 1 + m, [&](const array<int, 3>& a, const array<int, 3>& b){
        int aFrom = (a[0] - 1)/B + 1;
        int bFrom = (b[0] - 1)/B + 1;
        if(aFrom ^ bFrom) return aFrom < bFrom;
        return (aFrom&1) ? a[1] < b[1] : a[1] > b[1];
    }
    );
    auto addl = [&] (int x){
        now += s[a[x]] - val[x] * tot[a[x]];
        tot[a[x]]++;
        s[a[x]] += val[x];
    };
    auto dell = [&] (int x){
        tot[a[x]]--;
        s[a[x]] -= val[x];
        now -= s[a[x]] - val[x] * tot[a[x]];
    };
    auto addr = [&] (int x){
        now += val[x] * tot[a[x]] - s[a[x]];
        tot[a[x]] ++;
        s[a[x]] += val[x];
    };
    auto delr = [&] (int x){
        tot[a[x]] --;
        s[a[x]] -= val[x];
        now -= val[x] * tot[a[x]] - s[a[x]];
    };
    int L = 1, R = 0;
    for(int i = 1; i <= m; i++){
        while(L > que[i][0]) L--, addl(L);
        while(R < que[i][1]) R++, addr(R);
        while(L < que[i][0]) dell(L), L++;
        while(R > que[i][1]) delr(R), R--;
        ans[que[i][2]] = now;
        //printf("%d %d %d \n", L, R, now);
    }
    for(int i = 1; i <= m; i++){
        printf("%d\n", ans[i]);
    }
    return 0;
}
