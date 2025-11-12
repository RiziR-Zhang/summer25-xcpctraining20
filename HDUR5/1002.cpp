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
constexpr int mN = 200005;
LL n, m, k, p, a[mN];
pii r[mN];
bool iF[mN];//isFull
bool chk(LL t){
    LL tot = 0, rcell = t * p;
    for(int i = 1; i <= n && rcell; ++i){
        if(a[i] >= t * k){
            LL dc = min(rcell, t);
            tot += dc * k;
            rcell -= dc;
            iF[i] = 1;
        }else{
            LL dc = min(rcell, a[i] / k);
            tot += dc * k;
            rcell -= dc;
            iF[i] = 0;
        }
    }
    for(int i = 1; i <= n && rcell; ++i){
        if(!iF[r[i].second]){
            tot += r[i].first;
            rcell--;
        }
    }
    return tot >= m;
}
LL BS(){
    LL l = 1, r = m;
    while(l < r){
        LL mid = (l + r) >> 1;
        if(chk(mid)){
            r = mid;
        }else{
            l = mid + 1;
        }
    }
    return l;
}
void solve(){
    cin>>n>>m>>k>>p;
    Rep(i, 1, n){
        cin>>a[i];
        r[i] = pii(a[i] % k, i);
    }
    sort(r + 1, r + n + 1, greater<pii>());
    // assert(r[1] > r[n]);
    int ans = BS();
    cout<<ans<<endl;
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
