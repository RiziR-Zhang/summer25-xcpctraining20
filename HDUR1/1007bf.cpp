#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<vector>
#include<queue>
using namespace std;

#define DEBUG
#define FILE
#define Rpl(i,a,b) for(int i = (a); i < (b); ++i)
#define Rep(i,a,b) for(int i = (a); i <= (b); ++i)
typedef long long LL;
typedef pair<int,int> pii;
constexpr int mN = 100005;
int n, x, a[mN], ans;
vector<int> G[mN];
int fa[mN], sz[mN], dep[mN];
void dfs(int u){
    sz[u] = 1;
    for(auto v: G[u]){
        if(v == fa[u]) continue;
        fa[v] = u;
        dep[v] = dep[u] + 1;
        dfs(v);
        sz[u] += sz[v];
    }
}
int gcd(int p, int q){
    return q ? gcd(q, p % q) : p;
}
int lcm(int p, int q){
    return p / gcd(p, q) * q;
}
int pathlcm(int u, int v){
    int val = 1;
    if(dep[u] < dep[v]) swap(u, v);
    while(dep[u] > dep[v]){
        val = lcm(val, a[u]);
        u = fa[u];
    }
    while(u != v){
        val = lcm(val, a[u]);
        val = lcm(val, a[v]);
        u = fa[u];
        v = fa[v];
    }
    return lcm(val, a[u]);
}
void ALLClear(){
    Rep(i, 1, n){
        G[i].clear();

    }
}
int main()
{
#ifdef FILE
    freopen("1007.in", "r", stdin);
    freopen("1007bf.txt", "w", stdout);
#endif
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int tsk;
    cin>>tsk;
    while(tsk--){
        cin>>n>>x;
        int u, v;
        Rpl(i, 1, n){
            cin>>u>>v;
            G[u].push_back(v);
            G[v].push_back(u);
        }
        Rep(i, 1, n){
            cin>>a[i];
        }
        fa[1] = 0;
        dep[1] = 1;
        dfs(1);
        ans = 0;
        Rep(i, 1, n)Rep(j, i, n){
            ans += (pathlcm(i, j) == x);
        }
        cout<<ans<<endl;
        ALLClear();
    }
#ifdef FILE
fclose(stdin);
fclose(stdout);
#endif
    return 0;
}
