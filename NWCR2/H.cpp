#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<vector>
#include<queue>
using namespace std;

#define DEBUG
#define Rpl(i,a,b) for(int i = (a); i < (b); ++i)
#define Rep(i,a,b) for(int i = (a); i <= (b); ++i)
typedef long long LL;
typedef pair<int,int> pii;
constexpr int mN = 100005, mM = 300005;
constexpr double eps = 1e-6;
int n, m;
struct Edge{
    int u, v;
    LL t, enh;
}e[mM];
LL _s[mM], _t[mM], dis[mN];
vector<int> gui[mN];
typedef pair<LL, int> plli;
struct Line{
    LL b, k;
    Line(LL _b = 0, LL _k = 0): b(_b),k(_k){} 
}roadK[mM];
struct PseudoSegment{
    int id;
    double x;
    PseudoSegment(int _id = 0, double _x = 0): id(_id), x(_x){}
}stk[mM];
int tp;
double intersectX(Line r1, Line r2){
    return (r1.b - r2.b) * 1.0 / (r2.k - r1.k);
}
void dijkstra(int S){
    static bool vis[mN];
    static priority_queue<plli, vector<plli>, greater<plli> > pq;
    memset(vis + 1, 0, sizeof(bool) * n);
    memset(dis + 1, 0x3f, sizeof(LL) * n);
    dis[S] = 0;
    pq.push({0, S});
    while(!pq.empty()){
//        auto [d, u] = pq.top();
        LL d = pq.top().first;
        int u = pq.top().second;
        pq.pop();
        if(vis[u]) continue;
        vis[u] = 1;
        for(auto ei: gui[u]){
            int v = e[ei].v;
            if(dis[v] > d + e[ei].t){
                dis[v] = d + e[ei].t;
                pq.push(plli(dis[v], v));
            }
        }
    }
}
void convex(){
    Rep(i, 1, m){
        roadK[i] = Line(_s[i] + e[i].t + _t[i], -e[i].enh);
    }
    auto cmp = [](Line r1, Line r2){
        return r1.k > r2.k ||
            (r1.k == r2.k && r1.b < r2.b);
    };
    sort(roadK + 1, roadK + m + 1, cmp);
    tp = 0;
    Rep(i, 1, m){
        if(i == 1){
            stk[tp = 1] = PseudoSegment(1, 0);
            continue;
        }else if(roadK[i - 1].k == roadK[i].k){
            continue;
        }
        while(tp && intersectX(roadK[i], roadK[stk[tp].id]) < stk[tp].x){
            --tp;
        }
        if(tp){
            ++tp;
            stk[tp] = PseudoSegment(i, intersectX(roadK[i], roadK[stk[tp - 1].id]));
        }else{
            stk[++tp] = PseudoSegment(i, 0);
        }
    }
    stk[++tp] = PseudoSegment(0, 1e9 + 1);
}
LL qr(int num){
    int l = 1, r = tp;
    while(l < r){
        int mid = (l + r + 1) >> 1;
        if(stk[mid].x + eps < num){
            l = mid;
        }else{
            r = mid - 1;
        }
    }
    int id = stk[l].id;
    return roadK[id].b + roadK[id].k * num;
}
void solve(){
    Rep(i, 1, m){
        gui[e[i].u].push_back(i);
    }
    dijkstra(1);
    Rep(i, 1, m){
        _s[i] = dis[e[i].u];
    }
    Rep(i, 1, n){gui[i].assign(0, 0);}
    Rep(i, 1, m){
        swap(e[i].u, e[i].v);
        gui[e[i].u].push_back(i);
    }
    dijkstra(n);
    Rep(i, 1, m){
        _t[i] = dis[e[i].u];
    }
    Rep(i, 1, n){gui[i].assign(0, 0);}

    convex();
    int Q, t;
    cin>>Q;
    while(Q--){
        cin>>t;
        cout<<qr(t)<<'\n';
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
        cin>>n>>m;
        Rep(i, 1, m){
            cin>>e[i].u>>e[i].v>>e[i].t>>e[i].enh;
        }
        solve();
    }
    return 0;
}
