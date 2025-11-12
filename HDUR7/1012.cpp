#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<vector>
#include<cassert>
#include<map>
using namespace std;

#define DEBUG
#define Rpl(i,a,b) for(int i = (a); i < (b); ++i)
#define Rep(i,a,b) for(int i = (a); i <= (b); ++i)
typedef unsigned long long LL;
typedef pair<int,int> pii;
constexpr int mN = 200005;
constexpr LL bs = 998244353;
int dep[mN], sz[mN], hson[mN], val[mN], lfnum;
vector<int> son[mN], reson[mN];
struct batrie{
    int rt[mN], stk[mN * 2], tp, col[mN * 2], cnt, ed;
    bool fd;
    map<int,int> mp[mN * 2];
    vector<int> pre, suc;
    int apply(){
        return stk[tp--];
    }
    void del(int x){
        mp[x].clear();
        stk[++tp] = x;
        col[x] = 0;
    }
    void reInit(int num){
        int r = num * 2 + 1;
        while(--r){
            stk[++tp] = r;
        }
        rt[1] = apply();
    }
    void construct(int x, int Dep){
        mp[rt[x]][Dep] = -1;
        col[rt[x]] = rt[x];
        return;
    }
    void remark(int hson, int id){
        rt[hson] = id;
    }
    void unite(int u, int v){
        u = rt[u], v = rt[v];
        while(v != -1){
            pii s = (*mp[v].begin());
            if(mp[u].find(s.first) != mp[u].end()){
                mp[u][s.first] = apply();
            }
            u = mp[u][s.first];
            col[u] = col[v];
            del(v);
            v = s.second;
        }
    }
    void get(int u, int col0){
        int sson = 0, eg = 0;
        if(col[u] == col0) ed = u;
        else if(fd){
            pre.push_back(u);
        }else{
            suc.push_back(u);
        }
        for(auto s: mp[u]){
            int v = s.second;
            if(v == -1) continue;
            if(col[v] == col0){
                ed = v;
                fd = 1;
                sson = v;
                eg = s.first;
                get(v, col0);
                col[u] = col0;
            }else{
                if(fd) suc.push_back(s.first);
                else pre.push_back(s.first);
                get(v, col0);
                if(col[v] == col0) sson = v, eg = s.first;
            }
        }
        if(col[u] != col0) del(u);
        else{
            mp[u].clear();
            if(sson) mp[u][eg] = sson;
        }
    }
    void deal(int u, int col0){
        pii w = *mp[u].begin();
        mp[u].clear();
        for(auto ele: pre){
            mp[u][ele] = apply();
            u = mp[u][ele];
            col[u] = col0;
        }
        mp[u][w.first] = w.second;
        
        u = ed;
        int eg = mp[u].begin()->first;
        for(auto ele: suc){
            mp[u][eg] = apply();
            u = mp[u][eg];
            col[u] = col0;
            eg = ele;
        }
        mp[u][eg] = -1;
    }
    void deal(){

    }
    void transfer(int u){
        pre.clear();
        suc.clear();
        fd=0;
        get(rt[u], rt[u]);
        deal();
    }
}abtrie;
void dfspre(int u, int fa){
    dep[u] = dep[fa] + 1;
    sz[u] = 1;
    hson[u] = 1;
    for(auto v: son[u]){
        dfspre(v, u);
        if(!hson[u] || sz[v] > sz[hson[u]]){
            hson[u] = v;
        }
        sz[u] += sz[v];
    }
}
void dfsord(int u){
    if(!hson[u]){
        abtrie.construct(u, dep[u]);
        ++lfnum;
        return;
    }
    abtrie.remark(hson[u], u);
    dfsord(hson[u]);
    for(auto v: son[u]){
        if(v == hson[u]) continue;
        dfsord(v);
        abtrie.unite(u, v);
    }
    abtrie.transfer(u);
}
void print(int u, LL pre){
    pre = (pre * bs + val[u]);
    if(!hson[u]){
        cout<<pre<<endl;
        return;
    }
    for(auto v: reson[u]){
        print(v, pre);
    }
}
int m, fa[mN];
void solve(){
    cin>>m;
    Rep(i, 2, m){
        cin>>fa[i];
        son[fa[i]].push_back(i);
    }
    dfspre(1, 0);
    abtrie.reInit(m);
    dfsord(1);
    cout<<lfnum<<endl;
    print(1, 0);
}
void ALLClear(){
    
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
        ALLClear();//son, dep, sz, hson, lfnum, trie, reson
    }
    return 0;
}
