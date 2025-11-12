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
constexpr int mN = 200005;
constexpr LL mdN = 998244353;
int n, a[mN];
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int tsk;
    cin>>tsk;
    while(tsk--){
        cin>>n;
        int l = 0, r = 0, L = n, R = 0;
        LL sum = 0;
        Rep(i, 1, n){
            cin>>a[i];
            sum += a[i];
            if(a[i] && l == 0) l = i;
            if(a[i]) r = i;
            if(a[i] != 0) L = min(L, a[i]);
            R = max(R, a[i]);
        }
        cout<<sum<<' ';
        if(R == 0){
            cout<<(1ll * n * (n + 1) / 2) % mdN * (n + 1) % mdN * (n + 1) % mdN<<endl;
        }else{
            cout<<1ll * l * (n - r + 1) % mdN * (n - R + 1) % mdN * (max(L, 1) + n + 1) % mdN<<endl;
        }
    }
    return 0;
}
