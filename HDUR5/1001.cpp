#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<vector>
#include<cassert>
using namespace std;

#define DEBUG
//#define MINI
#define Rpl(i,a,b) for(int i = (a); i < (b); ++i)
#define Rep(i,a,b) for(int i = (a); i <= (b); ++i)
typedef long long LL;
typedef pair<LL,LL> pll;
#ifndef MINI
constexpr int mN = 100005;
#else
constexpr int mN = 25;
#endif
constexpr LL INF = 1e13;
int n, quen;
int clk, nwfa[mN], dep[mN], jmp[19][mN], lgt[mN << 1];
LL reward[mN], req[19][mN];
pll ene[mN], val[mN], que[mN << 1], st[19][mN << 1];
struct Node{LL a, toFa;}key[mN];
vector<int> e[mN], nwe[mN];

void dfs(int u, int fa){
    que[++quen] = val[u];
    for(auto v: e[u]){
        if(v == fa) continue;
        dfs(v, u);
        que[++quen] = pll(ene[u].first, u);
    }
}
void buildst(){
    lgt[0] = -1;
    Rep(i, 1, quen) lgt[i] = lgt[i >> 1] + 1;
    // Rep(i, 1, quen){
    //     st[0][i] = que[i];
    // }
    memcpy(st[0] + 1, que + 1, sizeof(pll) * quen);
    for(int k = 1; (1 << k) <= quen; ++k){
        for(int l = 1, r = (1 << k); r <= quen; ++l, ++r){
            st[k][l] = max(st[k - 1][l], st[k - 1][l + (1 << (k - 1))]);
        }
    }
}

inline void upd(int& Fa, int candd){
    if(!candd) return;
    if(!Fa) Fa = candd;
    if(val[candd] <= val[Fa]) Fa = candd;
}
pll qseq(int l, int r){
    int dep = lgt[r - l + 1];
    return max(st[dep][l], st[dep][r - (1 << dep) + 1]);
}
int qfa(int pos){
    pll bs = que[pos], res(INF, 0);
    if(qseq(1, pos) != bs){
        int l = 1, r = pos - 1;
        while(l < r){
            int mid = (l + r + 1) >> 1;
            if(qseq(mid, pos) == bs) r = mid - 1;
            else l = mid;
        }
        res = min(res, que[l]);
    }
    if(qseq(pos, quen) != bs){
        int l = pos + 1, r = quen;
        while(l < r){
            int mid = (l + r) >> 1;
            if(qseq(pos, mid) == bs) l = mid + 1;
            else r = mid;
        }
        res = min(res, que[l]);
    }
    return res.second;
}

void dfs2(int u){
    if(!nwfa[u]) dep[u] = 1;
    else dep[u] = dep[nwfa[u]] + 1;
    key[u].a = ene[u].first;
    reward[u] = ene[u].second;
    for(auto v: nwe[u]){
        dfs2(v);
        reward[u] += reward[v];
    }
    if(!nwfa[u]) key[u].toFa = 1e18;
    else key[u].toFa = max(key[nwfa[u]].a - reward[u], 0ll);//key[u].toFa <= key[nwfa[u]].a
}
void buildpw(){
    memcpy(jmp[0] + 1, nwfa + 1, sizeof(int) * n);
    Rep(i, 1, n){
        jmp[0][i] = nwfa[i];
        req[0][i] = key[i].toFa;
    }
    for(int p = 1; (1 << p) <= n; ++p){
        Rep(u, 1, n){
            if(dep[u] > (1 << p)){
                jmp[p][u] = jmp[p-1][jmp[p - 1][u]];
                req[p][u] = max(req[p - 1][u], req[p - 1][jmp[p - 1][u]]);
            } 
        }
    }
}
struct DSU{
    int fa[mN], sz[mN], nd[mN];
    void init(int len){
        Rep(i, 1, len){
            fa[i] = nd[i] = i;
            sz[i] = 1;
        }
    }
    int ffa(int x){return x == fa[x] ? x : (fa[x] = ffa(fa[x]));}
    int merge(int s, int f){
        int fu = ffa(s), fv = ffa(f);
        assert(fu != fv);
        int val = nd[fv], top = nd[fu];
        if(sz[fu] < sz[fv]) swap(fu, fv);
        fa[fv] = fu;
        sz[fu] += sz[fv];
        nd[fu] = val;
        return top;
    }
}dsu;
bool in[mN];
void buildtree(){
    dsu.init(n);
    vector<pll> tmp(n);
    Rep(i, 1, n) tmp[i - 1] = val[i];
    sort(tmp.begin(), tmp.end());
    memset(in + 1, 0, sizeof(bool) * n);
    Rep(i, 1, n){
        int u = tmp[i - 1].second;
        for(auto v: e[u]){
            if(!in[v]) continue;
            int sn = dsu.merge(v, u);
            nwfa[sn] = u;
        }
        in[u] = 1;
    }
    int rt = 0;
    Rep(i, 1, n){
        assert(nwfa[i] || !rt);
        if(!nwfa[i]) rt = i;
        nwe[nwfa[i]].push_back(i);
    }
    dfs2(rt);
    buildpw();
}
LL query(int x, LL lv){
    if(lv < key[x].a) return lv;
    for(int p = 20; p >= 0; --p){
        if(dep[x] - (1 << p) >= 1 && req[p][x] <= lv) x = jmp[p][x];
    }
    if(key[x].toFa <= lv) x = nwfa[x];
    return lv + reward[x];
}
void solve(){
    int Qr;
    cin>>n>>Qr;
    Rep(i, 1, n){
        cin>>ene[i].first;
    }
    Rep(i, 1, n){
        cin>>ene[i].second;
        val[i] = pll(ene[i].first, i);
    }
    int u, v;
    Rpl(i, 1, n){
        cin>>u>>v;
        e[u].push_back(v);
        e[v].push_back(u);
    }
    buildtree();//build: newfa[], dep[], reward[], (pii)key.a/toFa,
    // powLevel[u][p]: level need to **jump** 1 << p steps

    int x; LL initLvl;
    while(Qr--){
        cin>>x>>initLvl;
        cout<<query(x, initLvl)<<endl;//pow
    }
}
void ALLClear(){//e, fa, cnt, nwfa, quen
    Rep(i, 1, n){
        e[i].clear();
        nwe[i].clear();
        nwfa[i] = 0;
    }
    quen = 0;
}
//#define FILE
int main()
{
#ifdef FILE
freopen("1001.in","r",stdin);
freopen("1001.out","w",stdout);
#endif
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int tsk;
    cin>>tsk;
    while(tsk--){
        solve();
        ALLClear();
    }
#ifdef FILE
fclose(stdin);fclose(stdout);
#endif

    return 0;
}
