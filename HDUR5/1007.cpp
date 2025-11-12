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
constexpr int mN = 1000005;
constexpr LL mdN = 1e9 + 7;
int n, k;
LL fac[mN], ifac[mN];
LL qp(LL a, LL b){
    LL pw = 1;
    while(b){
        if(b & 1) pw = pw * a % mdN;
        a = a * a % mdN;
        b >>= 1;
    }
    return pw;
}
void mathinit(int len = 1000000){
    fac[0] = ifac[0] = 1;
    Rep(i, 1, len){
        fac[i] = fac[i - 1] * i % mdN;
    }
    ifac[len] = qp(fac[len], mdN - 2);
    for(int i = len - 1; i >= 1; --i){
        ifac[i] = ifac[i + 1] * (i + 1) % mdN;
    }
}
LL C(LL a, LL b){
    if(a < 0 || b < 0 || a < b) return 0;
    return fac[a] * ifac[b] % mdN * ifac[a - b] % mdN;
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int tsk;
    cin>>tsk;
    mathinit();
    while(tsk--){
        cin>>n>>k;
        k = n - k;
        LL E = 0;
        Rpl(v, 0, n){
            E = (E + 1ll * v * C(n - v - 1, k - 1)) % mdN;
#ifdef DEBUG
cout<<n - v - 1<<','<<k - 1<<":"<<C(n - v - 1, k - 1)<<endl;
#endif
        }
        cout<<E * qp(C(n, k), mdN - 2) % mdN<<endl;
    }
    return 0;
}
