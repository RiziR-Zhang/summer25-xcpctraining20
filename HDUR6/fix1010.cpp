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

#define _YES_ cout<<"YES"<<endl;
#define _NO_ cout<<"NO"<<endl;
int n;
LL a[mN];
void solve(){
    cin>>n;
    Rep(i, 1, n){
        cin>>a[i];
    }
    sort(a + 1, a + n + 1, greater<LL>());
    LL m1 = 0, c1 = 0;
    for(m1 = a[1], c1 = 1; c1 <= n && a[c1] == m1; ++c1);
    c1--;
    if(c1 % 2 ==0){
        _YES_;
        return;
    }
    LL ssum = 0;
    Rep(i, c1 + 1, n) ssum += a[i];
    if(ssum < m1){
        _NO_;
        return;
    }
    if(c1 >= 3){
        _YES_;
        return;
    }
    LL m2 = a[c1 + 1], c2 = 0;
    for(c2 = 1; c1 + c2 <= n && a[c1 + c2] == m2; c2++);
    --c2;
    if(m2 * c2 < m1){
        _YES_;
        return;
    }
    LL cons = (m1 - 1) / m2 + 1;
    if((c2 - cons) % 2 == 0){
        _YES_;
        return;
    }
    ssum -= m2 * c2;
    if((cons - 1) * m2 >= m1 - ssum){
        _YES_;
    }else{
        _NO_;
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
        solve();
        // ALLClear();
    }
    return 0;
}
