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
constexpr int mN = 200005, mM = 400005;
int n, m;
bool lb[mN << 1];
struct It{
    int l, r;
}it[mM];
void solve(){
    cin>>n>>m;
    Rep(i, 1, m){
        cin>>it[i].l>>it[i].r;
    }
    auto cmp = [](It x, It y){
        return x.l > y.l;
    };
    sort(it + 1, it + m + 1, cmp);
    int cnt = 0, lm = n * 2 + 1;
    memset(lb + 1, 0, sizeof(bool) * n * 2);
    for(int i = 1; i <= m; ++i){
        if(it[i].r < lm){
            ++cnt;
            lb[it[i].l] = 1;
            lm = it[i].l;
        }
    }
    if(cnt > n){
        cout<<-1<<endl;
        return;
    }
    int nn = n * 2, dep = 0;
    Rep(i, 1, nn){
        if(!lb[i] && cnt < n){
            ++cnt;
            lb[i] = 1;
        }
        if(lb[i]) dep++;
        else dep--;
    }
    if(dep != 0){
        cout<<-1<<endl;
        return;
    }
    Rep(i, 1, nn){
        if(lb[i]) cout<<'(';
        else cout<<')';
    }
    cout<<endl;
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
        // ALLClear();
    }
    return 0;
}
