#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N = 3e3;
int n, k;
int a[N];
signed main()
{
    scanf("%lld%lld", &n, &k);
    int posSum = 0, maxv = -1.6e9;

    for(int i = 1; i <= n; i++){
        scanf("%lld", a + i);
        posSum += max(0ll, a[i]);
        maxv = max(maxv, a[i]);
    }
    if(k <= 0){
        if(maxv >= k) puts("0"), exit(0);
        else puts("-1"), exit(0);
    }
    else{
        if(posSum < k) puts("-1"), exit(0);
        if(maxv >= k) puts("0"), exit(0);
        // 这一句代码必须加上去，因为下面讨论的是区间大于等于2的情况
    }
    
    int ans = 1.3e9;
    for(int l = 1; l <= n; l++){
        if(a[l] <= 0) continue;
        priority_queue<int, vector<int>, greater<int> > p1;
        priority_queue<int> p2;
        int cnt = 1;
        int s = a[l];
        for(int r = l + 1; r <= n; r++){
            if(a[r] > 0){
                cnt++, s += a[r];
            }
            else{
                p2.push(a[r]);
                while(p1.size() && p2.size() && p1.top() < p2.top()){
                    int x = p1.top();
                    int y = p2.top();
                    s += y - x;
                    p1.pop(), p2.pop();
                    p1.push(y), p2.push(x);
                }
                continue;

            }
            while(p2.size() && s + p2.top() >= k){
                s += p2.top();
                cnt++;
                p1.push(p2.top());
                p2.pop();
            }
            if(s >= k) 
                ans = min(ans, 2 * (r - l) - cnt + 1);
        }
    }
    cout << ans;
    return 0;
}
