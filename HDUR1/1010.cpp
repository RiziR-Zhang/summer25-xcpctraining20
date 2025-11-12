#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<vector>
#include<queue>
using namespace std;

#define DEBUG
#define Rpl(i,a,b) for(int i = (a); i < (b); ++i)
#define Rep(i,a,b) for(int i = (a); i <= (b); ++i)
typedef long long LL;
typedef pair<int,int> pii;
constexpr int mN = 2005;
int n, a[mN], grid[mN][mN], pre[mN][mN];
int findmid(int il, int ir){
    int l = 1, r = n, len = (ir - il + 1);
    while(l < r){
        int mid = (l + r) >> 1;
        if(pre[ir][mid] - pre[il - 1][mid] < (len + 1) / 2){
            l = mid + 1;
        }else{
            r = mid;
        }
    }
    return l;
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int tsk;
    cin>>tsk;
    while(tsk--){
        cin>>n;
        Rep(i, 1, n){
            cin>>a[i];
            grid[i][a[i]] = 1;
        }
        
        Rep(i, 1, n){
            Rep(v, 1, n){
                pre[i][v] = pre[i - 1][v] + pre[i][v - 1] - pre[i - 1][v - 1] + grid[i][v];
            }
        }
        LL ans(0);
        for(int i = 1; i <= n; ++i){
            for(int j = i; j <= n; j += 2){
                int mid = findmid(i, j);
                ans += 1ll * i * j * mid;
            }
        }
        cout<<ans<<endl;
        Rep(i, 1, n){
            grid[i][a[i]] = 0;
        }
    }
    return 0;
}
