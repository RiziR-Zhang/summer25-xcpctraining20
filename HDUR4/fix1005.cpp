#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<vector>
#include<queue>
#include<bitset>
using namespace std;

#define DEBUG
#define Rpl(i,a,b) for(int i = (a); i < (b); ++i)
#define Rep(i,a,b) for(int i = (a); i <= (b); ++i)
typedef long long LL;
constexpr int mN = 305, mS = 305;
constexpr LL mdN = 998244353;
int n, sonn[mN], fa[mN], lfson[mN];
char s[mS];
vector<int> son[mN];
bitset<mN> visd;
LL inv[mN], dp[mN][mS];
LL qp(LL a, LL b){
    LL pw = 1;
    while(b){
        if(b & 1) pw = pw * a % mdN;
        a = a * a % mdN; b >>= 1;
    }
    return pw;
}
void mathinit(int len = 300){
    vector<LL> fac(len + 1), ifac(len + 1);
    fac[0] = ifac[0] = 1;
    for(int i = 1; i <= len; ++i) fac[i] = fac[i - 1] * i % mdN;
    ifac[len] = qp(fac[len], mdN - 2);
    for(int i = len - 1; i; --i) ifac[i] = ifac[i + 1] * (i + 1) % mdN;
    Rep(i, 1, len) inv[i] = ifac[i] * fac[i - 1] % mdN;
}
int que[mN], quelen;
void dfs(int u){
    que[++quelen] = u;
    for(auto v: son[u]){
        dfs(v);
    }
}
void solve(){
    cin>>n>>s;
    int len = strlen(s);
    Rep(i, 1, n){
        cin>>sonn[i];
        son[i].resize(sonn[i]);
        Rpl(j, 0, sonn[i]){
            cin>>son[i][j];
            fa[son[i][j]] = i;
        }
    }
    int rt = 0;
    Rep(i, 1, n){
        if(sonn[i] == 0) lfson[fa[i]]++;
        if(fa[i] == 0) rt = i;
    }

    int now = 0;
    for(; now < len && s[now] != 'D'; ++now);
    if(n == 1 || now == len){
        cout<<rt<<endl;
        return;
    }

    dfs(rt);
    dp[rt][now] = 1;
    LL ans(0);
    Rep(i, 1, n){
        int u = que[i], lf = lfson[u], br = sonn[u] - lf;
        Rpl(t, 0, len){
            if(!dp[u][t]) continue;
            visd.reset();
            int nowId = 0, visNum = 0;
            LL dpVal = dp[u][t];
            Rpl(tt, t + 1, len){
                if(s[tt] == 'L'){if(nowId > 0) nowId--;}
                else if(s[tt] == 'R'){if(nowId + 1 < sonn[u]) nowId++;}
                else{
                    if(!visd[nowId]){
                        visd[nowId] = 1;
                        for(auto v: son[u]){
                            if(sonn[v] != 0){
                                dp[v][tt] = (dp[v][tt] + dpVal * inv[sonn[u] - visNum]) % mdN;
                            }
                        }
                        dpVal = dpVal * inv[sonn[u] - visNum] % mdN * (lf - visNum) % mdN;
                        visNum++;
                        if(dpVal == 0) break;
                    }
                }
            }
            if(dpVal > 0){
                if(visd[nowId]){
                    for(auto v: son[u]){
                        if(sonn[v] == 0){
                            ans = (ans + dpVal * v % mdN * inv[lf]) % mdN;
                        }
                    }                    
                }else{
                    for(auto v: son[u]){
                        if(sonn[v] == 0){
                            ans = (ans + dpVal * v % mdN * inv[lf] % mdN * (lf - visNum) % mdN * inv[sonn[u] - visNum]) % mdN;
                        }else{
                            ans = (ans + dpVal * v % mdN * inv[sonn[u] - visNum]) % mdN;
                        }
                    }                    
                }
            }
        }
    }
    cout<<ans<<endl;
}
inline void ALLClear(){
    memset(lfson, 0, sizeof(int) * (n + 1));
    memset(fa, 0, sizeof(int) * (n + 1));
    Rep(i, 1, n){
        memset(dp[i], 0, sizeof(dp[i]));
    }
    quelen = 0;
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
        solve();
        ALLClear();
    }
    return 0;
}
