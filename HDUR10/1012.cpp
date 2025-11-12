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
constexpr int mN = 305;
int TOP;
LL mdN, C[mN][mN], stir2[mN][mN], fac[mN];
void mathinit(){
    C[0][0] = fac[0] = stir2[0][0] = 1;
    Rep(i, 1, TOP){
        fac[i] = fac[i - 1] * i % mdN;
        C[i][0] = 1;
        Rep(j, 1, i){
            C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % mdN;
            stir2[i][j] = (stir2[i - 1][j - 1] + stir2[i - 1][j] * j) % mdN;
        }
    }
}
inline LL A(int x, int y){
    if(x < 0 || y < 0 || x < y) return 0;
    return C[x][y] * fac[y] % mdN;
}
void solve(){
    cin>>TOP>>mdN;
    mathinit();
    Rep(n, 1, TOP){
        // f[0][0] = 1;
        // Rpl(i, 0, n){
        //     Rep(num, i != 0, i){
        //         f[i][num] %= mdN;
        //         f[i + 1][num + 1] += f[i][num];//unordered
        //         f[i + 1][num] += f[i][num] * num % mdN;//stir
        //     }
        // }
        LL ans = 0;
        Rep(k, 1, n){
            Rpl(p, 0, k){
                ans = (ans + stir2[n][k] * A(n - p - 1, p) % mdN * A(n - p - 1, k - p - 1)) % mdN;
            }
        }
        cout<<ans<<endl;
    }
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
