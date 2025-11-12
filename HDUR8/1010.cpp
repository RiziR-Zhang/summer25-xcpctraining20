#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<vector>
#include<cassert>
using namespace std;

#define DEBUG
#define MINI
#define Rpl(i,a,b) for(int i = (a); i < (b); ++i)
#define Rep(i,a,b) for(int i = (a); i <= (b); ++i)
typedef long long LL;
typedef pair<int,int> pii;
#ifndef MINI
constexpr int mN = 200005;
#else
constexpr int mN = 25;
#endif
constexpr int nINF = -1e9;
int n, w[mN];
pii t[mN];
int fa[mN], dep[mN], sz[mN], hson[mN], top[mN], dfn[mN], clk;
int bias[mN];
vector<int> e[mN];
struct Node{
    int maxb, ans, lz;
    Node(int B = 0):maxb(B), ans(nINF), lz(0){}
}nd[mN];
void dfs1(int u, int Fa){
    fa[u] = Fa;
    dep[u] = dep[Fa] + 1;
    sz[u] = 1;
    hson[u] = 0;
    for(auto v: e[u]){
        if(v == Fa) continue;
        dfs1(v, u);
        sz[u] += sz[v];
        if(!hson[u] || sz[v] > sz[hson[u]]) hson[u] = v;
    }
}
void dfs2(int u, int Tp){
    dfn[u] = ++clk;
    bias[clk] = -dep[u] * 2;
    top[u] = Tp;
    if(hson[u]){
        dfs2(hson[u], Tp);
        for(auto v: e[u]){
            if(v == fa[u] || v == hson[u]) continue;
            dfs2(v, v);
        }
    }
}
struct SGT{
    Node nd[mN<<2];
    inline int lc(int p){return p << 1;}
    inline int rc(int p){return p << 1 | 1;}
    inline void umax(int &p, int q){if(p < q) p = q;}
    void PU(int p){
        nd[p].maxb = max(nd[lc(p)].maxb, nd[rc(p)].maxb);
        nd[p].ans = max(nd[lc(p)].ans, nd[rc(p)].ans);
        nd[p].lz = 0;
    }

    void assn(int p, int x = nINF, bool islz = 0){
        umax(nd[p].ans, x + nd[p].maxb);
        if(islz) umax(nd[p].lz, x);
    }
    void PD(int p){
        if(!nd[p].lz) return;
        umax(nd[lc(p)].ans, nd[p].lz + nd[lc(p)].maxb);
        umax(nd[lc(p)].lz, nd[p].lz);
        umax(nd[rc(p)].ans, nd[p].lz + nd[rc(p)].maxb);
        umax(nd[rc(p)].lz, nd[p].lz);
        nd[p].lz = 0;
    }
    void buildtree(int p, int l, int r){
        if(l == r){
            nd[p] = Node(bias[l]);
            return;
        }
        int mid = (l + r) >> 1;
        buildtree(lc(p), l, mid);
        buildtree(rc(p), mid + 1, r);
        PU(p);
    }
    int qry(int p, int l, int r, int ql, int qr){
        if(ql <= l && r <= qr){
            return nd[p].ans;
        }
        PD(p);
        int mid = (l + r) >> 1, ans = nINF;
        if(ql <= mid) umax(ans, qry(lc(p), l, mid, ql, qr));
        if(mid < qr) umax(ans, qry(rc(p), mid + 1, r, ql, qr));
        return ans; 
    }
    void upd(int p, int l, int r, int x, int ul, int ur){
        if(ul <= l && ur <= r){
            assn(p, x, 1);
            return;
        }
        PD(p);
        int mid = (l + r) >> 1;
        if(ul <= mid) upd(lc(p), l, mid, x, ul, ur);
        if(mid < ur) upd(rc(p), mid + 1, r, x, ul, ur);
        PU(p);
    }
}tr;
int totans;
void solve(int u){
    int res = nINF;
    while(u){
        int v = top[u];
        res = max(res, tr.qry(1, 1, n, dfn[v], dfn[u]));
        u = fa[v];
    }
    if(res > totans) totans = res;
    cout<<(totans + 1) / 2<<endl;
}
void upd(int u){
    int d0 = dep[u];
    while(u){
        int v = top[u];
        tr.upd(1, 1, n, d0, dfn[v], dfn[u]);
        u = fa[v];
    }
}
void ALLClear(){
    clk = 0;
    totans = 0;
    Rep(i, 1, n){
        e[i].clear();
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
        cin>>n;
        Rep(i, 1, n){
            cin>>w[i];
            t[i] = {w[i], i};
        }
        int u, v;
        Rpl(i, 1, n){
            cin>>u>>v;
            e[u].push_back(v);
            e[v].push_back(u);
        }
        sort(t + 1, t + n + 1);
        dfs1(1, 0);//u, fa
        dfs2(1, 1);//u, tp
        tr.buildtree(1, 1, n);
        Rep(i, 1, n){
            if(i == 1){
                cout<<(totans = 0)<<endl;
            }else{
                solve(t[i].second);
            }
            upd(t[i].second);
        }
        ALLClear();//clk, e
    }
    return 0;
}
