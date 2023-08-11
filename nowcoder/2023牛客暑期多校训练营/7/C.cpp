#include <bits/stdc++.h>
using namespace std;
const int N = 2e6;
int n, k;
int b[N];
set<int> fix;
int ans = 0;
bool dfs(int l, int r, int k){
    if(k < 0 || l > r) return true;
    int pos = 0, num = 0;
    for(int i = l; i <= r; i++) {
        if((b[i]>>k) & 1) pos = i, num++;
    }
    if(num >= 2) return false;
    if(num == 0){
        
        if(dfs(l, r, k - 1)) return true;
        else return false;
    }
    if(num == 1){
        int posl, posr, numl, numr;
        posl = posr = numl = numr = 0;
        if(fix.count(k) == 0) fix.insert(k);
        for(int i = l; i <= pos - 1; i++) {
            
            if((b[i]>>(k - 1)) & 1) posl = i, numl++;
        }
        for(int i = pos + 1; i <= r; i++) {
            if((b[i]>>(k - 1)) & 1) posr = i, numr++;
        }
        if(numl >= 2 || numr >= 2) return false;
        else if(numl == 1 && numr == 1){
            fix.insert(k - 1);
            ans &= ~(1 << (k - 1));
        }
        else if(numl == 0 && numr == 1){
            fix.insert(k - 1);
            ans |= (1 << (k - 1));
        }
        else if(numl == 1 && numr == 0){
            fix.insert(k - 1);
            ans &= ~(1 << (k - 1));
        }
        else if(numl == 0 && numr == 0){
        }


        bool ok = true;
        if(!dfs(l, pos - 1, k - 1)) ok = false;
        if(!dfs(pos + 1, r, k - 1)) ok = false;
        if(ok) return true;
        else return false;
    }
    return true;// 无所谓
}
int main()
{
    int T;
    cin >> T;
    while(T--){
        fix.clear();
        ans = 0;
        cin >> n >> k;
        for(int i = 1; i <= n - 1; i++) {
            scanf("%d", b + i);
        }
        if(dfs(1, n - 1, 29)){
//             cout << "fix : ";
//             for(int x : fix){
//                 printf("%d  ", x);
//             }
//             puts("");
            vector<int> vec;
            for(int i = 29; i >= 0; i--){
                if(fix.count(i) == 0) vec.push_back(i);
            }
            if( k - 1 >= (1 << (int)vec.size()) ){
                puts("-1");
            }
            else{
                for(int i = (int)vec.size() - 1, j = 0; i >= 0; i --, j++){
                    if(((k - 1) >> i) & 1) ans |= (1 << vec[j]);
                }
                printf("%d ", ans);
                for(int i = 2; i <= n; i++){
                    ans = ans ^ b[i - 1];
                    printf("%d ", ans);
                }
                puts("");
            }
        }
        else {
            puts("-1");
        }

    }

    return 0;
}
/*
1
6 1
1 0 3 1 0 
*/