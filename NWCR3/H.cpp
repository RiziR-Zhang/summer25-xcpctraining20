#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<vector>
#include<queue>
#include<cassert>
using namespace std;

#define DEBUG
#define Rpl(i,a,b) for(int i = (a); i < (b); ++i)
#define Rep(i,a,b) for(int i = (a); i <= (b); ++i)
typedef long long LL;
typedef pair<int,int> pii;
constexpr int mN = 1000005, mK = 1000005;
int ans = -1, n, m, fa[mN], dep[mN], earlist[mN], g[mN][21];
vector<int> son[mN];
struct Targ{
    int innode, l, r;
}tar[mK];

void dfs(int x){
    dep[x] = dep[fa[x]] + 1;
    g[x][0] = fa[x];
    if(x == 1) earlist[x] = 0;
    else earlist[x] = -1;
    for(int p = 1; (1 << p) <= dep[x] - 1; ++p){
        g[x][p] = g[g[x][p-1]][p-1];
    }
    for(int y : son[x]){
        dfs(y);
    }
}
void seek(Targ x){
    if(ans != -1) return;
    int u = x.innode, anc = u;
    if(earlist[u] != -1){
        ans = x.l;
        return;
    }
    for(int i = 20; i >= 0; --i){
        if((1 << i) <= dep[anc] - 1 && earlist[g[anc][i]] == -1)
            anc = g[anc][i];
    }
    anc = fa[anc];

    int ut = x.r - x.l + 1;
    if(dep[u] - dep[anc] <= x.r - x.l + 1){
        ans = x.l + (dep[u] - dep[anc] - 1);
        ut = dep[u] - dep[anc];
    }
    int depv = dep[anc] + ut;
    int v = u;

    for(int i = 20; i >= 0; --i){
        if(dep[v] - (1 << i) > depv) v = g[v][i];
    }
    v = fa[v];
    while(earlist[v] == -1){
        earlist[v] = x.l + (dep[v] - dep[anc] - 1);
        v = fa[v];
    }
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    
    cin>>n>>m;
    Rep(i, 2, n){
        cin>>fa[i];
        son[fa[i]].push_back(i);
    }
    dep[0] = 0;
    dfs(1);
    Rep(i, 1, m){
        cin>>tar[i].innode>>tar[i].l>>tar[i].r;
        assert(i == 1 || tar[i].l > tar[i-1].r);
        seek(tar[i]);
    }
    cout<<ans<<endl;
    return 0;
}