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
constexpr int mN = 25;
int n,m;
LL dif, lim[mN], ans[mN];
struct Per{
    LL e;int t;
}per[mN];
LL sum, pre,a[mN];
void dfs(int p, int k){
    if(p == n * 2 + 1){
        ans[pre] = max(ans[pre], sum);
        return;
    }
    for(int i = k; i <= m && per[i].e <= lim[(p + 1)/2] && (p % 2 == 1 || per[i].e - a[p - 1] <= dif);++i){
        sum += per[i].e;
        pre += (per[i].t==1);
        a[p] = per[i].e;
        dfs(p + 1, i + 1);
        sum -= per[i].e;
        pre -= (per[i].t==1);
    }
}
#define FILE
int main()
{
#ifdef FILE
freopen("I.in","r",stdin);
freopen("Ibf.out","w",stdout);
#endif
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int tsk;
    cin>>tsk;
    while(tsk--){
        cin>>n>>m>>dif;
        Rep(i,1,n)cin>>lim[i];
        Rep(i,1,m){
            cin>>per[i].e>>per[i].t;
        }
        sort(per + 1, per + m + 1, [](Per a, Per b){return a.e < b.e;});
        sort(lim + 1, lim + n + 1);
        memset(ans, 0xff, sizeof(ans));
        dfs(1,1);
        Rep(i,0,n * 2)cout<<ans[i]<<' ';
        cout<<endl;
    }
#ifdef FILE
fclose(stdin);fclose(stdout);
#endif
    return 0;
}
