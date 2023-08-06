#include <bits/stdc++.h>
using namespace std;
const int N = 6e5;
int sum[N]; // 前缀异或和
int cnt[N][2]; // 前缀为i的地方的1或者0的个数
long long a[N];
int main()
{
    int T;
    cin >> T;
    while(T--)
    {
        int n, q;
        scanf("%d%d", &n, &q);
        for(int i = 1; i <= n; i++){
            scanf("%lld", a + i);
        }
        sum[0] = 0, cnt[0][1] = cnt[0][0] = 0;
        for(int i = 1; i <= n; i++){
            sum[i] = sum[i - 1] ^ (a[i] & 1);
            cnt[i][0] = cnt[i - 1][0] + ( (sum[i]) == 0);
            cnt[i][1] = cnt[i - 1][1] + ( (sum[i]) == 1);
        }
        for(int i = 1; i <= q; i++){
            int l, r, k;
            scanf("%d%d%d", &l, &r, &k);
            if(sum[r] != sum[l - 1]) {
                puts("NO");
                continue;
            }
            int tt = sum[r];
            if(cnt[r][tt] - cnt[l - 1][tt] >= k) puts("YES");
            else puts("NO");
        }
    }

    return 0;
}