#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<vector>
#include<cassert>
#include<cmath>
using namespace std;

#define DEBUG
#define Rpl(i,a,b) for(int i = (a); i < (b); ++i)
#define Rep(i,a,b) for(int i = (a); i <= (b); ++i)
typedef long long LL;
typedef pair<int,int> pii;
constexpr int mN = 100005;
int n;
int x[mN], y[mN], myXM, myXN, myYM, myYN;
LL sum(int Ox, int Oy){
    LL s = 0;
    Rep(i, 1, n){
        LL dx = x[i] - Ox, dy = y[i] - Oy;
        s += max(max(llabs(dx), llabs(dy)), llabs(dx + dy));
    }
    return s;
}
LL f(int Ox){
    int l = myYN, r = myYM;
    LL fl = sum(Ox, l), fr = sum(Ox, r);
    while(r - l > 2){
        int lm = (l + r) / 2, rm = lm + 1;
        LL flm = sum(Ox, lm), frm = sum(Ox, rm);
        // assert(flm != frm);
        if(flm == frm){
            // LL b = max((LL)sqrt(r - l + 1), 1ll);
            // LL _ll = max(l, lm - 2 * b),
            //     _rr = min(r, rm + 2 * b);
            // for(int i = _ll; i <= _rr; i += b){
            //     assert(sum(Ox, i) >= flm);
            // }
            l = r = lm;
            fl = fr = flm;
            break;
        }
        if(flm < frm){
            r = rm;
            fr = frm;
        }else{
            l = lm;
            fl = flm;
        }
    }
    LL ret = min(fl, fr);
    Rpl(i, l + 1, r){
        ret = min(ret, sum(Ox, i));
    }
    return ret;
}
void solve(){
    cin>>n;
    int z;
    myXM = -1e9, myXN = 1e9, myYM = -1e9, myYN = 1e9;
    Rep(i, 1, n){
        cin>>x[i]>>y[i];
        cin>>z;
        myXM = max(myXM, x[i]);
        myXN = min(myXN, x[i]);
        myYM = max(myYM, y[i]);
        myYN = min(myYN, y[i]);
    }
    int L = myXN, R = myXM;
    LL fL = f(L), fR = f(R);
    while(R - L > 2){
        int lm = (L + R) / 2, rm = lm + 1;
        LL flm = f(lm), frm = f(rm);
        if(flm == frm){
            // LL b = max((LL)sqrt(R - L + 1), 1ll);
            // LL _ll = max(L, lm - 2 * b),
            //     _rr = min(R, rm + 2 * b);
            // for(int i = _ll; i <= _rr; i += b){
            //     assert(f(i) >= flm);
            // }
            L = R = lm;
            fL = fR = flm;
            break;
        }
        if(flm < frm){
            R = rm;
            fR = frm;
        }else{
            L = lm;
            fL = flm;
        }
    }
    LL ans = min(fL, fR);
    Rpl(i, L + 1, R){
        ans = min(ans, f(i));
    }
    cout<<ans<<endl;
}
#define FILE
int main()
{
#ifdef FILE
freopen("1002.in","r",stdin);
#endif
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int tsk;
    cin>>tsk;
    while(tsk--){
        solve();
    }
#ifdef FILE
fclose(stdin);
#endif
    return 0;
}
