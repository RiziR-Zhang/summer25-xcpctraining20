#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<vector>
#include<cassert>
using namespace std;

//#define DEBUG
#define Rpl(i,a,b) for(int i = (a); i < (b); ++i)
#define Rep(i,a,b) for(int i = (a); i <= (b); ++i)
typedef long long LL;
typedef pair<int,int> pii;
constexpr int mN = 100005, mB = 23, stdB = 20;
constexpr LL nINF = 0xcfcfcfcfcfcfcfcf;
int m, bond, las[mN][2];
LL d;
struct Candd{
    LL p;
    int typ;
    bool operator<(const Candd rhs)const{
        return p < rhs.p;
    }
}cd[mN];
LL f[mN][mB][mB << 1], l[mB];
void upd(LL& u, LL v){
    if(v > u) u = v;
}
void solve(){
    cin>>bond>>m>>d;
    Rep(i, 1, bond){
        cin>>l[i];
    }
    Rep(i, 1, m){
        cin>>cd[i].p>>cd[i].typ;
    }
    sort(cd + 1, cd + m + 1);
    for(int i = 1, ls1 = 0, ls2 = 0; i <= m; ++i){
        if(ls1 && cd[i].p - cd[ls1].p <= d)
            las[i][0] = ls1;
        else
            las[i][0] = 0;
        if(ls2 && cd[i].p - cd[ls2].p <= d)
            las[i][1] = ls2;
        else
            las[i][1] = 0;
        if(cd[i].typ == 1){
            ls1 = i;
        }else{
            ls2 = i;
        }
    }
    Rep(i, 0, m)Rep(b, 0, bond)Rep(j, 0, bond * 2) f[i][b][j] = nINF;
    Rep(i, 0, m) f[i][0][0] = 0;
    Rep(b, 1, bond){
        Rep(i, 1, m){
            int tp = min(b * 2, i);
            Rep(j, 0, tp){
                int dj = (cd[i].typ == 1);
                f[i][b][j] = f[i - 1][b][j];
                if((dj && j == 0) || cd[i].p > l[b]) continue;
                if(las[i][0] && j - dj > 0){
                    upd(f[i][b][j], f[las[i][0] - 1][b - 1][j - dj - 1] + cd[i].p + cd[las[i][0]].p);
                }
                if(las[i][1]){
                    upd(f[i][b][j], f[las[i][1] - 1][b - 1][j - dj] + cd[i].p + cd[las[i][1]].p);
                }
            }
        }
    }
#ifdef DEBUG
Rep(i, 1, m){
    Rep(b, 0, bond){
        cout<<'('<<i<<','<<b<<')'<<": ";
        Rep(j, 0, bond * 2){
            cout<<f[i][b][j]<<' ';
        }
        cout<<endl;
    }
}
#endif
    Rep(j, 0, bond * 2){
        if(f[m][bond][j] > 0){
            cout<<f[m][bond][j]<<' ';
        }else{
            cout<<-1<<' ';
        }
    }
    cout<<endl;
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
