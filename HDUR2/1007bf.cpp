#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<vector>
#include<queue>
using namespace std;

#define DEBUG
#define FILE
#define Rpl(i,a,b) for(int i = (a); i < (b); ++i)
#define Rep(i,a,b) for(int i = (a); i <= (b); ++i)
typedef long long LL;
typedef pair<int,int> pii;
constexpr int mN = 15, mV = 1005;
constexpr LL mdN = 1e9+7;
int n, R, a[mN];
LL f[mN][mV];
void solve(){
    cin>>n>>R;
    Rep(i, 1, n){
        cin>>a[i];
    }
    for(int i = n - 1; i >= 1; --i){
        a[i] = max(a[i], a[i + 1]);
    }
    Rep(v, a[1], R) f[1][v] = 1;
    Rep(i, 2, n){
        Rep(v, a[i], R){
            f[i][v] = 0;
            Rep(w, max(v, a[i - 1]), R){
                f[i][v] += f[i - 1][w];
            }
            f[i][v] %= mdN;
        }
    }
    LL ans = 0;
    Rep(v, a[n], R){
        ans += f[n][v];
    }
    cout<<ans % mdN<<endl;
}
int main()
{
#ifdef FILE
    freopen("1007.in", "r", stdin);
    freopen("1007bf.out", "w", stdout);
#endif
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int tsk;
    cin>>tsk;
    while(tsk--){
        solve();
    }
#ifdef FILE
    fclose(stdin);
    fclose(stdout);
#endif
    return 0;
}
