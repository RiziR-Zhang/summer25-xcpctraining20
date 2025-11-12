#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<vector>
#include<cassert>
#include<queue>
#include<iomanip>
using namespace std;

#define DEBUG
#define Rpl(i,a,b) for(int i = (a); i < (b); ++i)
#define Rep(i,a,b) for(int i = (a); i <= (b); ++i)
typedef long long LL;
typedef pair<int,int> pii;
constexpr int mN = 33, stdN = 30, mM = 205, mW = 23;
constexpr LL ILLG = -1;
int n, m;
bool sto[mN], tot[mN], flag;
double mins;
struct EG{
    int u, v, w;
}e[mM];
vector<int> eid[mN];

void updans(double a2, double a1){
    mins = min(mins, a2 - a1 * a1);
}
LL f[mN][mN][mN][mN * mW];
void upd(LL& u, LL v){
    if(u == ILLG || v < u) u = v;
}
void solve(){
    mins = 400.1;
    memset(f, 0xff, sizeof(f));
//    f[1][1][0][0] = 0;
    Rep(i, 1, n) f[i][i][0][0] = 0;
    int wm = 20 * n;
    Rep(len, 0, n){
        Rep(sum, 0, wm){
            Rep(u, 1, n){
                Rep(v, 1, n){
                    if(f[u][v][len][sum] == ILLG) continue;
                    LL Fnow = f[u][v][len][sum];
                    if(u == 1) sto[v] = 1;
                    if(v == n) tot[u] = 1;
                    if(len == n) continue;
                    for(auto i: eid[v]){
                        int w = e[i].v;
                        upd(f[u][w][len + 1][sum + e[i].w], f[u][v][len][sum] + e[i].w * e[i].w);
                    }
                }
            }
        }
    }
    sto[1] = tot[n] = 1;
    assert(sto[n] == tot[1]);
    flag = sto[n];
    if(!flag) return;
    Rep(len, 1, n){
        Rep(sum, 0, wm){
            if(f[1][n][len][sum] != ILLG)
                updans(1.0 * f[1][n][len][sum] / len, 1.0 * sum / len);
        }
    }
    Rep(u, 1, n){
        if(!sto[u] || !tot[u]) continue;
        Rep(len, 1, n){
            Rep(sum, 0, wm){
                if(f[u][u][len][sum] != ILLG)
                    updans(1.0 * f[u][u][len][sum] / len, 1.0 * sum / len);
            }
        }
    }
}
//#define FILE
int main()
{
#ifdef FILE
freopen("D.in","r",stdin);
#endif
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin>>n>>m;
    Rep(i, 1, m){
        cin>>e[i].u>>e[i].v>>e[i].w;
        eid[e[i].u].push_back(i);
    }
    solve();
    if(!flag){
        cout<<-1<<endl;
    }else{
        cout<<fixed<<setprecision(12)<<mins<<endl;
    }
#ifdef FILE
fclose(stdin);
#endif
    return 0;
}
