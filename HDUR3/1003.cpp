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
constexpr int mN = 1000005, stdN = 1000001;
constexpr LL mdN = 1e9 + 7;
LL fac[mN], ifac[mN];
LL qpow(LL a, LL b){
    LL pw = 1;
    while(b){
        if(b & 1) pw = pw * a % mdN;
        a = a * a % mdN;
        b >>= 1;
    }
    return pw;
}
inline LL inv(LL x){
    return qpow(x, mdN - 2);
}
inline void mathinit(int len = stdN){
    fac[0] = ifac[0] = 1;
    Rep(i, 1, len){
        fac[i] = fac[i - 1] * i % mdN;
    }
    ifac[len] = inv(fac[len]);
    for(int i = len - 1; i >= 1; --i){
        ifac[i] = ifac[i + 1] * (i + 1) % mdN;
    }
}
inline LL C(LL p, LL q){
    return fac[p] * ifac[q] % mdN * ifac[p - q] % mdN;
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int tsk;
    cin>>tsk;
    mathinit();
    LL n, m, c, d;
    while(tsk--){//ans = \sum_{index} {m-1\choose k-1}{n+1\choose k}b^{2k}a^{m+n+1-2k}
                    // = \sum_{index} ...(d/c)^{2k} (c/c+d)^{m+n+1}
        cin>>n>>m>>c>>d;
        LL base = qpow(c * inv(c + d) % mdN, m + n + 1);
        LL frac = qpow(d * inv(c) % mdN, 2);
        LL fpow = frac;
        if(m == 0){
            cout<<base<<endl;
            continue;
        }
        if(c == 0){
            if(n + 1 == m) cout<<1<<endl;
            else cout<<0<<endl;
            continue;
        }
        if(d == 0){
            if(m == 0) cout<<1<<endl;//cannot reach
            else cout<<0<<endl;
            continue;
        }
        LL ans = 0;
        for(int k = 1, top = min(m, n + 1); k <= top; ++k){
            ans = (ans + C(m - 1, k - 1) * C(n + 1, k) % mdN * fpow % mdN * base) % mdN;
            fpow = fpow * frac % mdN;
        }
        cout<<ans<<endl;
    }
    return 0;
}
