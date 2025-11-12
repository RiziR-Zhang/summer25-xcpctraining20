#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<vector>
#include<queue>
#include<cassert>
using namespace std;

#define DEBUG
//#define MINI
//#define FILE
#define Rpl(i,a,b) for(int i = (a); i < (b); ++i)
#define Rep(i,a,b) for(int i = (a); i <= (b); ++i)
typedef long long LL;
typedef pair<int,int> pii;
constexpr int mN = 100005, PRF = 8, mV = 1e7 + 5, stdV = 1e7;
LL ans, f[mN][1<<PRF], g[mN][1<<PRF];
int n, x, a[mN], fa[mN], U, st[mN];
bool ill[mN];
vector<int> e[mN];

bool npr[mV];
int prn, prl[mV / 5];
int divn, _p[PRF + 5], _q[PRF + 5];
void sieve(int len = stdV){
    Rep(i, 2, len){
        if(!npr[i]){
            prl[++prn] = i;
        }
        for(int j = 1; j <= prn && i * prl[j] <= len; ++j){
            npr[i * prl[j]] = 1;
            if(i % prl[j] == 0) break;
        }
    }
}
void decom(int x){
    int X = x;
    divn = 0;
    for(int i = 1; prl[i] * prl[i] <= x; ++i){
        if(x % prl[i] == 0){
            _p[++divn] = prl[i];
            _q[divn] = 0;
            while(x % prl[i] == 0){
                _q[divn]++;
                x /= prl[i];
            }
        }
    }
    if(x != 1) _p[++divn] = x, _q[divn] = 1;
    U = (1 << divn) - 1;
}
int gcd(int a, int b){
    return b ? gcd(b, a % b) : a;
}
void chk(){
    Rep(i, 1, n){
        st[i] = 0;
        ill[i] = (gcd(x, a[i]) != a[i]);
        if(ill[i]) continue;
        Rep(j, 1, divn){
            if(a[i] % _p[j] == 0){
                int cnt = 0;
                while(a[i] % _p[j] == 0){
                    a[i] /= _p[j];
                    cnt++;
                }
                if(cnt == _q[j]) st[i] |= (1 << (j - 1));
            }
        }
        assert(a[i] == 1);
    }
}
void dfs(int u){
    int now = st[u];
    if(!ill[u]){
        f[u][now] = 1;
        if(now == U) ans++;
    }
    for(auto v: e[u]){
        if(v == fa[u]) continue;
        fa[v] = u;
        dfs(v);
        if(!ill[u]){
//            ans += g[v][U ^ now];
            Rep(s, 0, U){
                ans += f[u][s] * g[v][U ^ s];
            }
            Rep(s, 0, U){
                f[u][s | now] += f[v][s];
            }
        }

    }
    if(!ill[u]){
    Rep(s, 0, U){
        for(int t = s; t <= U; t = (t + 1) | s){
            g[u][s] += f[u][t];
        }
    }
    }
    //no
}
void ALLClear(){
    Rep(i, 1, n){
        memset(f[i], 0, sizeof(LL) * (U + 1));
        memset(g[i], 0, sizeof(LL) * (U + 1));
        e[i].assign(0, 0);
    }
}
int main()
{
#ifdef FILE
    freopen("1007.in", "r", stdin);
    freopen("1007.txt", "w", stdout);
#endif
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int tsk;
    cin>>tsk;
    sieve();
    while(tsk--){
        cin>>n>>x;
        decom(x);
        for(int i = 1, u, v; i < n; ++i){
            cin>>u>>v;
            e[u].push_back(v);
            e[v].push_back(u);
        }
        Rep(i, 1, n){
            cin>>a[i];
        }
        chk();
        ans = 0;
        dfs(1);
        cout<<ans<<endl;
        ALLClear();
    }
#ifdef FILE
    fclose(stdin);
    fclose(stdout);
#endif
    return 0;
}
