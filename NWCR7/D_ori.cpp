#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<vector>
#include<cassert>
#include<queue>
#include<iomanip>
using namespace std;

#define DEBUG
#define Rpl(i,a,b) for(int i = (a); i < (b); ++i)
#define Rep(i,a,b) for(int i = (a); i <= (b); ++i)
typedef long long LL;
typedef pair<int,int> pii;
constexpr int mN = 33, stdN = 30, mM = 205;
int n, m;
bool flag, vis[mN], col[mN], ava[mN];
int AVAst;
double mins;
struct EG{
    int u, v, w;
}e[mM];
vector<int> eid[mN];
struct Node{
    LL pre1, pre2;
    int u, stut, dep;
};
void upd(double a1, double a2){
    mins = min(mins, a2 - a1 * a1);
}
//LL f[mN][mN][mN][mN * mW];
bool dfs(int u, int dep = 0, LL p1 = 0, LL p2 = 0){
    col[u] = 1;
    if(u == n){
        upd(1.0 * p1 / dep, 1.0 * p2 / dep);
        return 1;
    }
    bool rc = 0;
    vis[u] = 1;
    for(auto i: eid[u]){
        int v = e[i].v;
        if(!vis[v])
            rc |= dfs(v, dep + 1, p1 + e[i].w, p2 + e[i].w * e[i].w);
    }
    ava[u] |= rc;
    vis[u] = 0;
    return rc;
}
void findCirc(int st){
    queue<Node> que;
    auto S = [](int u){return 1 << (u - 1);};
    que.push(Node{0, 0, st, S(st), 0});//ignore all v < u (id)
    while(!que.empty()){
        Node hd = que.front();
        que.pop();
        int u = hd.u, v; 
        for(auto i: eid[u]){
            v = e[i].v;
            if(v == st){
                if(hd.stut & AVAst)
                    upd(1.0 * (hd.pre1 + e[i].w) / (hd.dep + 1), 1.0 * (hd.pre2 + e[i].w * e[i].w) / (hd.dep + 1));
            }else if(v < st || (S(v) & hd.stut)) continue;
            else{
                que.push(Node{
                    hd.pre1 + e[i].w,
                    hd.pre2 + e[i].w * e[i].w,
                    v,
                    hd.stut | S(v),
                    hd.dep + 1
                });
            }
        }        
    }
}
void solve(){
    mins = 400.1;
    dfs(1);
    flag = col[n];
    if(!flag) return;
    Rep(i, 1, n){
        if(ava[i])
            AVAst |= 1 << (i - 1);
    }
    Rep(i, 1, n){
        if(col[i]){
            findCirc(i);
        }
    }
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin>>n>>m;
    Rep(i, 1, m){
        cin>>e[i].u>>e[i].v>>e[i].w;
        eid[e[i].u].push_back(i);
    }
    solve();
    if(!flag){
        cout<<-1<<endl;
    }else{
        cout<<fixed<<setprecision(12)<<mins<<endl;
    }
    return 0;
}
