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
LL f[mN][2][mB << 1], l[mB];
void upd(LL& u, LL v){
    if(v > u) u = v;
}
void solve(){
    cin>>bond>>m>>d;
    Rep(i, 1, bond){
        cin>>l[i];
    }
    sort(l + 1, l + bond + 1);
    Rep(i, 1, m){
        cin>>cd[i].p>>cd[i].typ;
    }
    sort(cd + 1, cd + m + 1);
    for(int i = 1, ls1 = 0, ls2 = 0; i <= m; ++i){
        las[i][0] = (ls1 && cd[i].p - cd[ls1].p <= d) ? ls1 : 0;
        las[i][1] = (ls2 && cd[i].p - cd[ls2].p <= d) ? ls2 : 0;
        if(cd[i].typ == 1){
            ls1 = i;
        }else{
            ls2 = i;
        }
    }
    memset(f, 0xcf, sizeof(f[0]) * (m + 1));
    Rep(i, 0, m) f[i][0][0] = 0;

    Rep(b, 1, bond){
        int nowb = b & 1, lasb = (b - 1) & 1;
        Rep(i, 0, m) memset(f[i][nowb], 0xcf, sizeof(LL) * (bond * 2 + 1));

        Rep(i, b * 2, m){
            int tp = min(b * 2, i), dj = (cd[i].typ == 1);
            memcpy(f[i][nowb], f[i - 1][nowb], sizeof(LL) * (tp + 1));
            if(cd[i].p > l[b]) continue;
            Rep(j, dj, tp){
                if(las[i][0] && j - dj > 0){
                    upd(f[i][nowb][j], f[las[i][0] - 1][lasb][j - dj - 1] + cd[i].p + cd[las[i][0]].p);
                }
                if(las[i][1]){
                    upd(f[i][nowb][j], f[las[i][1] - 1][lasb][j - dj] + cd[i].p + cd[las[i][1]].p);
                }
            }
        }
    }
#ifdef DEBUG
Rep(i, 1, m){
    Rep(b, 1, bond){
        cout<<'('<<i<<','<<b<<')'<<": ";
        Rep(j, 0, bond * 2){
            cout<<f[i][b & 1][j]<<' ';
        }
        cout<<endl;
    }
}
#endif
    Rep(j, 0, bond * 2){
        if(f[m][bond & 1][j] > 0){
            cout<<f[m][bond & 1][j]<<' ';
        }else{
            cout<<-1<<' ';
        }
    }
    cout<<endl;
}
// #define FILE

int main()
{
#ifdef FILE
freopen("I.in","r",stdin);
freopen("I.out","w",stdout);
#endif
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int tsk;
    cin>>tsk;

    while(tsk--){
        solve();
        // ALLClear();
    }
#ifdef FILE
fclose(stdin);fclose(stdout);
#endif
    return 0;
}
