#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<vector>
#include<cassert>
using namespace std;

//#define DEBUG
//#define MINI
#define Rpl(i,a,b) for(int i = (a); i < (b); ++i)
#define Rep(i,a,b) for(int i = (a); i <= (b); ++i)
typedef long long LL;
typedef pair<int,int> pii;
#ifndef MINI
constexpr int mN = 3005;
#else
constexpr int mN = 35;
#endif
constexpr LL mdN = 998244353;
int n, a[mN];
LL f[mN][mN], g[mN][mN];
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
        }
        f[0][0]=1;
        Rep(j,0,n)g[0][j]=1;
        // g[0][0] = 1;
        Rep(i, 1, n){
            LL pre = f[i][i] = g[i - 1][i];
            int premin = a[i];
            for(int j = i - 1; j >= 1; --j){
                if(a[j] < premin){
                    f[i][j] = g[i - 1][j];
                    premin = a[j];
                }else{
                    f[i][j] = 0;
                }
            }
            int sucmin = a[i];
            for(int j = i + 1; j <= n; ++j){
                if(a[j] < sucmin){
                    f[i][j] = g[i - 1][j];//(f[i - 1][j] + g[i - 1][i - 1]) % mdN;
                    sucmin = a[j];
                }else{
                    f[i][j] = 0;
                }
            }
            g[i][0] = 0;
            Rep(j, 1, n){
                g[i][j] = (g[i][j - 1] + f[i][j]) % mdN;
            }
            f[i][0]=0;
        }
        LL sum(0);
        Rep(i, 1, n){
            sum += f[n][i];
        }
        cout<<g[n][n]<<endl;
    }
    return 0;
}
