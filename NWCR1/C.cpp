#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<vector>
#include<queue>
#include<cassert>
using namespace std;

#define DEBUG
//#define FILE
#define Rpl(i,a,b) for(int i = (a); i < (b); ++i)
#define Rep(i,a,b) for(int i = (a); i <= (b); ++i)
typedef long long LL;
typedef pair<int,int> pii;
constexpr int mN = 1005;
constexpr LL INF = 3e9 + 1;
int n, q;
LL a[mN], w[mN];
struct Blk{
    LL x, mulp, muln;
    bool operator<(const Blk &rhs) const{
        return x < rhs.x;
    }
}blk[mN];
struct Seg{
    LL x, mul;
}seg[mN];

int main()
{
#ifdef FILE
freopen("C.in","r",stdin);
freopen("C.out","w",stdout);
#endif
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin>>n>>q;
    Rep(i, 1, n){
        cin>>a[i];
        blk[i].x = a[i];
    }
    Rpl(i, 1, n){
        cin>>w[i];
        int x = a[i] > a[i + 1] ? i + 1 : i;
        int y = a[i] < a[i + 1] ? i + 1 : i;
        blk[x].mulp += w[i];
        blk[y].muln += w[i];
    }
    sort(blk + 1, blk + n + 1);
    LL kmul = 0;
    int m = 0;
    seg[0] = {blk[1].x - INF, 0};
    for(int i = 1; i <= n;){
        ++m;
        LL v = blk[i].x;
        for(; i <= n && blk[i].x == v; ++i){
            kmul += blk[i].mulp - blk[i].muln;
        }
        if(i > n) assert(kmul == 0);
        seg[m] = {v, kmul};
    }
    seg[m + 1] = {INF, 0};
    LL d;
    while(q--){
        cin>>d;
        LL l = seg[1].x - d, r = seg[1].x;
        int li = 0, ri = 1;
        LL sum = 0,summax = 0;
        while(li < m){
            int deltax = min(seg[li + 1].x - l, seg[ri + 1].x - r);
            sum += deltax * (seg[ri].mul - seg[li].mul);
            summax = max(summax, sum);
            if((l += deltax) == seg[li + 1].x) li++;
            if((r += deltax) == seg[ri + 1].x) ri++;
        }
        cout<<summax<<'\n';
    }
#ifdef FILE
fclose(stdin);fclose(stdout);
#endif
    return 0;
}
