#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<vector>
#include<cassert>
using namespace std;

// #define DEBUG
#define Rpl(i,a,b) for(int i = (a); i < (b); ++i)
#define Rep(i,a,b) for(int i = (a); i <= (b); ++i)
typedef long long LL;
typedef pair<int,int> pii;
constexpr int mN = 305;

int n;
LL modN, f[mN][mN][mN][2][2], A[mN][mN];
inline void mathinit(int len){
    Rep(i, 0, len){
        A[i][0] = 1;
        Rep(j, 1, i){
            A[i][j] = A[i][j - 1] * (i - j + 1) % modN;
        }
    }
}
inline void trans(LL &trto, LL trfm){
    trto = (trto + trfm) % modN;
}
inline LL qpow(LL a, LL b){
    LL pw = 1;
    while(b){
        if(b & 1) pw = pw * a % modN;
        a = a * a % modN;
        b >>= 1;
    }
    return pw;
}
void solve(){
    mathinit(n);
    f[0][0][0][0][0] = 1;
    Rpl(i, 0, n){
        Rep(col, i > 0, i){//aka j
            int upm = min(col, n - 1 - col);
            Rep(up, 0, upm){
                Rep(st, 0, 3){
                    bool exsj = st & 1, exsjp1 = st & 2;
                    int collow = col - up - exsj - exsjp1;
                    if(collow < 0) continue;
                    LL Fnow = f[i][col][up][exsj][exsjp1];
                    if(col >= 2){

                    // c_i<col & exs
                    trans(f[i + 1][col][up][exsj][exsjp1], Fnow * collow);
                    
                    // c_i < col & !exs
                    int nex = col - 1 - collow;
                    if(nex > 0){
                        trans(f[i + 1][col + 1][up][exsjp1][0], Fnow * nex);
                        if(up > 0)
                            trans(f[i + 1][col + 1][up - 1][exsjp1][1], Fnow * nex % modN * up);
                    }

                    }

                    /*  00: c ok, c + 1 nok
                        01: c ok, c + 1 ok
                        10: c nok, c + 1 nok
                        11: c nok, c + 1 ok
                    */
                    // col, must nexs
                    if(!exsj && col >= 1){
                        trans(f[i + 1][col + 1][up][exsjp1][0], Fnow);
                        if(up > 0)
                            trans(f[i + 1][col + 1][up - 1][exsjp1][1], Fnow * up);
                    }

                    //col + 1, must exs
                    if(exsjp1){
                        trans(f[i + 1][col][up][exsj][exsjp1], Fnow);
                    }

                    //(col + 1, infty), exs
                    if(up){
                        trans(f[i + 1][col][up][exsj][exsjp1], Fnow * up);
                    }
                    // (col + 1, infty), !exs
                    trans(f[i + 1][col + 1][up + 1][exsjp1][0], Fnow);
                    trans(f[i + 1][col + 1][up][exsjp1][1], Fnow * (up + 1));
                }
            }
        }
        int ansn = i + 1;
        LL calc = 0;
        Rpl(col, 1, ansn){
            int upm = min(col, max(0, ansn - 1 - col));
            Rep(up, 0, upm){//when ansn = 1, none is added to calc, then output 1^1-0=1
                Rep(st, 0, 3){
                    bool exsj = st & 1, exsjp1 = st & 2;
#ifdef DEBUG
cout<<col<<','<<up<<','<<exsj<<','<<exsjp1<<':'<<f[ansn][col][up][exsj][exsjp1]<<'*'<<A[ansn - 1 - col][up]<<"("<<ansn - 1 - col<<','<<up<<")"<<endl;
#endif
                    trans(calc, f[ansn][col][up][exsj][exsjp1] * A[ansn - 1 - col][up]);
                }
            }
        }
        //col == ansn
#ifdef DEBUG
cout<<ansn<<','<<0<<':'<<f[ansn][ansn][0][0][0]<<' '
    <<f[ansn][ansn][0][1][0]<<' '
    <<f[ansn][ansn][0][0][1]<<' '
    <<f[ansn][ansn][0][1][1]<<' '
    <<endl;
#endif
        trans(calc, f[ansn][ansn][0][1][0]);
        cout<<(qpow(ansn, ansn) + modN - calc) % modN << ' ';
    }
    cout<<endl;
}
void ALLClear(){
    Rep(i, 1, n){
        Rep(col, 1, i){
            memset(f[i][col], 0, sizeof(f[i][col][0]) * min(col + 2, n - col + 2));
        }
    }
}
// #define FILE
int main()
{
#ifdef FILE
    freopen("1012.in", "r", stdin);
    freopen("1012.out", "w", stdout);
#endif
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int tsk;
    cin>>tsk;
    while(tsk--){
        cin>>n>>modN;
        solve();
        ALLClear();
    }
#ifdef FILE
    fclose(stdin);
    fclose(stdout);
#endif
    return 0;
}
