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
constexpr int mN = 200005;
void solve(){
    int n;
    cin>>n;
    vector<int> a(n + 1), b(n + 1), pos(n + 1);
    Rep(i, 1, n) cin>>a[i];
    Rep(i, 1, n) cin>>b[i], pos[b[i]] = i;
    int cnt = 0;
    Rep(i, 1, n){
        if(i == 1 || (pos[a[i]] != pos[a[i - 1]] + 1)) cnt++;
    }
    cout<<cnt<<endl;

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
