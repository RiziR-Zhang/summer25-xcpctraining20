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
constexpr int mN = 425;
LL a[mN], pre[mN];
struct Node{
    LL imb, cost;
}dp[mN][mN][mN];
void tomin(LL& x, LL y){
    if(x == -1 || y < x) x = y;
}
int main()
{
#ifdef FILE
    freopen("I.in", "r", stdin);
    freopen("Ibf.out", "w", stdout);
#endif
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int tsk;
    cin>>tsk;
    while(tsk--){
        int n;
        cin>>n;
        pre[0] = 0;
        Rep(i, 1, n){
            cin>>a[i];
            pre[i] = pre[i-1] + a[i];
        }
        for(int l = 1, r = 2; r <= n; ++l, ++r){
            int log2L = 1;
            while((1ll << log2L) < a[l] + a[r]) ++log2L;
            dp[l][r][l] = {llabs(a[l] - a[r]), 
                           min(a[l], a[r]) * log2L};
        }
        Rep(len, 3, n){for(int l = 1, r = len; r <= n; ++l, ++r){Rpl(m, l, r){
                    int log2L = 0;
                    while((1ll << log2L) < pre[r] - pre[l - 1]) ++log2L;
                    dp[l][r][m].imb = llabs((pre[r] - pre[m]) - (pre[m] - pre[l - 1]));
                    LL fl = -1;
                    if(m == l){
                        fl = 0;
                    }else{
                        Rpl(lm, l, m){
                            if(dp[l][m][lm].imb <= dp[l][r][m].imb){
                                tomin(fl, dp[l][m][lm].cost);
                            }
                        }
                    }
                    LL fr = -1;
                    if(m + 1 == r){
                        fr = 0;
                    }else{
                        Rpl(mr, m + 1, r){
                            if(dp[m][r][mr].imb <= dp[l][r][m].imb){
                                tomin(fr, dp[m + 1][r][mr].cost);
                            }
                        }
                    }
                    if(fl == -1 || fr == -1)
                        dp[l][r][m].cost = -1;
                    else
                        dp[l][r][m].cost = fl + fr + min(pre[r] - pre[m], pre[m] - pre[l - 1]) * log2L;
        }}}
        Rpl(i, 1, n){
            cout<<dp[1][n][i].cost<<' ';
        }
        cout<<endl;
    }
#ifdef FILE
fclose(stdin);
fclose(stdout);
#endif
    return 0;
}
