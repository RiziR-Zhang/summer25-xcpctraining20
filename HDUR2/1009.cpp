#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<vector>
#include<queue>
#include<cmath>
using namespace std;

#define DEBUG
//#define MINI
#define Rpl(i,a,b) for(int i = (a); i < (b); ++i)
#define Rep(i,a,b) for(int i = (a); i <= (b); ++i)
typedef long long LL;
typedef pair<int,int> pii;
#ifndef MINI
constexpr int mN = 100005;
#else
constexpr int mN = 25;
#endif
int n, B;
int deg[mN], a[mN];
vector<int> e[mN];
int fa[mN], sz[mN], dep[mN], hson[mN], top[mN], clk, t2a[mN], a2t[mN];
bool david[mN];
int rec[mN];
inline void addedge(int u, int v){
    e[u].push_back(v);
    ++deg[u];
    e[v].push_back(u);
    ++deg[v];
}
struct SGT{
    int nd[mN << 2];
    inline int lc(int p){return p << 1;}
    inline int rc(int p){return p << 1 | 1;}
    inline void pu(int p){
        nd[p] = max(nd[lc(p)], nd[rc(p)]);
    }
    void buildtree(int p, int l, int r){
        if(l == r){
            nd[p] = a[t2a[l]];
            return;
        }
        int mid = (l + r) >> 1;
        buildtree(lc(p), l, mid);
        buildtree(rc(p), mid + 1, r);
        pu(p);
    }
    void add(int p, int l, int r, int y, int z){
        if(l == r){
            nd[p] += z;
            return;
        }
        int mid = (l + r) >> 1;
        if(y <= mid){add(lc(p), l, mid, y, z);}
        else        {add(rc(p), mid + 1, r, y, z);}
        pu(p);
    }
    void add(int id, int dt){
        add(1, 1, n, a2t[id], dt);
    }
    int qr(int p, int l, int r, int sl, int sr){
        if(sl <= l && r <= sr){
            return nd[p];
        }
        int mid = (l + r) >> 1;
        int ans = 0;
        if(sl <= mid) ans = max(ans, qr(lc(p), l, mid, sl, sr));
        if(mid < sr)  ans = max(ans, qr(rc(p), mid + 1, r, sl, sr));
        return ans;
    }
    int qr(int anc, int son){
        return qr(1, 1, n, a2t[anc], a2t[son]);
    }
}tr;
void dfs1(int u = 1, int Fa = 0){
    fa[u] = Fa;
    sz[u] = 1;
    dep[u] = dep[Fa] + 1;
    hson[u] = 0;
    
    for(auto v: e[u]){
        if(v == Fa) continue;
        dfs1(v, u);
        sz[u] += sz[v];
        if(hson[u] == 0 || sz[hson[u]] < sz[v]){
            hson[u] = v;
        }
    }
}
void dfs2(int u = 1, int tp = 1){
    t2a[++clk] = u;
    a2t[u] = clk;
    top[u] = tp;
    if(hson[u] != 0){
        dfs2(hson[u], tp);
    }
    for(auto v: e[u]){
        if(v == fa[u] || v == hson[u]) continue;
        dfs2(v, v);
    }
}
void init(){
    B = sqrt(n / log2(n));
    dfs1();
    dfs2();
    tr.buildtree(1, 1, n);//real node
    Rep(i, 1, n){
        rec[i] = 0;
        david[i] = (deg[i] >= B);
    }
}
void modify(int x, int z){
    if(x != 1){
        a[fa[x]] += z;
        tr.add(fa[x], z);// real node
    }
    if(hson[x] != 0){
        a[hson[x]] += z;
        tr.add(hson[x], z);
    }
    if(david[x]){
        rec[x] += z;
    }else{
        for(auto v: e[x]){
            if(v != fa[x] && v != hson[x]){
                a[v] += z;
                tr.add(v, z);
            }
        }
    }
}
void solve(int x, int y){
    int ans = 0;
    while(top[x] != top[y]){
        if(dep[top[x]] < dep[top[y]]){
            swap(x, y);
        }
        ans = max(ans, tr.qr(top[x], x));//real node, dep_l < dep_r
        x = top[x];
        if(david[fa[x]]){
            ans = max(ans, a[x] + rec[fa[x]]);
        }
        x = fa[x];
    }
    if(dep[x] < dep[y]){
        swap(x, y);
    }
    ans = max(ans, tr.qr(y, x));//real node
    int lca = y;
    if(top[lca] == lca && david[fa[lca]]){
        ans = max(ans, a[lca] + rec[fa[lca]]);
    }
    cout<<ans<<endl;
//    spjudge(lca);
}
void ALLClear(){
    clk = 0;
    memset(deg + 1, 0, sizeof(int) * n);
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
    int Qr, opt, x, y, z;
    cin>>tsk;
    while(tsk--){
        cin>>n>>Qr;
        Rep(i, 1, n){
            cin>>a[i];
        }
        Rpl(i, 1, n){
            cin>>x>>y;
            addedge(x, y);//vector, deg, bi
        }
        init();
        while(Qr--){
            cin>>opt>>x>>y;
            if(opt == 1){
                solve(x, y);//jump, qr, enum
            }else{
                modify(x, y);//divide and solve
            }
        }
        ALLClear();//eg, deg, clk
    }
    return 0;
}
