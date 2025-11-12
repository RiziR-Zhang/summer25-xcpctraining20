#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<vector>
#include<cassert>
#include<queue>
using namespace std;

#define DEBUG
#define Rpl(i,a,b) for(int i = (a); i < (b); ++i)
#define Rep(i,a,b) for(int i = (a); i <= (b); ++i)
typedef long long LL;
typedef pair<LL,LL> pll;
typedef pair<int,int> pii;
constexpr int mN = 25;
int n;
LL a[mN], b[mN];
vector<int> e[mN];
priority_queue<pll, vector<pll>, greater<pll> > pq;
bool vis[mN];
void solve(int x, LL lv){
    pq.push(pll(a[x], x)), vis[x] = 1;
    while(!pq.empty()){
        int u = pq.top().second;
        pq.pop();
        if(a[u] > lv) continue;
        lv += b[u];
        for(auto v: e[u]){
            if(!vis[v]){
                vis[v] = 1;
                pq.push(pll(a[v], v));
            }
        }
    }
    cout<<lv<<endl;
    memset(vis + 1, 0, sizeof(bool) * n);
} 
//#define FILE
int main()
{
#ifdef FILE
freopen("1001.in","r",stdin);
freopen("1001bf.out","w",stdout);
#endif
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int tsk, Qr;
    cin>>tsk;
    int cnt = 0;
    while(tsk--){
        cin>>n>>Qr;
        Rep(i, 1, n) cin>>a[i];
        Rep(i, 1, n) cin>>b[i];
        int u,v;
        Rep(i, 2, n){
            cin>>u>>v;
            e[u].push_back(v);
            e[v].push_back(u);
        }
        int x;LL initVal;
        while(Qr--){
            cin>>x>>initVal;
if(++cnt == 2517){
    cout<<tsk<<endl;
    cout<<n<<Qr<<endl;
    Rep(i, 1, n) cout<<a[i]<<' ';
    cout<<endl;
    Rep(i,1,n)cout<<b[i]<<' ';
    Rep(u,1,n)for(auto v:e[u]) if(u < v) cout<<u<<' '<<v<<endl;
    cout<<endl;
    cout<<x<<' '<<initVal<<endl;
}
            solve(x, initVal);
        }
        Rep(i, 1, n){
            e[i].clear();
        }
    }
#ifdef FILE
fclose(stdin);fclose(stdout);
#endif
    return 0;
}
