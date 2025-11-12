#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<vector>
#include<queue>
using namespace std;

#define DEBUG
#define Rpl(i,a,b) for(LL i = (a); i < (b); ++i)
#define Rep(i,a,b) for(LL i = (a); i <= (b); ++i)
typedef long long LL;
typedef pair<int,int> pii;
constexpr int mN = 200005;
constexpr LL mdN  = 1e9 + 7, inv2 = (mdN + 1) / 2;
int n;
struct Core{
    LL x, y, a;
}core[mN];

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int tsk;
    cin>>tsk;
while(tsk--){

    cin>>n;
    LL ox, oy;
    Rep(i, 1, n){
        cin>>ox>>oy>>core[i].a;
        core[i].x = ox - oy;
        core[i].y = ox + oy;
    }
    LL ans = 0;
    auto cmpx = [](const Core &u, const Core &v){
        return u.x < v.x;
    };
    sort(core + 1, core + n + 1, cmpx);
    LL sufx = 0, prex = 0;//sufx =\sum x_j, prex = \sum -x_j
    Rep(i, 1, n){
        sufx += core[i].x;
    }
    Rep(i, 1, n){
        ans = (ans + (sufx - core[i].x * (n - i + 1) + prex + core[i].x * (i - 1)) % mdN * core[i].a) % mdN;
        sufx -= core[i].x;
        prex -= core[i].x;
    }
    auto cmpy = [](const Core &u, const Core &v){
        return u.y < v.y;
    };
    sort(core + 1, core + n + 1, cmpy);
    LL sufy = 0, prey = 0;
    Rep(i, 1, n){
        sufy += core[i].y;
    }
    Rep(i, 1, n){
        ans = (ans + (sufy - core[i].y * (n - i + 1) + prey + core[i].y * (i - 1)) % mdN * core[i].a) % mdN;
        sufy -= core[i].y;
        prey -= core[i].y;
    }
    cout<<ans * inv2 % mdN << endl;
}
    return 0;
}
