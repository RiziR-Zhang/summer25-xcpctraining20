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
constexpr int mN = 200005, mND = mN << 1, FLR = 19;
int n, nn, a[mND], k[mN], lk[mN], sum[mN], trdt[mND];
int fa[mND], dep[mND], anc[FLR][mND];
vector<int> e[mND];
void dmake(int u, int f){
    anc[0][u] = fa[u] = f;
    dep[u] = dep[f] + 1;
    for(int p = 1; (1 << p) <= dep[u]; ++p){
        anc[p][u] = anc[p - 1][anc[p - 1][u]];
    }
    for(auto v: e[u]){
        if(v == f) continue;
        dmake(v, u);
    }
}
void deal(int LK, int K){
    if(dep[K] <= dep[LK]){
        trdt[1]++;
        trdt[LK]--;
        return;
    }
    for(int p = 18; p >= 0; --p){
        if(dep[K] - (1 << p) > dep[LK]){
            K = anc[p][K];
        }
    }
    if(fa[K] == LK){
        trdt[K]++;
    }else{
        trdt[1]++;
        trdt[LK]--;
    }
}
void dfs(int u, int presum = 0){
    presum += trdt[u];
    if(a[u] > 0){
        sum[a[u]] = presum;
    }
    for(auto v: e[u]){
        if(v == fa[u]) continue;
        dfs(v, presum);
    }
}
int quek[mND], quelk[mN], hd1, hd2, tl1, tl2;
bool unlk[mND], vis[mND];
//priority_queue<pii, vector<pii>, greater<pii> > pq;
bool chk(){
    hd1 = hd2 = 1;
    tl1 = tl2 = 0;
    memset(unlk + 1, 0, sizeof(bool) * n);
    memset(vis + 1, 0, sizeof(bool) * nn);
    Rep(i, 1, n){
        if(sum[i] == n) quek[++tl1] = k[i], vis[k[i]] = 1, unlk[i] = 1;
    }
    while(hd1 <= tl1){
        int u = quek[hd1++];
        if(a[u] > 0) unlk[a[u]] = 1;
        for(auto v: e[u]){
            if(vis[v]) continue;
            if(a[v] > 0){
                quek[++tl1] = v;
                vis[v] = 1;
                unlk[a[v]] = 1;
                if(vis[lk[a[v]]]) quek[++tl1] = lk[a[v]];
            }else{
                vis[v] = 1;
                if(unlk[-a[v]]) quek[++tl1] = v;
            }
        }
    }
    return tl1 == nn;
}
void solve(){
    cin>>n;
    nn = n * 2;
    Rep(i, 1, nn){
        cin>>a[i];
        if(a[i] > 0) k[a[i]] = i;
        else lk[-a[i]] = i;
    }
    int u, v;
    Rep(i, 2, nn){
        cin>>u>>v;
        e[u].push_back(v);
        e[v].push_back(u);
    }
    fa[0] = dep[0] = 0;
    dmake(1, 0);
    Rep(i, 1, n){
        deal(lk[i], k[i]);
    }
    dfs(1);
    if(chk()){
        Rep(i, 1, n){
            cout<<(sum[i] == n);
        }
    }else{
        Rep(i, 1, n) cout<<'0';
    }
    cout<<endl;
}
void ALLClear(){
    Rep(i, 1, nn){
        e[i].clear();
    }
    memset(trdt + 1, 0, sizeof(int) * nn);
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
