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
constexpr int mN = 300005;
LL n, k, c, a[mN], pre[mN];
priority_queue<LL> pq;

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin>>n>>k>>c;
    Rep(i, 1, k){
        cin>>a[i];
        pre[i] = pre[i - 1] + a[i];
    }
    Rep(i, k + 1, n){
        cin>>a[i];
        pq.push(a[i] - (i - k) * c);
    }
    LL ans = pre[k], heapsum = 0;
    for(int sw = 1; sw <= k; ++sw){
        int j = k + 1 - sw;
        pq.push(a[j] + (k - j) * c);
        heapsum += pq.top();
        pq.pop();
        ans = max(ans, pre[j - 1] + heapsum - c * sw * (sw - 1) / 2);
    }
    cout<<ans<<endl;
    return 0;
}
