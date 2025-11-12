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
constexpr int mN = 100005;
int n;
LL a[mN], pre[mN];
LL seq(int l, int r){
    if(r > l) return 0;
    return pre[r] - pre[l - 1];
}
LL delseq(int dl, int dr){
    return seq(dl + 1, n - dr);
}
#define Los cout<<"Bob"<<endl;
#define Win cout<<"Alice"<<endl;
void solve(LL val){
//    int d, u;
    int l = 0, r = (n + 1) / 2;
    while(l < r){
        int mid = (l + r) >> 1;
        if(seq(mid + 1, n - mid) < val){
            r = mid;
        }else{
            l = mid + 1;
        }
    }
    int D = l, R = l;
    bool Ver = (delseq(D - 1, R) < val), Hor = (delseq(D, R - 1) < val);
    if(Ver && Hor){
        
    }
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin>>n;
    Rep(i, 1, n){
        cin>>a[i];
        pre[i] = pre[i - 1] + a[i];
    }
    int Qr;
    cin>>Qr;
    LL Val;
    while(Qr--){
        cin>>Val;
        solve(Val);
    }
    return 0;
}
