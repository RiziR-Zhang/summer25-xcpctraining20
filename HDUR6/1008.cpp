#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<vector>
#include<cassert>
using namespace std;

#define DEBUG
#define Rpl(i,a,b) for(int i = (a); i < (b); ++i)
#define Rep(i,a,b) for(int i = (a); i <= (b); ++i)
typedef long long LL;
typedef pair<int,int> pii;
constexpr int mN = 1005, mM = 13;
int n, m, k;
LL a[mN][mM], mx[mM], psum[(1 << mM)|1], f[2][(1 << mM) | 1];
inline int lowbit(int S){return S ^ (-S);}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int _a = 0xbfbfbfbf, _b = 0xbfbfbfbf;
    cout<<_a<<' '<<(_a+_b)<<endl;
    int tsk;
    cin>>tsk;
    while(tsk--){
        cin>>n>>m>>k;
        memset(mx + 1, 0, sizeof(LL) * m);
        Rep(i, 1, n)Rep(j, 1, m){
            cin>>a[i][j];
            mx[j] = max(mx[j], a[i][j]);
        }
        if(k >= m){
            LL sum = 0;
            Rep(i, 1, m) sum += mx[i];
            cout<<sum<<endl;
            continue;
        }
        int U = (1 << m) - 1;
        memset(f[0], 0, sizeof(LL) *(1 << m));
        Rep(i, 1, n){
            int nw = i & 1, ls = (i - 1) & 1;
            f[nw][0] = 0;
            psum[0] = 0;
            int cnt = 0;
            Rep(S, 1, U){
                if(S == lowbit(S)) psum[S] = a[i][++cnt];
                else psum[S] = psum[S ^ lowbit(S)] + psum[lowbit(S)];
//                psum[S] = psum[S ^ lowbit(S)] + a[]
                f[nw][S] = psum[S];
                for(int T = S; T; T = (T - 1) & S){//subset
                for(int T = S; T <= U; T = (T + 1) | S)//
                    f[nw][S] = max(f[nw][S], f[ls][T] + psum[S ^ T]);
                }
            }
        }
            cout<<f[n & 1][U]<<endl;
    }
    return 0;
}
