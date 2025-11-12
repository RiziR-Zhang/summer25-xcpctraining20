#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<vector>
#include<map>
#include<cassert>
#include<set>
using namespace std;

//#define DEBUG
#define Rpl(i,a,b) for(int i = (a); i < (b); ++i)
#define Rep(i,a,b) for(int i = (a); i <= (b); ++i)
typedef long long LL;
typedef pair<int,int> pii;
constexpr int mN = 200005;
int n, fa[mN], hson[mN], sz[mN];
pii dom[mN];
vector<int> e[mN];
struct Node{
    int fa, sz, sdeg;
    bool deg;
    Node(int id = 0): fa(id), sz(id != 0), sdeg(0), deg(0){}
};
struct DSU{
    Node nd[mN];
    int blkAdd;
    multiset<pii> domList;
    void init(int len){
        Rep(i, 1, len){nd[i] = Node();}
        blkAdd = 0;
    }
    void clear(){
        for(auto x: domList){
            nd[x.first] = Node();
            nd[x.second] = Node();
        }
        blkAdd = 0;
        domList.clear();
    }
    int ffa(int x){
        return nd[x].fa == x ? x : (nd[x].fa = ffa(nd[x].fa));
    }
    inline int count(int x){assert(x % 2 == 0);return max(x / 2, 1);}
    bool mg(int u, int v){
        assert(nd[u].fa != 0);assert(nd[v].fa != 0);

        int fu = ffa(u), fv = ffa(v);
        if(fu == fv){
            blkAdd -= count(nd[fu].sdeg);
        }else{
            blkAdd -= count(nd[fu].sdeg) + count(nd[fv].sdeg);
        }
        nd[fu].sdeg += (nd[u].deg ^ 1) - nd[u].deg;
        nd[u].deg ^= 1;
        nd[fv].sdeg += (nd[v].deg ^ 1) - nd[v].deg;
        nd[v].deg ^= 1;

        if(fu == fv){
            blkAdd += count(nd[fu].sdeg);
            return 0;
        }
        if(sz[fu] < sz[fv]) swap(fu, fv);
        nd[fv].fa = fu;
        nd[fu].sz += nd[fv].sz;
        nd[fu].sdeg += nd[fv].sdeg;
        blkAdd += count(nd[fu].sdeg);
        return 1;
    }
    void ins(pii eg){
        domList.insert(eg);
        int u = eg.first, v = eg.second;
        if(!nd[u].fa) nd[u] = Node(u), blkAdd++;
        if(!nd[v].fa) nd[v] = Node(v), blkAdd++;
        mg(u, v);
    }
}dsu[20];
void dfspre(int u){
    sz[u] = 1;
    hson[u] = 0;
    for(auto v: e[u]){
        if(v == fa[u]) continue;
        fa[v] = u;
        dfspre(v);
        if(!hson[u] || sz[v] > sz[hson[u]]){
            hson[u] = v;
        }
        sz[u] += sz[v];
    }
}
int ans[mN], len;

void dfssolve(int u, int mpid){
    assert(mpid < 19);
    if(hson[u]){
        int hs = hson[u];
        dfssolve(hs, mpid);
        for(auto v: e[u]){
            if(v == fa[u] || v == hs) continue;
            ++len;
            dfssolve(v, len);
            for(auto dompair: dsu[len].domList){
                dsu[mpid].ins(dompair);//.mpins(dompair);
            }
            dsu[len--].clear();
        }
    }
    dsu[mpid].ins(dom[u]);
    ans[u] = dsu[mpid].blkAdd;//\sum_{component} \max{oddnum/2, 1}
}
//#define FILE
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
#ifdef FILE
freopen("A.in","r",stdin);
freopen("A.out","w",stdout);
int tsk;
cin>>tsk;
while(tsk--){
#endif

    cin>>n;
    Rep(i, 1, n){
        cin>>dom[i].first;
    }
    Rep(i, 1, n){
        cin>>dom[i].second;
    }
    int u, v;
    Rpl(i, 1, n){
        cin>>u>>v;
        e[u].push_back(v);
        e[v].push_back(u);
    }
    len = 1;
    dfspre(1);
    Rpl(i, 1, 20) dsu[i].init(n);
    dfssolve(1, len);
    Rep(i, 1, n){
        cout<<ans[i]<<' ';
    }
    cout<<endl;
#ifdef FILE
dsu[1].clear();
Rep(i, 1, n) e[i].clear();
}
fclose(stdin);fclose(stdout);
#endif

    return 0;
}
