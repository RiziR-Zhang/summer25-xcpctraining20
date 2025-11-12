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
constexpr int mN = 2000005;
int n, a[mN], pos[mN];

int main()
{
    ios::sync_with_stdio(0);
    int tsk;
    cin>>tsk;
    while(tsk--){
        cin>>n;
        Rep(i, 1, n){
            cin>>a[i];
            pos[a[i]] = i;
        }
        int l = n, r = 1, ans = 1;
        for(int val = n; val >= 1; --val){
            l = min(l, pos[val]);
            r = max(r, pos[val]);
            if(val < n)
                ans = max(ans, r - l + 1 - (n - val + 1 - 2));
        }
        cout<<ans<<'\n';
    }
    return 0;
}