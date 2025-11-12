#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<vector>
#include<cassert>
using namespace std;

//#define DEBUG
#define Rpl(i,a,b) for(int i = (a); i < (b); ++i)
#define Rep(i,a,b) for(int i = (a); i <= (b); ++i)
typedef long long LL;
typedef pair<int,int> pii;
//constexpr int mN = ;

LL f3l, f2l, f1l, h,g,f;
constexpr LL U = (1 << 30) - 1;
void build(LL A, LL B, LL C){
    f3l = A & U, f2l = B & U, f1l = C & U;
}
LL gen(){
    g = f3l ^ ((f3l << 16) & U);
    h = g ^ (g >> 5);
    f = h ^ ((h << 1) & U) ^ f2l ^ f1l;
    f3l = f2l;
    f2l = f1l;
    f1l = f;
    return f;
}
void solve(){
    LL n, A, B, C;
    cin>>n>>A>>B>>C;
    build(A,B,C);
    bool st = 0;
    Rpl(i, 0, n){
        LL idx = i + gen() % (n - i);
#ifdef DEBUG
cout<<i<<','<<idx<<endl;
#endif
        if(idx != i) st ^= 1;
    }
    cout<<(int)st;
    Rep(ver, 2, n){
        LL l = gen() % n, r = gen() % n, x = gen() % n + 1;
        if(l > r) swap(l, r);
#ifdef DEBUG
cout<<l<<','<<r<<' '<<x<<endl;
#endif
        st ^= (1ll * (r - l) * x) & 1;
        cout<<(int)st;
    }
    cout<<endl;
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int tsk;
    cin>>tsk;
    while(tsk--){
        solve();
        // ALLClear();
    }
    return 0;
}
