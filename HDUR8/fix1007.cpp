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
constexpr int mN = 100005, mL = 19, stdL = 17;
constexpr LL mdN = 998244353;
int n, m;
struct DSU{
    int sz[mN * stdL * 2], fa[mN * stdL * 2];
    int ffa(int u){
        return fa[u] == u ? u : (fa[u] = ffa(fa[u]));
    }
    bool merge(int u, int v){
        u = ffa(u), v = ffa(v);
        if(u == v) return 0;
        if(sz[u] < sz[v]) swap(u, v);
        sz[u] += sz[v];
        fa[v] = u;
        return 1;
    }
    bool detect(int u, int v){
        return ffa(u) == ffa(v);
    }
    void init(int len){
        Rep(i, 1, len){
            sz[i] = 1;
            fa[i] = i;
        }
    }
}dsu;
vector<int> eg[mN * stdL * 2];
int col[mN], blk, s, bias[mL][2];
bool vis[mN * stdL * 2];
void buildDSU(int n){
    s = n;
    bias[0][0] = bias[0][1] = 0;
    for(int b = 1; (1 << b) < n; ++b){
        bias[b][0] = s;
        bias[b][1] = s + (n - (1 << b) + 1);
        s += (n - (1 << b) + 1) * 2;
    }
    dsu.init(s);
}
void spMerge(int l, int len, int r){
    assert(l + len - 1 < r - len + 1);
    for(int b = 0, pw = 1; len; ++b, pw <<= 1){
        if(len & pw){
            int _l = bias[b][0] + l, _r = bias[b][1] + (r - pw + 1);
            if(dsu.merge(_l, _r)){
                eg[_l].push_back(_r);
                eg[_r].push_back(_l);
            }
            len ^= pw;
            l += pw;
            r -= pw;
        }
    }
}
void dfs(int b, int isRev, int l){
    int u = bias[b][isRev] + l;
    vis[u] = 1;
    for(auto v: eg[u]){
        if(vis[v]) continue;
        int downv = v - bias[b][isRev^1] + bias[b - 1][isRev^1];
        int su = bias[b - 1][isRev] + l,
            sv = downv + (1 << (b - 1));
        if(dsu.merge(su, sv)){
            eg[su].push_back(sv);
            eg[sv].push_back(su);
        }
        su = bias[b - 1][isRev] + l + (1 << (b - 1)),
        sv = downv;
        if(dsu.merge(su, sv)){
            eg[su].push_back(sv);
            eg[sv].push_back(su);
        }
        dfs(b, isRev ^ 1, v - bias[b][isRev ^ 1]);
    }
}
void lnk(int u){
    col[u] = blk;
    for(auto v: eg[u]){
        if(col[v]) continue;
        lnk(v);
    }
}
void pdDSU(){
    int b = 0;
    while((1 << b) < n) ++b;
    for(--b; b > 0; --b){
        int pw = 1 << b;
        for(int l = 1, r = 1 << b; r <= n; ++l, ++r){
            if(!vis[bias[b][0] + l]){
                // ++blk;
                dfs(b, 0, l);
            }
            if(!vis[bias[b][1] + l]){
                dfs(b, 1, l);
            }
            eg[bias[b][0] + l].clear();
            eg[bias[b][1] + l].clear();
        }
    }
    Rep(i, 1, n){
        if(!col[i]){
            ++blk;
            lnk(i);
        }
        eg[i].clear();
    }
}
LL qp(LL a, LL b){
    LL pw = 1;
    while(b){
        if(b & 1) pw = pw * a % mdN;
        a = a * a % mdN;
        b >>= 1;
    }
    return pw;
}
void print(){
    cout<<qp(26ll, blk)<<endl;
    Rep(rk, 1, 20){
        Rep(i, 1, n){
            if(col[i] == blk){
                cout<<char('a' + rk - 1);
            }else{
                cout<<'a';
            }
        }
        cout<<endl;
    }
}
void solve()
{
    cin>>n>>m;
    buildDSU(n);
    int l, r;
    while(m--){
        cin>>l>>r;
        if(l == r) continue;
        int len = (r - l + 1) / 2;
        spMerge(l, len, r);
    }
    pdDSU();
    print();
}
void ALLClear()
{
    memset(col + 1, 0, sizeof(int) * n);
    memset(vis + 1, 0, sizeof(bool) * s);
    blk = 0;
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
        ALLClear();
    }
    return 0;
}
