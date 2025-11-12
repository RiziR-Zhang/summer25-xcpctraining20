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
    if(r < l) return 0;
    return pre[r] - pre[l - 1];
}
LL delseq(int dl, int dr){
    return seq(dl + 1, n - dr);
}
#define Los cout<<"Bob"<<endl;
#define Win cout<<"Alice"<<endl;
void solve(LL val){
//    int d, u;
    int l = 0, r = n / 2;
    while(l < r){
        int mid = (l + r + 1) >> 1;
        if(delseq(mid, mid) > val){
            l = mid;
        }else{
            r = mid - 1;
        }
    }
    int x = 1 + l, y = n - l;

    int cx = x, _r = y;
    while(cx < _r){
        int mid = (cx + _r + 1) >> 1;
        if(seq(mid, y) > val){
            cx = mid;
        }else{
            _r = mid - 1;
        }
    }
    int cy = y, _l = x;
    while(_l < cy){
        int mid = (_l + cy) >> 1;
        if(seq(x, mid) > val){
            cy = mid;
        }else{
            _l = mid + 1;
        }
    }

    if((cx - x) % 2 == 0 && (y - cy) % 2 == 0){
        Los;
    }else{
        Win;
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
