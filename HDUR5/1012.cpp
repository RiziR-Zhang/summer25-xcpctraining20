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
struct Pt{
    LL x, y;
    Pt(LL X = 0, LL Y = 0):x(X), y(Y){}
}P[mN];
void solve(){
    cin>>n;
    Rep(i, 1, n){
        cin>>P[i].x;
    }
    Rep(i, 1, n){
        cin>>P[i].y;
        P[i] = Pt(P[i].x - P[i].y, P[i].x + P[i].y);
    }
    auto cx = [](Pt p, Pt q){
        return p.x < q.x;
    };
    sort(P + 1, P + n + 1, cx);
    LL minmin = 2e12 + 1;
    Rep(i, 2, n){
        minmin = min(minmin, P[i].x - P[i - 1].x);
    }
    auto cy = [](Pt p, Pt q){
        return p.y < q.y;
    };
    sort(P + 1, P + n + 1, cy);
    Rep(i, 2, n){
        minmin = min(minmin, P[i].y - P[i - 1].y);
    }
    cout<<minmin<<endl;
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
